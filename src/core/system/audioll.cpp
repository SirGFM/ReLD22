#include <core/audio.h>
#include <core/system/audioll.h>

int CppOGL::AudioLL::num = 0;
int CppOGL::AudioLL::nextID = 0;
CppOGL::AudioLL *CppOGL::AudioLL::pushAll = 0;

CppOGL::AudioLL::AudioLL(Audio *audio) {
	this->pos = 0;
	this->next = 0;
	this->volume = 1.0f;
	this->self = audio;
	this->id = CppOGL::AudioLL::nextID++;
	CppOGL::AudioLL::num++;
};

CppOGL::AudioLL::~AudioLL() {
	if (this->self)
		AudioLL::num--;
	this->self = 0;
	this->next = 0;
};

void CppOGL::AudioLL::reuse(Audio *audio) {
	this->next = 0;
	this->pos = 0;
	this->volume = 1.0f;
	this->self = audio;
	AudioLL::num++;
};

void CppOGL::AudioLL::clear() {
	this->next = 0;
	AudioLL::num--;
};

void CppOGL::AudioLL::push(AudioLL *all) {
	CppOGL::AudioLL::pushAll = all;
	this->pvpush();
	CppOGL::AudioLL::pushAll = 0;
}

void CppOGL::AudioLL::pvpush() {
	if (this->next)
		this->next->pvpush();
	else
		this->next = CppOGL::AudioLL::pushAll;
};
