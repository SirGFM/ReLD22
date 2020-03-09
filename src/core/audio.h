#ifndef __AUDIO_H
#define __AUDIO_H

#include <SDL/SDL.h>

namespace CppOGL {
	class Audio {
		public:
			Uint8 *buffer;
			Uint32 len;
			//Uint32 samples;
			int looped;
		public:
			Audio(Uint8 *Buffer, int len, int Looped);
			~Audio();
			
			int play();
			
			int mix(Uint8 *dst, int length, int *pos, float volume);
			int mixSS16LSB(Uint8 *dst, int i, int pos, float volume);
		public:
			static void unpause(int id);
			static void pause(int id);
			static void stop(int id);
	};
}

#endif
