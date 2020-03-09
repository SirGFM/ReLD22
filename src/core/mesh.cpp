#include <core/buffer.h>
#include <core/mesh.h>

CppOGL::Mesh::Mesh(CppOGL::Buffer *_Buffer, const GLshort *indices, int NumTriangles) {
	// Create this mesh's vertex buffer object
	this->buffer = _Buffer;
	
	// Create this mesh's index buffer object
	glGenBuffers(1, &(this->ibo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort)*3*NumTriangles, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	this->numTriangles = NumTriangles;
}

CppOGL::Mesh::~Mesh() {
	this->buffer = 0;	
	glDeleteBuffers(1, &(this->ibo));
}

void CppOGL::Mesh::associate() {
	this->buffer->use();	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
}

void CppOGL::Mesh::render() {
	glDrawElements(GL_TRIANGLES, 3*this->numTriangles, GL_UNSIGNED_SHORT, 0);
}
