#include <core/game.h>
#include <core/timer.h>
#include <game/global.h>

int Global::maxred = 0;
int Global::red = 0;
int Global::maxgreen = 0;
int Global::green = 0;
int Global::maxblue = 0;
int Global::blue = 0;
int Global::updatecolors = 1;
int Global::restart = 0;
float Global::health = 12.5;

Player *Global::player = 0;
Gamestate *Global::gamestate = 0;
Introscene *Global::introscene = 0;
ColorCamera *Global::cc = 0;

void Global::init() {
	if (!Global::cc) {
		Global::cc = dynamic_cast<ColorCamera*>(CppOGL::Game::camera);
	}
	
	Global::maxred = 0;
	Global::red = 0;
	Global::maxgreen = 0;
	Global::green = 0;
	Global::maxblue = 0;
	Global::blue = 0;
	Global::updatecolors = 1;
	Global::restart = 0;
	Global::health = 12.5;
	
	Global::player = 0;
	Global::gamestate = 0;
	Global::introscene = 0;
}

void Global::updateHealth() {
	int n;
	float h;
	
	n = Global::red + Global::green + Global::blue;
	
	h = Global::health + 0.5f * n * CppOGL::Timer::elapsed;
	if (h < 25.0f) {
		float t = Global::maxred + Global::maxgreen + Global::maxblue;
		if (n == 0)
			h -= 1.5f * t * CppOGL::Timer::elapsed;
		else {
			t -= n;
			h -= t / n * CppOGL::Timer::elapsed;
		}
	}
	
	if (h > 100.0f)
		h = 100.0f;
	else if (h < 0.0f)
		h = 0.0f;
	
	Global::health = h;
}
