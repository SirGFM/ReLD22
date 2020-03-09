#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <SDL/SDL.h>

namespace CppOGL {
	namespace Keyboard {
		extern void init(int keyNum);
		extern void clear();
		
		extern void addKey(int key, SDLKey sym);
		extern void setKey(SDLKey sym, int val);
		extern int queryKey(int key);
		
		extern SDLKey lastKey();
		extern int gotKeyPress();
	}
}

#endif
