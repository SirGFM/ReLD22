#include <cstring>
#include <core/save.h>

//#define __GFM_DEBUG__
#ifndef __GFM_DEBUG__
	#define getpos() 
#else
	int __pos__;
	#define getpos() __pos__ = ftell(this->file)
#endif

CppOGL::Save::Save() {
	this->file = NULL;
	this->filename = NULL;
	this->state = 0;
	this->size = 0;
}

CppOGL::Save::~Save() {
	if (this->file)
		this->close();
}

void CppOGL::Save::bind(const char *name) {
	if (!(this->file = fopen(name, "rb+")))
		this->file = fopen(name, "wb+");
	this->getFileSize();
	this->filename = name;
}

void CppOGL::Save::flush(int force) {
	if (force ||
		((this->state & DIDWRITE)&&(this->state & ISREADING)) ||
		((this->state & DIDREAD)&&(this->state & ISWRITING)) )
		fseek(this->file, 0, SEEK_CUR);
	this->state &= 0xc;
}

void CppOGL::Save::close() {
	this->flush(1);
	fclose(this->file);
	this->file = NULL;
	this->filename = NULL;
}

int CppOGL::Save::write(const char *id, void *data, int size) {
	int tmp;
	
	this->state |= ISWRITING;
	this->flush(0);
	
	tmp = this->getIDPosition(id);
	if (!(tmp == EMPTY || tmp == INF)) {
		getpos();
		this->flush(1);
		getpos();
		fwrite(data, tmp, 1, this->file);
		this->flush(1);
	}
	else {
		int len = strlen(id)+1;
		getpos();
		fseek(this->file, 0, SEEK_END);
		fwrite(&len, sizeof(int), 1, this->file);
		fwrite(id, sizeof(char), len, this->file);
		fwrite(&size, sizeof(int), 1, this->file);
		fwrite(data, size, 1, this->file);
		this->flush(1);
		getpos();
		this->size += len+size+sizeof(int)+sizeof(int);
	}
	this->state |= DIDWRITE;
}

int CppOGL::Save::read(const char *id, void *data) {
	int size;
	
	this->state |= ISREADING;
	this->flush(0);
	
	size = this->getIDPosition(id);
	if (size == EMPTY || size == INF)
		return size;
	fread(data, size, 1, this->file);
	this->flush(1);
	
	this->state |= DIDREAD;
	return 0;
}

int CppOGL::Save::clear() {
	if (!this->file)
		return FNO;
	fclose(this->file);
	this->file = fopen(this->filename, "wb+");
	return 0;
}

int CppOGL::Save::getIDPosition(const char *id) {
	int size;
	char *str;
	
	if (!this->size)
		return EMPTY;
	fseek(this->file, 0, SEEK_SET);
	while (1) {
		this->readID(&str);
		getpos();
		int res = strcmp(id, str);
		getpos();
		delete[] str;
		if (!res) {
			fread(&size, sizeof(int), 1, this->file);
			break;
		}
		int next;
		getpos();
		fread(&next, sizeof(int), 1, this->file);
		fseek(this->file, next, SEEK_CUR);
		getpos();
		if (ftell(this->file) == this->size)
			return INF;
	}
	return size;
}

void CppOGL::Save::readID(char **id) {
	char *str;
	int len;
	fread(&len, sizeof(int), 1, this->file);
	str = new char[len];
	fread(str, sizeof(char), len, this->file);
	*id = str;
}

void CppOGL::Save::getFileSize() {
	fseek(this->file, 0, SEEK_END);
	this->size = ftell(this->file);
	fseek(this->file, 0, SEEK_SET);
}
