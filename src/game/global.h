#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <game/gamestate.h>
#include <game/introscene.h>
#include <game/player.h>
#include <game/bar.h>
#include <game/colorcamera.h>

namespace Global {
	extern int red;
	extern int maxred;
	extern int green;
	extern int maxgreen;
	extern int blue;
	extern int maxblue;
	extern int updatecolors;
	extern int restart;
	extern float health;
	extern Player *player;
	extern Gamestate *gamestate;
	extern Introscene *introscene;
	extern ColorCamera *cc;
	
	extern void init();
	extern void updateHealth();
};

#endif
