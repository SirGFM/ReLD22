#ifndef __SCENE_H
#define __SCENE_H

#include <core/group.hpp>

namespace CppOGL {
	class Scene : public Group {
		public:
			Scene();
			
			virtual void create();
	};
}

#endif
