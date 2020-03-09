#include <GL/glew.h>
#include <SDL/SDL.h>
#include <core/audio.h>
#include <core/buffer.h>
#include <core/mesh.h>
#include <core/texture.h>
#include <core/tile.h>
#include <core/data/coredata.h>
#include <core/data/assets/buttontiles.h>
#include <core/data/assets/fonttiles.h>

namespace CppOGL {
	extern char fontdata[];
	extern char btdata[];
	extern Uint8 btaudiodata[];
}
CppOGL::CoreData *CppOGL::CoreData::self = 0;

void CppOGL::CoreData::init() {
	if (CppOGL::CoreData::self)
		return;
	CppOGL::CoreData::self = new CppOGL::CoreData();
}

void CppOGL::CoreData::clear() {
	if (CppOGL::CoreData::self)
		delete CppOGL::CoreData::self;
}

CppOGL::CoreData::CoreData() {
	const GLshort vindex[] = {0, 1, 2, 2, 3, 0};
	
	const float v8x8[] = {-4.0f, -4.0f, -4.0f, 4.0f, 4.0f, 4.0f, 4.0f, -4.0f};
	this->buffers[CppOGL::FONTBUF] = new CppOGL::Buffer(v8x8, 4);
	this->meshes[CppOGL::FONTMESH] = new CppOGL::Mesh(this->buffers[CppOGL::FONTBUF], vindex, 2);
	this->textures[CppOGL::FONTTEXT] = new CppOGL::Texture(64, 64, CppOGL::fontdata);
	CppOGL::fonttiles((this->buffers+CppOGL::FONTTILEBUF), this->tiles, this->textures[CppOGL::FONTTEXT]);
	
	const float v128x16[] = {-64.0f, -8.0f, -64.0f, 8.0f, 64.0f, 8.0f, 64.0f, -8.0f};
	this->buffers[CppOGL::BTBUF] = new CppOGL::Buffer(v128x16, 4);
	this->meshes[CppOGL::BTMESH] = new CppOGL::Mesh(this->buffers[CppOGL::BTBUF], vindex, 2);
	this->textures[CppOGL::BTTEXT] = new CppOGL::Texture(128, 64, CppOGL::btdata);
	CppOGL::buttontiles((this->buffers+CppOGL::BTTILEBUF), this->tiles, this->textures[CppOGL::BTTEXT]);
	
	this->audios[BTSFX] = new CppOGL::Audio(btaudiodata, 22136, 0);
}

CppOGL::CoreData::~CoreData() {
	int i;
	
	i = -1;
	while (++i < CppOGL::MAXTILE)
		if (this->tiles[i])
			delete this->tiles[i];
	i = -1;
	while (++i < CppOGL::MAXTEXT)
		if (this->textures[i])
			delete this->textures[i];
	i = -1;
	while (++i < CppOGL::MAXMESH)
		if (this->meshes[i])
			delete this->meshes[i];
	i = -1;
	while (++i < CppOGL::MAXBUF)
		if (this->buffers[i])
			delete this->buffers[i];
	i = -1;
	while (++i < CppOGL::MAXAUDIO)
		if (this->audios[i])
			delete this->audios[i];
}

CppOGL::Mesh* CppOGL::CoreData::getMesh(int index) {
	if (!CppOGL::CoreData::self || index >= CppOGL::MAXMESH)
		return 0;
	return CppOGL::CoreData::self->meshes[index];
}

CppOGL::Tile* CppOGL::CoreData::getTile(int index) {
	if (!CppOGL::CoreData::self || index >= CppOGL::MAXTILE)
		return 0;
	return CppOGL::CoreData::self->tiles[index];
}

CppOGL::Texture* CppOGL::CoreData::getTexture(int index) {
	if (!CppOGL::CoreData::self || index >= CppOGL::MAXTEXT)
		return 0;
	return CppOGL::CoreData::self->textures[index];
}

CppOGL::Audio* CppOGL::CoreData::getAudio(int index) {
	if (!CppOGL::CoreData::self || index >= CppOGL::MAXAUDIO)
		return 0;
	return CppOGL::CoreData::self->audios[index];
}
