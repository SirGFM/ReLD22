#ifndef __PLAYER_H
#define __PLAYER_H

#include <core/sprite.h>

enum {
	PLHAPPY = 0,
	PLNORM,
	PLSAD,
	PLHAPPYST,
	PLNORMST,
	PLSADST,
};

class Player : public CppOGL::Sprite {
	public:
		Player();
		
		void update();
};

#endif
