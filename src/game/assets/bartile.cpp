#include <core/buffer.h>
#include <core/tile.h>
#include <core/texture.h>
#include "bartile.h"

void bartile(CppOGL::Buffer **buffer, CppOGL::Tile *tiles[], CppOGL::Texture *tex) {
	const float data[] = {0.0f, 0.0f, 0.0f, 0.125000f, 0.500000f, 0.125000f, 0.500000f, 0.0f};
	(*buffer) = new CppOGL::Buffer(data, 4);
	CppOGL::Buffer *buf = *buffer;
	tiles[15] = new CppOGL::Tile(buf, tex, 0.000000f, 0.625000f);
}
