#include <SDL/SDL.h>
#include <core/system/customevents.h>
#include <core/timer.h>

SDL_Event _timerEvent;
SDL_TimerID _timer = 0;

int CppOGL::Timer::fps = 0;
int CppOGL::Timer::timerInterval = 0;
float CppOGL::Timer::elapsed = 0.0f;

int CppOGL::Timer::step = 0;
int CppOGL::Timer::lostFrames = 0;
int CppOGL::Timer::ignoreTimer = 0;


Uint32 timerCallback(Uint32 interval, void *param) {
	if (!(CppOGL::Timer::ignoreTimer || CppOGL::Timer::step))
		SDL_PushEvent(&_timerEvent);
	return CppOGL::Timer::timerInterval;
}

int CppOGL::Timer::init(int FPS) {
	CppOGL::Timer::fps = FPS;
	CppOGL::Timer::timerInterval = 1000 / FPS;
	CppOGL::Timer::elapsed = 1.0f / FPS;
	if (_timer)
		return 1;
	
	if (!(_timer = SDL_AddTimer(CppOGL::Timer::timerInterval, timerCallback, NULL))) {
		fprintf(stderr, "Error initializing timer: %s.\n", SDL_GetError());
		return 0;
	}
	
	_timerEvent.type = SDL_USEREVENT;
	_timerEvent.user.code = CppOGL::GETTIMER;
	_timerEvent.user.data1 = 0;
	_timerEvent.user.data2 = 0;
	
	return 1;
}

void CppOGL::Timer::clear() {
	SDL_RemoveTimer(_timer);
}
