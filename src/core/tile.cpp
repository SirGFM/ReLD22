#include <core/buffer.h>
#include <core/camera.h>
#include <core/game.h>
#include <core/texture.h>
#include <core/tile.h>
#include <core/system/glslprogram.h>

int CppOGL::Tile::textureoffset;

CppOGL::Tile::Tile(CppOGL::Buffer *_Buffer, CppOGL::Texture *_Texture, float OffX, float OffY) {
	this->buffer = _Buffer;
	this->texture = _Texture;
	this->offx = OffX;
	this->offy = OffY;
}

CppOGL::Tile::~Tile() {
	this->buffer = 0;
}

void CppOGL::Tile::associate() {
	this->buffer->use();
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	this->texture->use();
}

void CppOGL::Tile::use() {
	this->buffer->use();
	CppOGL::Game::camera->setTextureOffset(this->offx, this->offy);
	//CppOGL::Game::shaderProgram->set2f(CppOGL::Tile::textureoffset, this->offx, this->offy);
	this->texture->use();
}
