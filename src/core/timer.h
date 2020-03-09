#ifndef __TIMER_H
#define __TIMER_H

namespace CppOGL {
	namespace Timer {
		extern int fps;
		extern int timerInterval;
		extern float elapsed;
		
		extern int step;
		extern int lostFrames;
		extern int ignoreTimer;
		
		extern int init(int FPS);
		extern void clear();
	}
}

#endif
