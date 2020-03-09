#include <core/buffer.h>
#include <core/tile.h>
#include <core/texture.h>
#include "buttontiles.h"

void CppOGL::buttontiles(CppOGL::Buffer **buffer, CppOGL::Tile *tiles[], CppOGL::Texture *tex) {
	const float data[] = {0.0f, 0.0f, 0.0f, 0.250000f, 1.000000f, 0.250000f, 1.000000f, 0.0f};
	(*buffer) = new CppOGL::Buffer(data, 4);
	CppOGL::Buffer *buf = *buffer;
	tiles[64] = new CppOGL::Tile(buf, tex, 0.000000f, 0.000000f);
	tiles[65] = new CppOGL::Tile(buf, tex, 0.000000f, 0.250000f);
	tiles[66] = new CppOGL::Tile(buf, tex, 0.000000f, 0.500000f);
}
