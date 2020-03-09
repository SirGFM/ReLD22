#include <cstdio>
#include <ctime>
#include <SDL/SDL.h>

#include <core/camera.h>
#include <core/keyboard.h>
#include <core/scene.hpp>
#include <core/pointer.h>
#include <core/timer.h>
#include <core/utils.h>
#include <core/data/coredata.h>
#include <core/system/audioutils.h>
#include <core/system/customevents.h>
#include <core/system/glslprogram.h>
#include <core/system/defaultprogram.h>

#include <core/game.h>

int createWindow(const char *name, const char *icon, unsigned char *mask);
int setupOpenGL(int width, int height, int zoom);
void updateMatrix();
void manageSwitchScene();
void manageEvents();
void loop();
void render();

SDL_Surface *_screen;
int _running;
Uint32 _lastTime;
Uint32 _acc;

FILE *ctt = 0;

CppOGL::Camera *CppOGL::Game::camera = 0;
CppOGL::Scene *CppOGL::Game::_curScene = 0;
CppOGL::Scene *_nextScene = 0;
int CppOGL::Game::screenwidth = 0;
int CppOGL::Game::screenheight = 0;

/******************************
 *  CppOGL::Keyboard imports  *
 ******************************/
extern int _didPress;
extern SDLKey _lastKey;

void CppOGL::Game::openConsole() {
	ctt = fopen("CON", "w" );
	freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
}

int CppOGL::Game::init(const char *name, const char *icon, unsigned char *mask, int Width, int Height, int Zoom, int FPS) {
	CppOGL::Game::screenwidth = Width * Zoom;
	CppOGL::Game::screenheight = Height * Zoom;
	
	if (!createWindow(name, icon, mask)) {
		printf("Exiting...\n");
		return 0;
	}
	if (!setupOpenGL(Width, Height, Zoom)) {
		printf("Exiting...\n");
		clear();
		return 0;
	}
	if (!AudioUtils::init()) {
		printf("Exiting...\n");
		clear();
		return 0;
	}
	CppOGL::CoreData::init();
	CppOGL::Keyboard::init(8);
	
	CppOGL::Utils::createLookupTable();
	CppOGL::Utils::setSeed(time(NULL));
	return 1;
}

int CppOGL::Game::run(CppOGL::Scene *scene) {
	if (!CppOGL::Timer::init(30)) {
		printf("Exiting...\n");
		clear();
		return 0;
	}
	
	_nextScene = scene;
	_running = 1;
	_acc = 0;
	
	while (_running) {
		manageSwitchScene();
		_didPress = 0;
		manageEvents();
		if (CppOGL::Timer::step)
			loop();
		CppOGL::Timer::step = 0;
	}
	
	return 1;
}

void CppOGL::Game::clear() {
	CppOGL::Timer::clear();
	CppOGL::AudioUtils::clear();
	if (CppOGL::Game::_curScene)
		delete CppOGL::Game::_curScene;
	CppOGL::Keyboard::clear();
	CppOGL::CoreData::clear();
	if (CppOGL::Game::camera)
		delete CppOGL::Game::camera;
	if (_screen)
		SDL_FreeSurface(_screen);
	SDL_Quit();
	if (ctt)
		fclose(ctt);
}

void CppOGL::Game::switchScene(CppOGL::Scene *scene) {
	_nextScene = scene;
}

int createWindow(const char *name, const char *icon, unsigned char *mask) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
		fprintf(stdout, "Error initializing SDL: %s.\n", SDL_GetError());
		return 0;
	}
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	if (icon)
		SDL_WM_SetIcon(SDL_LoadBMP(icon), mask);
	
	if (!(_screen = SDL_SetVideoMode(CppOGL::Game::screenwidth, CppOGL::Game::screenheight, 16, SDL_OPENGL))) {
		fprintf(stdout, "Error initializing video: %s.\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}
	
	SDL_WM_SetCaption(name, NULL);
	
	return 1;
}

int setupOpenGL(int width, int height, int zoom) {
	glClearColor(0, 0, 0, 0);
	
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 0;
	}
	
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	CppOGL::Game::camera = new CppOGL::Camera(0, 0, width, height, zoom, zoom);
	
	printf("OpenGL version supported by this platform (%s)\n", glGetString(GL_VERSION));
	return 1;
}

void manageSwitchScene() {
	if (_nextScene) {
		if (CppOGL::Game::_curScene)
			delete CppOGL::Game::_curScene;
		CppOGL::Game::_curScene = _nextScene;
		_nextScene = 0;
		CppOGL::Game::_curScene->create();
	}
}

void manageEvents() {
	SDL_Event ev;
	if (!SDL_WaitEvent(&ev)) {
		fprintf(stderr, "Error waiting for events: %s\n.", SDL_GetError());
		return;
	}
	while (1) {
		switch (ev.type) {
			/**/
			case SDL_KEYDOWN: {
				_lastKey = ev.key.keysym.sym;
				_didPress = 1;
				CppOGL::Keyboard::setKey(_lastKey, 1);
			}break;
			case SDL_KEYUP: {
				_lastKey = ev.key.keysym.sym;
				_didPress = 1;
				CppOGL::Keyboard::setKey(_lastKey, 0);
			}break;
			/**/
			case SDL_MOUSEMOTION: {
				CppOGL::Pointer::x = ev.motion.x / ((int)CppOGL::Game::camera->scaleX);
				CppOGL::Pointer::y = ev.motion.y / ((int)CppOGL::Game::camera->scaleY);
				CppOGL::Pointer::dx = ev.motion.xrel / ((int)CppOGL::Game::camera->scaleX);
				CppOGL::Pointer::dy = ev.motion.yrel / ((int)CppOGL::Game::camera->scaleY);
			} break;
			case SDL_MOUSEBUTTONDOWN: {
				if (ev.button.button == SDL_BUTTON_LEFT)
					CppOGL::Pointer::left = 1;
				else if (ev.button.button == SDL_BUTTON_MIDDLE)
					CppOGL::Pointer::middle = 1;
				else if (ev.button.button == SDL_BUTTON_RIGHT)
					CppOGL::Pointer::right = 1;
			} break;
			case SDL_MOUSEBUTTONUP: {
				if (ev.button.button == SDL_BUTTON_LEFT)
					CppOGL::Pointer::left = 0;
				else if (ev.button.button == SDL_BUTTON_MIDDLE)
					CppOGL::Pointer::middle = 0;
				else if (ev.button.button == SDL_BUTTON_RIGHT)
					CppOGL::Pointer::right = 0;
			} break;
			case SDL_USEREVENT: {
				if (ev.user.code == CppOGL::GETTIMER)
					if (CppOGL::Timer::step == 0) {
						CppOGL::Timer::step = 1;
						CppOGL::Timer::lostFrames = 0;
					}
					else
						CppOGL::Timer::lostFrames++;
			} break;
			case SDL_QUIT: {
				_running = 0;
			} break;
			default: ;
		}
		if (!SDL_PollEvent(&ev))
			break;
	}
}

void loop() {
	// start drawing
	render();
	
	Uint32 curTime = SDL_GetTicks();
	Uint32 frameTime = curTime - _lastTime;
	_lastTime = curTime;
	
	if (frameTime > 250)
		frameTime = 250;
	_acc += frameTime;
	
	while (_acc > CppOGL::Timer::timerInterval) {
		// update
		CppOGL::Game::_curScene->update();
		_acc -= CppOGL::Timer::timerInterval;
	}
}

void render() {
	CppOGL::Game::camera->start();
	CppOGL::Game::_curScene->draw();
	CppOGL::Game::camera->postProcess();
	
	glUseProgram(0);
	SDL_GL_SwapBuffers();
}
