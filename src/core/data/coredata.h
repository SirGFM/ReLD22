#ifndef __COREDATA_H
#define __COREDATA_H

namespace CppOGL {
	class Audio;
	class Buffer;
	class Mesh;
	class Tile;
	class Texture;
	
	enum {
		FONTMESH = 0,
		BTMESH,
		MAXMESH
	};
	enum {
		FONTTEXT = 0,
		BTTEXT,
		MAXTEXT
	};
	enum {
		FONTTILE = 0,
		FONTLASTTILE=63,
		BTTILENONE=64,
		BTTILEOVER=65,
		BTTILEPRES=66,
		MAXTILE
	};
	enum {
		FONTBUF = 0,
		FONTTILEBUF,
		BTBUF,
		BTTILEBUF,
		MAXBUF
	};
	enum {
		BTSFX = 0,
		MAXAUDIO
	};
	
	class CoreData {
		private:
			static CoreData *self;
		private:
			Buffer *buffers[MAXBUF];
			Mesh *meshes[MAXMESH];
			Texture *textures[MAXTEXT];
			Tile *tiles[MAXTILE];
			Audio *audios[MAXAUDIO];
		private:
			CoreData();
		public:
			~CoreData();
			static void init();
			static void clear();
			
			static Mesh* getMesh(int index);
			static Tile* getTile(int index);
			static Texture* getTexture(int index);
			static Audio* getAudio(int index);
	};
}

#endif
