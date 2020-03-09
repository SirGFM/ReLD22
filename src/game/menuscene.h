#ifndef __MENUSCENE_H
#define __MENUSCENE_H

#include <core/scene.hpp>
namespace CppOGL {
	class AudioLL;
}

class Menuscene : public CppOGL::Scene {
	private:
		CppOGL::AudioLL *song;
	public:
		~Menuscene();
		void create();
};

#endif
