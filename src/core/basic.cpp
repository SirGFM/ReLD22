#include <core/callback.h>
#include <core/basic.h>

CppOGL::Basic::Basic() {
	this->exists = 1;
	this->active = 1;
	this->visible = 1;
	this->id = 0;
	this->overlapable = 1;
}

CppOGL::Basic::~Basic() {}

void CppOGL::Basic::kill() {
	this->exists = 0;
}

void CppOGL::Basic::revive() {
	this->exists = 1;
}

int CppOGL::Basic::overlaps(CppOGL::Basic *b, CppOGL::Callback *const callback) {
	return 0;
}
