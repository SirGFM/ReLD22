#ifndef __GAMEOVERWND_H
#define __GAMEOVERWND_H

#include <core/group.hpp>
namespace CppOGL {
	class Sprite;
	class Text;
}

class GameOverWindow : public CppOGL::Group {
	private:
		CppOGL::Sprite *bg;
		CppOGL::Text *t;
	public:
		GameOverWindow();
		~GameOverWindow();
		
		void draw();
		void restart(int score, int highscore);
};

#endif
