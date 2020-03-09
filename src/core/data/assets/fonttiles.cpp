#include <core/buffer.h>
#include <core/tile.h>
#include <core/texture.h>
#include "fonttiles.h"

using namespace CppOGL;

void CppOGL::fonttiles(Buffer **buffer, Tile *tiles[], Texture *tex) {
	const float data[] = {0.0f, 0.0f, 0.0f, 0.125000f, 0.125000f, 0.125000f, 0.125000f, 0.0f};
	(*buffer) = new Buffer(data, 4);
	Buffer *buf = *buffer;
	tiles[0] = new Tile(buf, tex, 0.000000f, 0.000000f);
	tiles[1] = new Tile(buf, tex, 0.125000f, 0.000000f);
	tiles[2] = new Tile(buf, tex, 0.250000f, 0.000000f);
	tiles[3] = new Tile(buf, tex, 0.375000f, 0.000000f);
	tiles[4] = new Tile(buf, tex, 0.500000f, 0.000000f);
	tiles[5] = new Tile(buf, tex, 0.625000f, 0.000000f);
	tiles[6] = new Tile(buf, tex, 0.750000f, 0.000000f);
	tiles[7] = new Tile(buf, tex, 0.875000f, 0.000000f);
	tiles[8] = new Tile(buf, tex, 0.000000f, 0.125000f);
	tiles[9] = new Tile(buf, tex, 0.125000f, 0.125000f);
	tiles[10] = new Tile(buf, tex, 0.250000f, 0.125000f);
	tiles[11] = new Tile(buf, tex, 0.375000f, 0.125000f);
	tiles[12] = new Tile(buf, tex, 0.500000f, 0.125000f);
	tiles[13] = new Tile(buf, tex, 0.625000f, 0.125000f);
	tiles[14] = new Tile(buf, tex, 0.750000f, 0.125000f);
	tiles[15] = new Tile(buf, tex, 0.875000f, 0.125000f);
	tiles[16] = new Tile(buf, tex, 0.000000f, 0.250000f);
	tiles[17] = new Tile(buf, tex, 0.125000f, 0.250000f);
	tiles[18] = new Tile(buf, tex, 0.250000f, 0.250000f);
	tiles[19] = new Tile(buf, tex, 0.375000f, 0.250000f);
	tiles[20] = new Tile(buf, tex, 0.500000f, 0.250000f);
	tiles[21] = new Tile(buf, tex, 0.625000f, 0.250000f);
	tiles[22] = new Tile(buf, tex, 0.750000f, 0.250000f);
	tiles[23] = new Tile(buf, tex, 0.875000f, 0.250000f);
	tiles[24] = new Tile(buf, tex, 0.000000f, 0.375000f);
	tiles[25] = new Tile(buf, tex, 0.125000f, 0.375000f);
	tiles[26] = new Tile(buf, tex, 0.250000f, 0.375000f);
	tiles[27] = new Tile(buf, tex, 0.375000f, 0.375000f);
	tiles[28] = new Tile(buf, tex, 0.500000f, 0.375000f);
	tiles[29] = new Tile(buf, tex, 0.625000f, 0.375000f);
	tiles[30] = new Tile(buf, tex, 0.750000f, 0.375000f);
	tiles[31] = new Tile(buf, tex, 0.875000f, 0.375000f);
	tiles[32] = new Tile(buf, tex, 0.000000f, 0.500000f);
	tiles[33] = new Tile(buf, tex, 0.125000f, 0.500000f);
	tiles[34] = new Tile(buf, tex, 0.250000f, 0.500000f);
	tiles[35] = new Tile(buf, tex, 0.375000f, 0.500000f);
	tiles[36] = new Tile(buf, tex, 0.500000f, 0.500000f);
	tiles[37] = new Tile(buf, tex, 0.625000f, 0.500000f);
	tiles[38] = new Tile(buf, tex, 0.750000f, 0.500000f);
	tiles[39] = new Tile(buf, tex, 0.875000f, 0.500000f);
	tiles[40] = new Tile(buf, tex, 0.000000f, 0.625000f);
	tiles[41] = new Tile(buf, tex, 0.125000f, 0.625000f);
	tiles[42] = new Tile(buf, tex, 0.250000f, 0.625000f);
	tiles[43] = new Tile(buf, tex, 0.375000f, 0.625000f);
	tiles[44] = new Tile(buf, tex, 0.500000f, 0.625000f);
	tiles[45] = new Tile(buf, tex, 0.625000f, 0.625000f);
	tiles[46] = new Tile(buf, tex, 0.750000f, 0.625000f);
	tiles[47] = new Tile(buf, tex, 0.875000f, 0.625000f);
	tiles[48] = new Tile(buf, tex, 0.000000f, 0.750000f);
	tiles[49] = new Tile(buf, tex, 0.125000f, 0.750000f);
	tiles[50] = new Tile(buf, tex, 0.250000f, 0.750000f);
	tiles[51] = new Tile(buf, tex, 0.375000f, 0.750000f);
	tiles[52] = new Tile(buf, tex, 0.500000f, 0.750000f);
	tiles[53] = new Tile(buf, tex, 0.625000f, 0.750000f);
	tiles[54] = new Tile(buf, tex, 0.750000f, 0.750000f);
	tiles[55] = new Tile(buf, tex, 0.875000f, 0.750000f);
	tiles[56] = new Tile(buf, tex, 0.000000f, 0.875000f);
	tiles[57] = new Tile(buf, tex, 0.125000f, 0.875000f);
	tiles[58] = new Tile(buf, tex, 0.250000f, 0.875000f);
	tiles[59] = new Tile(buf, tex, 0.375000f, 0.875000f);
	tiles[60] = new Tile(buf, tex, 0.500000f, 0.875000f);
	tiles[61] = new Tile(buf, tex, 0.625000f, 0.875000f);
	tiles[62] = new Tile(buf, tex, 0.750000f, 0.875000f);
	tiles[63] = new Tile(buf, tex, 0.875000f, 0.875000f);
}
