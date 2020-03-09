#include <core/timer.h>
#include <core/tile.h>
#include <core/system/animation.h>

CppOGL::Animation::Animation(Tile *Tiles[], int NumTiles, int fps, int looped) {
	int i;
	
	this->tiles = new struct TileLL;
	struct CppOGL::TileLL *tmp = this->tiles;
	i = 0;
	while (1) {
		tmp->self = Tiles[i++];
		if (i < NumTiles) {
			tmp->next = new struct CppOGL::TileLL;
			tmp = tmp->next;
		}
		else
			break;
	}
	if (looped)
		tmp->next = this->tiles;
	else
		tmp->next = 0;
	
	this->numTiles = NumTiles;
	this->curTile = this->tiles;
	this->elapsed = 0;
	this->frameTime = 1.0f / fps;
}

CppOGL::Animation::~Animation() {
	int i = 0;
	while (i < this->numTiles && this->tiles) {
		struct CppOGL::TileLL *tmp = this->tiles->next;
		delete this->tiles;
		this->tiles = tmp;
		i++;
	}
	this->curTile = 0;
}

void CppOGL::Animation::restart() {
	this->curTile = this->tiles;
	this->elapsed = 0;
}

int CppOGL::Animation::update() {
	if (!this->curTile->next)
		return 0;
	this->elapsed += CppOGL::Timer::elapsed;
	if (this->elapsed >= this->frameTime) {
		this->curTile = this->curTile->next;
		this->elapsed -= this->frameTime;
		return 1;
	}
	return 0;
}

CppOGL::Tile *CppOGL::Animation::getTile() {
	if (!this->curTile)
		return 0;
	return this->curTile->self;
}
