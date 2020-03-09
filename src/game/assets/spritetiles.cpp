#include <core/buffer.h>
#include <core/tile.h>
#include <core/texture.h>
#include "spritetiles.h"

void spritetiles(CppOGL::Buffer **buffer, CppOGL::Tile *tiles[], CppOGL::Texture *tex) {
	const float data[] = {0.0f, 0.0f, 0.0f, 0.250000f, 0.125000f, 0.250000f, 0.125000f, 0.0f};
	(*buffer) = new CppOGL::Buffer(data, 4);
	CppOGL::Buffer *buf = *buffer;
	tiles[0] = new CppOGL::Tile(buf, tex, 0.000000f, 0.000000f);
	tiles[1] = new CppOGL::Tile(buf, tex, 0.125000f, 0.000000f);
	tiles[2] = new CppOGL::Tile(buf, tex, 0.250000f, 0.000000f);
	tiles[3] = new CppOGL::Tile(buf, tex, 0.375000f, 0.000000f);
	tiles[4] = new CppOGL::Tile(buf, tex, 0.500000f, 0.000000f);
	tiles[5] = new CppOGL::Tile(buf, tex, 0.625000f, 0.000000f);
	tiles[6] = new CppOGL::Tile(buf, tex, 0.750000f, 0.000000f);
	tiles[7] = new CppOGL::Tile(buf, tex, 0.875000f, 0.000000f);
	tiles[8] = new CppOGL::Tile(buf, tex, 0.000000f, 0.250000f);
	tiles[9] = new CppOGL::Tile(buf, tex, 0.125000f, 0.250000f);
	tiles[10] = new CppOGL::Tile(buf, tex, 0.250000f, 0.250000f);
	tiles[11] = new CppOGL::Tile(buf, tex, 0.375000f, 0.250000f);
}
