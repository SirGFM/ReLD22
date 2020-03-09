#include <core/button.h>
#include <core/game.h>
#include <core/sprite.h>
#include <core/text.h>
#include <game/assets/data.h>
#include <game/global.h>
#include <game/menuscene.h>
#include <game/mycallbacks.h>
#include <game/gameoverwindow.h>

GameOverWindow::GameOverWindow() {
	bg = new CppOGL::Sprite();
	bg->setMesh(Data::getMesh(MESH128x64));
	bg->setTile(Data::getTile(GMWINDOW));
	bg->setAngle(90);
	bg->y = 128;
	
	t = new CppOGL::Text();
	t->setText("   GAMEOVER\n\nSCORE:       0\n\n HIGH\nSCORE:       0", 15);
	t->x = 70;
	t->y = 72;
	add(t);
	
	//CppOGL::Button *b = new CppOGL::Button("MAIN MENU", &cb1);
	CppOGL::Button *b = new CppOGL::Button("MAIN MENU", MyCallbacks::toMenuBtCB);
	b->x = 128;
	b->y = 142;
	add(b);
	
	//b = new CppOGL::Button("RESTART", &cb2);
	b = new CppOGL::Button("RESTART", MyCallbacks::restartBtCB);
	b->x = 128;
	b->y = 166;
	add(b);
}

GameOverWindow::~GameOverWindow() {
	delete bg;
}

void GameOverWindow::draw() {
	bg->scaley = 1;
	bg->x = 128-32;
	bg->draw();
	bg->scaley = -1;
	bg->x = 128+32;
	bg->draw();
	CppOGL::Group::draw();
}

void GameOverWindow::restart(int score, int highscore) {
	t->writeInt(20, 7, score, 0);
	t->writeInt(42, 7, highscore, 0);
}
