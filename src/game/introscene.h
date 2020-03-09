#ifndef __INSTROSCENE_H
#define __INSTROSCENE_H

#include <core/scene.hpp>
namespace CppOGL {
	class Text;
}
class Bar;

class Introscene : public CppOGL::Scene {
	private:
		float timer;
		int i;
		int n;
		int len;
		const char *curTxt;
		CppOGL::Text *text;
		Bar *bar;
	public:
		Introscene();
		~Introscene();
		
		void update();
		void draw();
		
		void plHit();
	private:
		void setState();
};

#endif
