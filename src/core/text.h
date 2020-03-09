#ifndef __TEXT_H
#define __TEXT_H

#include <core/basic.h>
namespace CppOGL {
	class Sprite;
	
	class Text : public Basic {
		private:
			char *text;
			int len;
			Sprite *spr;
		public:
			float x;
			float y;
			int width;
		public:
			Text();
			virtual ~Text();
			
			void update();
			void draw();
			
			void setBlank(int Length, int Width);
			void setText(const char *Text, int Width);
			void updateText(const char *Text);
			void updateChar(int index, char c);
			void writeInt(int index, int digits, int val, int zerofill);
		private:
			char getChar(char c);
	};
}

#endif
