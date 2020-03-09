#ifndef __gmwindow_H
#define __gmwindow_H

namespace CppOGL {
	class Buffer;
	class Tile;
	class Texture;
}

extern void gmwindow(CppOGL::Buffer **buffer, CppOGL::Tile *tiles[], CppOGL::Texture *tex);

#endif
