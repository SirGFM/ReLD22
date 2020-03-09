#include <core/buffer.h>

CppOGL::Buffer::Buffer(const float *data, int NumVertices) {
	glGenBuffers(1, &(this->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*NumVertices, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CppOGL::Buffer::~Buffer() {
	glDeleteBuffers(1, &(this->vbo));
}

void CppOGL::Buffer::use() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}
