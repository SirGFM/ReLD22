#include <GL/glew.h>
#include <core/utils.h>
#include <core/system/glslprogram.h>

CppOGL::GLSLProgram::GLSLProgram(GLenum shaderTypes[], const char *shaders[], int NUniforms) {
	this->program = CppOGL::Utils::createProgram(shaderTypes, shaders);
	this->nUniforms = NUniforms;
	this->uniforms = new GLuint[NUniforms];
}

CppOGL::GLSLProgram::~GLSLProgram() {
	if (this->uniforms)
		delete[] this->uniforms;
	glDeleteProgram(this->program);
}

void CppOGL::GLSLProgram::createUniform(int index, const char *name) {
	if (index > this->nUniforms)
		return;
	this->use();
	this->uniforms[index] = glGetUniformLocation(this->program, name);
	glUseProgram(0);
}

int CppOGL::GLSLProgram::getError() {
	return this->error;
}

void CppOGL::GLSLProgram::use() {
	glUseProgram(this->program);
}

void CppOGL::GLSLProgram::setInt(int index, int val) {
	glUniform1i(this->uniforms[index], val);
}

void CppOGL::GLSLProgram::setFloat(int index, float val) {
	glUniform1f(this->uniforms[index], val);
}

void CppOGL::GLSLProgram::set2f(int index, float x, float y) {
	glUniform2f(this->uniforms[index], x, y);
}

void CppOGL::GLSLProgram::set3f(int index, float x, float y, float z) {
	glUniform3f(this->uniforms[index], x, y, z);
}

void CppOGL::GLSLProgram::set4fv(int index, const GLfloat *val) {
	glUniform4fv(this->uniforms[index], 1, val);
}

void CppOGL::GLSLProgram::setm3fv(int index, const GLfloat *val) {
	glUniformMatrix3fv(this->uniforms[index], 1, GL_FALSE, val);
}

void CppOGL::GLSLProgram::setm4fv(int index, const GLfloat *val) {
	glUniformMatrix4fv(this->uniforms[index], 1, GL_FALSE, val);
}

GLuint CppOGL::GLSLProgram::getUniform(int index) {
	if (index > this->nUniforms)
		return 0;
	return this->uniforms[index];
}
