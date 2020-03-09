#include <cstdio>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <core/audio.h>
#include <core/buffer.h>
#include <core/mesh.h>
#include <core/tile.h>
#include <core/texture.h>

#include <game/assets/data.h>
#include <game/assets/balltiles.h>
#include <game/assets/bartile.h>
#include <game/assets/gmwindow.h>
#include <game/assets/spritetiles.h>
#include <game/assets/titletile.h>

void loadAudio(CppOGL::Audio **audio, const char *name, int looped) {
	int len;
	Uint8 *data;
	
	FILE *f = fopen(name, "rb");
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	data = new Uint8[len];
	fread(data, sizeof(char), len, f);
	
	fclose(f);
	
	(*audio) = new CppOGL::Audio(data, len, looped);
	delete[] data;
}

Data *Data::self = NULL;

int Data::init() {
	if (Data::self != NULL)
		return !Data::self->error;
	Data::self = new Data();
	return !Data::self->error;
}
void Data::clear() {
	if (Data::self != NULL)
		delete Data::self;
}

Data::Data() {
	FILE *f;
	
	this->error = 1;
	
	if (!this->checkFiles())
		return;
	
	// loads texture dinamically
	f = fopen("data/atlas.dat", "rb");
	char texdata[256*128*4];
	fread(texdata, sizeof(char)*256*128*4, 1, f);
	fclose(f);
	this->textures[TEXATLAS] = new CppOGL::Texture(256, 128, texdata);
	
	const GLshort vindex[] = {0, 1, 2, 2, 3, 0};
	
	const float v8x8[] = {-4.0f, -4.0f, -4.0f, 4.0f, 4.0f, 4.0f, 4.0f, -4.0f};
	this->buffers[BUFF8x8] = new CppOGL::Buffer(v8x8, 4);
	this->meshes[MESH8x8] = new CppOGL::Mesh(this->buffers[BUFF8x8], vindex, 2);
	balltiles((this->buffers+BUFFTILE8x8), this->tiles, this->textures[TEXATLAS]);
	
	const float v32x32[] = {-16.0f, -16.0f, -16.0f, 16.0f, 16.0f, 16.0f, 16.0f, -16.0f};
	this->buffers[BUFF32x32] = new CppOGL::Buffer(v32x32, 4);
	this->meshes[MESH32x32] = new CppOGL::Mesh(this->buffers[BUFF32x32], vindex, 2);
	spritetiles((this->buffers+BUFFTILE32x32), this->tiles, this->textures[TEXATLAS]);
	
	const float v128x16[] = {-64.0f, -8.0f, -64.0f, 8.0f, 64.0f, 8.0f, 64.0f, -8.0f};
	this->buffers[BUFF128x16] = new CppOGL::Buffer(v128x16, 4);
	this->meshes[MESH128x16] = new CppOGL::Mesh(this->buffers[BUFF128x16], vindex, 2);
	bartile((this->buffers+BUFFTILE128x16), this->tiles, this->textures[TEXATLAS]);
	
	const float v128x64[] = {-64.0f, -32.0f, -64.0f, 32.0f, 64.0f, 32.0f, 64.0f, -32.0f};
	this->buffers[BUFF128x64] = new CppOGL::Buffer(v128x64, 4);
	this->meshes[MESH128x64] = new CppOGL::Mesh(this->buffers[BUFF128x64], vindex, 2);
	titletile((this->buffers+BUFFTILE128x64), this->tiles, this->textures[TEXATLAS]);
	
	const float v256x32[] = {-128.0f, -16.0f, -128.0f, 16.0f, 128.0f, 16.0f, 128.0f, -16.0f};
	this->buffers[BUFF256x32] = new CppOGL::Buffer(v256x32, 4);
	this->meshes[MESH256x32] = new CppOGL::Mesh(this->buffers[BUFF256x32], vindex, 2);
	gmwindow((this->buffers+BUFFTILE256x32), this->tiles, this->textures[TEXATLAS]);
	
	loadAudio((this->audios+MENUSONG), "data/ld22_menu.dat", 1);
	loadAudio((this->audios+SADSONG), "data/ld22_alone_final.dat", 1);
	loadAudio((this->audios+NORMSONG), "data/ld22_normal_final.dat", 1);
	loadAudio((this->audios+HAPPYSONG), "data/ld22_happy_final.dat", 1);
	loadAudio((this->audios+HITSFX), "data/hit.dat", 0);
	loadAudio((this->audios+FRIENDSFX), "data/friend.dat", 0);
	
	this->error = 0;
}

Data::~Data() {
	int i;
	
	i = -1;
	while (++i < MESHCOUNT)
		if (this->meshes[i])
			delete this->meshes[i];
	i = -1;
	while (++i < TEXCOUNT)
		if (this->textures[i])
			delete this->textures[i];
	i = -1;
	while (++i < TILECOUNT)
		if (this->tiles[i])
			delete this->tiles[i];
	i = -1;
	while (++i < BUFFERCOUNT)
		if (this->buffers[i])
			delete this->buffers[i];
	i = -1;
	while (++i < AUDIOCOUNT)
		if (this->audios[i])
			delete this->audios[i];
}

int Data::getError() {
	if (!Data::self)
		return -1;
	return Data::self->error;
}

CppOGL::Mesh* Data::getMesh(int index) {
	if (!Data::self || index >= MESHCOUNT)
		return NULL;
	return Data::self->meshes[index];
}

CppOGL::Texture* Data::getTexture(int index) {
	if (!Data::self || index >= TEXCOUNT)
		return NULL;
	return Data::self->textures[index];
}

CppOGL::Tile* Data::getTile(int index) {
	if (!Data::self || index >= TILECOUNT)
		return NULL;
	return Data::self->tiles[index];
}

CppOGL::Audio* Data::getAudio(int index) {
	if (!Data::self || index >= AUDIOCOUNT)
		return NULL;
	return Data::self->audios[index];
}

int Data::checkFile(const char *fileName) {
	FILE *f = fopen(fileName, "rb");
	if (!f) {
		printf("File not found: %s\n", fileName);
		return 0;
	}
	fclose(f);
	return 1;
}

int Data::checkFiles() {
	int res = 0;
	
	res |= this->checkFile("data/atlas.dat");
	res |= this->checkFile("data/ld22_menu.dat");
	res |= this->checkFile("data/ld22_alone_final.dat");
	res |= this->checkFile("data/ld22_normal_final.dat");
	res |= this->checkFile("data/ld22_happy_final.dat");
	res |= this->checkFile("data/hit.dat");
	res |= this->checkFile("data/friend.dat");
	
	return res;
}
