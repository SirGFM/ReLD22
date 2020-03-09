#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>
#include <core/utils.h>

#define PI 3.141596
#define angtorad	PI / 180.0f

unsigned int _seed;
float coslt[91];
float sinlt[91];

GLuint CppOGL::Utils::createProgram(GLenum shaderTypes[], const char *shaders[]) {
	GLuint *shaderList;
	GLuint program;
	int i = 0;
	int c = 0;
	while (1)
		if (!shaders[i++])
			break;
		else
			c++;
	
	shaderList = new GLuint[c];
	i = 0;
	while (i < c) {
		const char *shader = shaders[i];
		GLenum type = shaderTypes[i];
		
		shaderList[i++] = CppOGL::Utils::createShader(type, shader);
	}
	
	program = glCreateProgram();
	i = 0;
	while (i < c)
		glAttachShader(program, shaderList[i++]);
	
	glLinkProgram(program);
	
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength+1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
	
	i = 0;
	while (i < c) {
		GLuint shader = shaderList[i++];
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}
	
	delete[] shaderList;
	return program;
}

GLuint CppOGL::Utils::createShader(GLenum eShaderType, const char *strShaderFile) {
	GLuint shader = glCreateShader(eShaderType);
	glShaderSource(shader, 1, &strShaderFile, NULL);
	
	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		
		const char *strShaderType = NULL;
		switch (eShaderType) {
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			//case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}
		
		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	
	return shader;
}

// Random stuff

inline int stdrand() {
	return rand();
}

unsigned int CppOGL::Utils::getSeed() {
	return _seed;
}

void CppOGL::Utils::setSeed(unsigned int seed) {
	_seed = seed;
}

#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define RAND_MAX 0xffffffff

float CppOGL::Utils::frand() {
	return CppOGL::Utils::rand() / ((float)RAND_MAX);
	//return stdrand() / ((float)RAND_MAX);
}

unsigned int CppOGL::Utils::rand() {
	long int tmp = _seed;
	tmp *= 0x19660d;
	tmp += 0x3c6ef35f;
	_seed = tmp;
	return _seed;
	//return stdrand();
}

// Angle stuff

inline float stdcos(float ang) { return cos(ang*angtorad); }
inline float stdsin(float ang) { return sin(ang*angtorad); }

void CppOGL::Utils::createLookupTable() {
	int i = 0;
	while (i < 45) {
		coslt[i] = stdcos(i);
		sinlt[i] = stdsin(i);
		coslt[90-i] = sinlt[i];
		sinlt[90-i] = coslt[i];
		i++;
	}
	coslt[i] = stdcos(i);
	sinlt[i] = coslt[i];
}

float CppOGL::Utils::cos(float ang) {
	int a = (int)ang;
	float sign = 1.0f;
	while (a < 0)
		a += 360;
	if (a >= 360)
		a %= 360;
	
	if (a > 270)
		a = 360 - a;
	else if (a > 180) {
		a -= 180;
		sign = -1.0f;
	}
	else if (a > 90) {
		a = 180 - a;
		sign = -1.0f;
	}
	return sign*coslt[a];
}

float CppOGL::Utils::sin(float ang) {
	int a = (int)ang;
	float sign = 1.0f;
	while (a < 0)
		a += 360;
	if (a >= 360)
		a %= 360;
	
	if (a > 270) {
		a = 360 - a;
		sign = -1.0f;
	}
	else if (a > 180) {
		a -= 180;
		sign = -1.0f;
	}
	else if (a > 90)
		a = 180 - a;
	return sign*sinlt[a];
}

// Math stuff

inline float stdfloor(float val) {
	return (float)floor((double)val);
}

float CppOGL::Utils::floor(float val) {
	return stdfloor(val);
}

inline int stdabs(int val) {
	return abs(val);
}

float CppOGL::Utils::abs(float val) {
	return fabs(val);
}

int CppOGL::Utils::abs(int val) {
	return stdabs(val);
}

inline float stdsqrt(float val) {
	return sqrt(val);
}

float CppOGL::Utils::sqrt(float val) {
	return stdsqrt(val);
}

float CppOGL::Utils::mod(float div, float quo) {
	return fmod(div, quo);
}
