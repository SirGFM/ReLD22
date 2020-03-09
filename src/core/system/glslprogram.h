#ifndef __GLSLPROGRAM_H
#define __GLSLPROGRAM_H

#include <GL/glew.h>

namespace CppOGL {
	struct uniform {
		int type;
	};
	
	class GLSLProgram {
		private:
			GLuint program;
			int error;
			GLuint *uniforms;
			int nUniforms;
		public:
			GLSLProgram(GLenum shaderTypes[], const char *shaders[], int NUniforms);
			virtual ~GLSLProgram();
		public:
			void createUniform(int index, const char *name);
		public:
			int getError();
			void use();
			void setInt(int index, int val);
			void setFloat(int index, float val);
			void set2f(int index, float x, float y);
			void set3f(int index, float x, float y, float z);
			void set4fv(int index, const GLfloat *val);
			void setm3fv(int index, const GLfloat *val);
			void setm4fv(int index, const GLfloat *val);
			GLuint getUniform(int index);
	};
}

#endif
