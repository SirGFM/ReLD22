#ifndef __ANIMATION_H
#define __ANIMATION_H

namespace CppOGL {
	class Tile;
	
	struct TileLL {
		Tile *self;
		struct TileLL *next;
	};
	
	class Animation {
		private:
			int numTiles;
			float elapsed;
			float frameTime;
			struct TileLL *tiles;
			struct TileLL *curTile;
		public:
			Animation(Tile *Tiles[], int NumTiles, int fps, int looped);
			~Animation();
			
			void restart();
			int update();
			Tile *getTile();
	};
}
#endif
