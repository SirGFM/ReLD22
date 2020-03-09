#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include <core/scene.hpp>

namespace CppOGL {
	class AudioLL;
	class Text;
}
class Bar;
class GameOverWindow;

class Gamestate : public CppOGL::Scene {
	private:
		int gameover;
		int score;
		float timer;
		Bar *bar;
		CppOGL::Text *scoreText;
		CppOGL::AudioLL *sad;
		CppOGL::AudioLL *norm;
		CppOGL::AudioLL *happy;
		GameOverWindow *gmw;
	public:
		virtual ~Gamestate();
		
		void create();
		void update();
		void draw();
		
		void plHit();
	private:
		void updateMusic(float h);
};

#endif
