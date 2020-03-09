#ifndef __ENEMY_H
#define __ENEMY_H

#include <core/sprite.h>

class Enemy : public CppOGL::Sprite {
	private:
		float timer;
		int moveCount;
	public:
		Enemy();
		
		void update();
		void revive();
	private:
		void seekRandomPos();
};

#endif
