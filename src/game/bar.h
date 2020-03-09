#ifndef __BAR_H
#define __BAR_H

#include <core/sprite.h>

class Bar : public CppOGL::Sprite {
	private:
		int max;
		int cur;
		int updated;
	public:
		Bar(int Max);
		~Bar();
		
		void draw();
		
		void setval(int val);
};

#endif
