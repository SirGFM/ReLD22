#ifndef __DATA_H
#define __DATA_H

namespace CppOGL {
	class Mesh;
	class Texture;
	class Tile;
	class Buffer;
	class Audio;
}

enum {
	MESH32x32,
	MESH8x8,
	MESH128x16,
	MESH128x64,
	MESH256x32,
	MESHCOUNT
};

enum {
	TEXATLAS,
	TEXCOUNT
};

enum {
	HAPPY0,
	HAPPY1,
	HAPPY2,
	NORM0,
	NORM1,
	NORM2,
	SAD0,
	SAD1,
	SAD2,
	BADDY0,
	BADDY1,
	BADDY2,
	BRED,
	BGREEN,
	BBLUE,
	BAR,
	TITLE,
	GMWINDOW,
	TILECOUNT
};

enum {
	BUFF32x32 = 0,
	BUFF8x8,
	BUFF128x16,
	BUFF128x64,
	BUFF256x32,
	BUFFTILE32x32,
	BUFFTILE8x8,
	BUFFTILE128x16,
	BUFFTILE128x64,
	BUFFTILE256x32,
	BUFFERCOUNT
};

enum {
	MENUSONG,
	SADSONG,
	NORMSONG,
	HAPPYSONG,
	BTSFX,
	HITSFX,
	FRIENDSFX,
	AUDIOCOUNT
};

class Data {
	private:
		static Data *self;
	private:
		CppOGL::Mesh *meshes[MESHCOUNT];
		CppOGL::Texture *textures[TEXCOUNT];
		CppOGL::Tile *tiles[TILECOUNT];
		CppOGL::Buffer *buffers[BUFFERCOUNT];
		CppOGL::Audio *audios[AUDIOCOUNT];
		int error;
	
	private:
		Data();
	public:
		static int init();
		static void clear();
		~Data();
		
		static int getError();
		static CppOGL::Mesh *getMesh(int index);
		static CppOGL::Texture *getTexture(int index);
		static CppOGL::Tile *getTile(int index);
		static CppOGL::Audio *getAudio(int index);
	private:
		int checkFiles();
		int checkFile(const char *fileName);
};

#endif
