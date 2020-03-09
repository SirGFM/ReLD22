#include <SDL/SDL.h>
#include <core/audio.h>
#include <core/system/audioutils.h>

extern int bytesPerSample;

CppOGL::Audio::Audio(Uint8 *Buffer, int Len, int Looped) {
	int i = -1;
	this->buffer = new Uint8[Len];
	while (++i < Len)
		this->buffer[i] = Buffer[i];	
	this->len = Len;
	this->looped = Looped;
}

CppOGL::Audio::~Audio() {
	delete[] this->buffer;
}

int CppOGL::Audio::play() {
	return CppOGL::AudioUtils::push(this);
}

int CppOGL::Audio::mix(Uint8 *dst, int length, int *pos, float volume) {
	int i = 0;
	int p = *pos;
	// read as many bytes from the buffer as the destination can handle
	while (i < length) {
		// mix each (stereo) sample into dst
		int mixed = this->mixSS16LSB(dst, i, p, volume);
		// and loop or stop this audio
		if (!mixed)
			if (this->looped)
				p = 0;
			else
				return 0;
		i++;
	}
	// otherwise, update the position and keep playing it
	(*pos) = p+i;
	return 1;
}

int CppOGL::Audio::mixSS16LSB(Uint8 *dst, int i, int pos, float volume) {
	i *= 4;
	pos *= 4;
	
	if (i+pos >= this->len)
		return 0;
	
	Sint16 chan1 = (this->buffer[i+pos]) | ((this->buffer[i+pos+1]<<8)&0xff00);
	Sint16 chan2 = (this->buffer[i+pos+2]) | ((this->buffer[i+pos+3]<<8)&0xff00);
	
	chan1 = (Sint16)(chan1*volume);
	chan2 = (Sint16)(chan2*volume);
	
	dst[i] += (Uint8)(chan1&0xff);
	dst[i+1] += (Uint8)((chan1>>8)&0xff);
	dst[i+2] += (Uint8)(chan2&0xff);
	dst[i+3] += (Uint8)((chan2>>8)&0xff);
	
	return 1;
}

void CppOGL::Audio::unpause(int id) {
	
}

void CppOGL::Audio::pause(int id) {
	
}

void CppOGL::Audio::stop(int id) {
	CppOGL::AudioUtils::stop(id);
}
