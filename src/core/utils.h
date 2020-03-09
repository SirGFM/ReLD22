#ifndef __UTILS_H
#define __UTILS_H

#include <GL/glew.h>

namespace CppOGL {
	namespace Utils {
		extern GLuint createProgram(GLenum shaderTypes[], const char *shaders[]);
		extern GLuint createShader(GLenum eShaderType, const char *strShaderFile);
		
		extern unsigned int getSeed();
		extern void setSeed(unsigned int seed);
		extern float frand();
		extern unsigned int rand();
		
		extern void createLookupTable();
		extern float cos(float ang);
		extern float sin(float ang);
		
		extern float floor(float val);
		extern float abs(float val);
		extern int abs(int val);
		extern float sqrt(float val);
		extern float mod(float div, float quo);
	};
}

#endif
