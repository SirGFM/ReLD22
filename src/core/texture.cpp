#include <core/texture.h>
#include <core/game.h>

GLuint CppOGL::Texture::sampler;

CppOGL::Texture::Texture(int Width, int Height, char *data) {
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &(this->texId));
	glBindTexture(GL_TEXTURE_2D, this->texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

CppOGL::Texture::~Texture() {
	glDeleteTextures(1, &(this->texId));
}

void CppOGL::Texture::use() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texId);
	glBindSampler(CppOGL::Texture::sampler, GL_TEXTURE0);
}
