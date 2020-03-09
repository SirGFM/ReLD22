#ifndef __BUTTON_H
#define __BUTTON_H

#include <core/sprite.h>
namespace CppOGL {
	class Text;
	class Callback;
	
	enum {
		BTNONE,
		BTOVER,
		BTPRES,
		BTMAX
	};
	
	class Button : public Sprite {
		private:
			Callback *cb;
			int mouseState;
		public:
			Text *label;
		public:
			Button(char *Label, Callback *const CB);
			~Button();
			
			void update();
			void draw();
	};
}

#endif
