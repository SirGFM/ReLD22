#ifndef __FRIEND_H
#define __FRIEND_H

#include <core/sprite.h>

enum {
	WANDER = 0,
	FOLLOW,
	RUN
};

enum {	
	RED = 0,
	GREEN,
	BLUE
};

class Friend : public CppOGL::Sprite {
	private:
		float timer;
		int color;
		int state;
		int befriended;
	public:
		Friend();
		
		void update();
		void revive();
		void kill();
	private:
		void rndVelocity();
		void rndTimer();
		void isOutScreen();
		void befriend();
		void unbefriend();
	public:
		void runway();
		void switchState(int State);
};

#endif
