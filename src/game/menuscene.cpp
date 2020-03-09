#include <core/audio.h>
#include <core/button.h>
#include <core/game.h>
#include <core/save.h>
#include <core/sprite.h>
#include <core/text.h>
#include <core/system/audioll.h>
#include <core/system/audioutils.h>
#include <game/colorcamera.h>
#include <game/gamestate.h>
#include <game/menuscene.h>
#include <game/mycallbacks.h>
#include <game/assets/data.h>

Menuscene::~Menuscene() {
	CppOGL::Audio::stop(this->song->id);
}

void Menuscene::create() {
	CppOGL::Sprite *title = new CppOGL::Sprite();
	title->x = 128;
	title->y = 32+16;
	title->setMesh(Data::getMesh(MESH256x32));
	title->setTile(Data::getTile(TITLE));
	add(title);
	
	CppOGL::Button *b = new CppOGL::Button("START GAME", MyCallbacks::toGameBtCB);
	b->setTopLeft(8, 96);
	add(b);
	b = new CppOGL::Button("INSTRUCTIONS", MyCallbacks::toIntroBtCB);
	b->setTopLeft(8, 128);
	add(b);
	
	int hc;
	CppOGL::Save *s = new CppOGL::Save();
	s->bind("save.sav");
	if (s->read("hc", &hc)) {
		hc = 0;
		s->write("hc", &hc, sizeof(int));
	}
	delete s;
	
	CppOGL::Text *t = new CppOGL::Text();
	t->setText("HIGHSCORE         ", 9);
	t->writeInt(10, 7, hc, 0);
	add(t);
	
	this->song = CppOGL::AudioUtils::getAudioReference(Data::getAudio(MENUSONG)->play());
}
