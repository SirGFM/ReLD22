#include <core/buffer.h>
#include <core/tile.h>
#include <core/texture.h>
#include "titletile.h"

void titletile(CppOGL::Buffer **buffer, CppOGL::Tile *tiles[], CppOGL::Texture *tex) {
	const float data[] = {0.0f, 0.0f, 0.0f, 0.250000f, 1.000000f, 0.250000f, 1.000000f, 0.0f};
	(*buffer) = new CppOGL::Buffer(data, 4);
	CppOGL::Buffer *buf = *buffer;
	tiles[16] = new CppOGL::Tile(buf, tex, 0.000000f, 0.750000f);
}
