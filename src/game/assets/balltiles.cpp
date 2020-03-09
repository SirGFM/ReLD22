#include <core/buffer.h>
#include <core/tile.h>
#include <core/texture.h>
#include "balltiles.h"

void balltiles(CppOGL::Buffer **buffer, CppOGL::Tile *tiles[], CppOGL::Texture *tex) {
	const float data[] = {0.0f, 0.0f, 0.0f, 0.062500f, 0.031250f, 0.062500f, 0.031250f, 0.0f};
	(*buffer) = new CppOGL::Buffer(data, 4);
	CppOGL::Buffer *buf = *buffer;
	tiles[12] = new CppOGL::Tile(buf, tex, 0.000000f, 0.500000f);
	tiles[13] = new CppOGL::Tile(buf, tex, 0.031250f, 0.500000f);
	tiles[14] = new CppOGL::Tile(buf, tex, 0.062500f, 0.500000f);
}
