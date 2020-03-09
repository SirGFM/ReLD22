#ifndef __BUFFER_H
#define __BUFFER_H

#include <GL/glew.h>

namespace CppOGL {
	class Buffer {
		private:
			GLuint vbo;
		public:
			Buffer(const float *data, int NumVertices);
			~Buffer();
			
			void use();
	};
}

#endif
