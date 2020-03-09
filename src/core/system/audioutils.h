#ifndef __AUDIOUTILS_H
#define __AUDIOUTILS_H

namespace CppOGL {
	class Audio;
	class AudioLL;
	
	namespace AudioUtils {
		extern int init();
		extern void clear();
		
		extern float songVolume;
		extern float sfxVolume;
		
		extern int push(Audio *audio);
		extern void stop(int id);
		
		extern AudioLL* getAudioReference(int id);
	};
}

#endif
