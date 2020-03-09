#include <cstdio>
#include <SDL/SDL.h>
#include <core/audio.h>
#include <core/system/audioll.h>
#include <core/system/audioutils.h>

#define ALLOWLOCKING

/********************************************
 *  PRIVATE FUNCTIONS FORWARD DECLARATIONS  *
 ********************************************/

/**
 * SDL's callback for filling the audio buffer.
 */
void fillAudio(void *udata, Uint8 *stream, int len);
/**
 * Return a recycled AudioLL or a newly instantiated one.
 */
CppOGL::AudioLL* getAudio(CppOGL::Audio *audio);

/*************************
 *  NAMESPACE VARIABLES  *
 *************************/

/**
 * Loudness of the song. (defaults to 0.75)
 */
float CppOGL::AudioUtils::songVolume = 0.75;
/**
 * Loudness of the every sfx (their volume are normalized to this). (defaults to 0.25)
 */
float CppOGL::AudioUtils::sfxVolume = 0.25;

/***********************
 *  PRIVATE VARIABLES  *
 ***********************/

/**
 * The audio specifications gotten from SDL.
 */
SDL_AudioSpec specs;
/**
 * Currently playing song (looped, louder(?) audio).
 */
CppOGL::Audio *song = 0;
/**
 * List of sound effects currently being played.
 */
CppOGL::AudioLL *sfxs = 0;
/**
 * List of "deleted" sounds effects. Used to minimize instantiation.
 */
CppOGL::AudioLL *sfxsrecycle = 0;
int bytesPerSample = 0;
extern int _running;

/*************************
 *  NAMESPACE FUNCTIONS  *
 *************************/

/**
 * Initialize the audio unit.
 * TODO: customizable!
 */
int CppOGL::AudioUtils::init() {
	SDL_AudioSpec wanted;
	
	wanted.freq = 44100;
	wanted.format = AUDIO_S16LSB;
	wanted.channels = 2;
	wanted.samples = 1024;
	wanted.callback = fillAudio;
	wanted.userdata = 0;
	
	if (SDL_OpenAudio(&wanted, &specs) < 0) {
		printf("Error opening audio: %s\n", SDL_GetError());
		return 0;
	}
	
	bytesPerSample = specs.channels;
	if (!(specs.format == AUDIO_U8 && specs.format == AUDIO_S8))
		bytesPerSample *= 2;
	
	printf("-----------------------------\n");
	printf("Audio info:\n");
	printf("  Frequency: %i\n", specs.freq);
	printf("  Format: ");
	if (specs.format == AUDIO_S16LSB)
		printf("signed 16 bits little endian");
	printf("\n  Channels: %i\n", specs.channels);
	printf("  Samples: %i\n", specs.samples);
	printf("  Bytes per sample: %i\n", bytesPerSample);
	printf("-----------------------------\n");
	
	song = NULL;
	sfxs = NULL;
	return 1;
}

/**
 * Close the audio unit and clear allocated memory.
 */
void CppOGL::AudioUtils::clear() {
	SDL_PauseAudio(1);
	SDL_CloseAudio();
	
	CppOGL::AudioLL *tmp = sfxs;
	CppOGL::AudioLL *tmp2;
	while (tmp) {
		tmp2 = tmp->next;
		delete tmp;
		tmp = tmp2;
	}
	tmp = sfxsrecycle;
	while (tmp) {
		tmp2 = tmp->next;
		delete tmp;
		tmp = tmp2;
	}
}

/**
 * Push a new sfx to the list of currently playing ones.
 */
int CppOGL::AudioUtils::push(CppOGL::Audio *audio) {
	int id;
	if (!audio)
		return -1;
	#ifdef ALLOWLOCKING
		SDL_LockAudio();
	#endif
	if (!sfxs) {
		sfxs = getAudio(audio);
		id = sfxs->id;
	}
	else {
		CppOGL::AudioLL *tmp = getAudio(audio);
		sfxs->push(tmp);
		id = tmp->id;
	}
	#ifdef ALLOWLOCKING
		SDL_UnlockAudio();
	#endif
	SDL_PauseAudio(0);
	return id;
}

/**
 * Remove a sfx from the list of currently playing ones.
 */
void CppOGL::AudioUtils::stop(int id) {
	#ifdef ALLOWLOCKING
		SDL_LockAudio();
	#endif
	CppOGL::AudioLL *tmp = sfxs;
	if (tmp->id == id)
		sfxs = tmp->next;
	else {
		while (tmp->next && tmp->next->id != id)
			tmp = tmp->next;
		if (!tmp->next)
			return;
		CppOGL::AudioLL *tmp2 = tmp->next;
		tmp->next = tmp2->next;
		tmp = tmp2;
	}
	if (sfxsrecycle)
		sfxsrecycle->push(tmp);
	else
		sfxsrecycle = tmp;
	tmp->clear();
	#ifdef ALLOWLOCKING
		SDL_UnlockAudio();
	#endif
}

CppOGL::AudioLL* CppOGL::AudioUtils::getAudioReference(int id) {
	CppOGL::AudioLL *tmp = sfxs;
	if (sfxs->id == id)
		return sfxs;
	while (tmp->next && tmp->next->id != id)
		tmp = tmp->next;
	if (!tmp->next)
		return 0;
	return tmp->next;
}

/***********************
 *  PRIVATE FUNCTIONS  *
 ***********************/

/**
 * Return a recycled AudioLL or a newly instantiated one.
 */
CppOGL::AudioLL* getAudio(CppOGL::Audio *audio) {
	if (!sfxsrecycle)
		return new CppOGL::AudioLL(audio);
	CppOGL::AudioLL *tmp = sfxsrecycle;
	sfxsrecycle = sfxsrecycle->next;
	tmp->reuse(audio);
	return tmp;
}

/**
 * SDL's callback for filling the audio buffer.
 */
void fillAudio(void *udata, Uint8 *stream, int len) {
	// if no sound is playing, halt audio unit
	if (!(_running && (song || sfxs))) {
		SDL_PauseAudio(1);
		return;
	}
	
	len /= bytesPerSample;
	
	CppOGL::AudioLL *prev = 0;
	CppOGL::AudioLL *tmp = sfxs;
	// else, loop through every sound and mix it together
	while (tmp) {
		// mix current sound into the buffer
		int playing = tmp->self->mix(stream, len, &(tmp->pos), tmp->volume*CppOGL::AudioUtils::sfxVolume / CppOGL::AudioLL::num);
		// if it stopped
		if (!playing) {
			// add it to the recycled list
			if (!sfxsrecycle)
				sfxsrecycle = tmp;
			else
				sfxsrecycle->push(tmp);
			// and remove it from the sounds list
			if (!prev) {
				sfxs = tmp->next;
				tmp->clear();
				tmp = sfxs;
			}
			else {
				prev->next = tmp->next;
				tmp->clear();
				tmp = prev->next;
			}
			continue;
		}
		// get the next sound
		prev = tmp;
		tmp = prev->next;
	}
}
