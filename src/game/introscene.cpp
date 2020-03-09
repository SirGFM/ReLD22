#include <core/game.h>
#include <core/text.h>
#include <core/timer.h>
#include <core/utils.h>
#include <game/bar.h>
#include <game/enemy.h>
#include <game/friend.h>
#include <game/gamestate.h>
#include <game/global.h>
#include <game/mycallbacks.h>
#include <game/player.h>
#include <game/introscene.h>

#define CHARDELAY	0.075f

Introscene::Introscene() {
	Global::init();
	
	this->text = new CppOGL::Text();
	this->text->setBlank(49, 28);
	this->text->x = 16;
	this->text->y = 24;
	this->n = 0;
	this->timer = CppOGL::Timer::elapsed;
	
	this->bar = new Bar(100);
	Global::player = new Player();
	this->add(Global::player);
	
	Global::introscene = this;
}

Introscene::~Introscene() {
	delete this->text;
	delete this->bar;
}

void Introscene::update() {
	this->timer -= CppOGL::Timer::elapsed;
	if (this->timer <= 0) {
		this->setState();
		this->n++;
	}
	else if (this->i < this->len && CppOGL::Utils::mod(this->timer, CHARDELAY) <= CppOGL::Timer::elapsed) {
		this->text->updateChar(this->i, this->curTxt[i]);
		this->i++;
	}
	
	Global::updateHealth();
	this->bar->setval((int)Global::health);
	this->overlaps(MyCallbacks::introCollisionCB);
	
	Group::update();
}

void Introscene::draw() {
	if (Global::updatecolors) {
		Global::cc->update();
		Global::updatecolors = 0;
	}
	
	Group::draw();
	this->bar->draw();
	this->text->draw();
}

void Introscene::setState() {
	CppOGL::Basic *b;
	this->i = 0;
	switch (this->n) {
		case 0: {
			this->len = 14;
			this->curTxt = "YOU ARE ALONE!";
		} break;
		case 1: {
			this->len = 42;
			this->curTxt = "So alone your \"loneliness\"\nis hurting you!";
		}break;
		case 2: {
			this->len = 14;
			this->curTxt = "But fraid not!";
		}break;
		case 3: {
			this->len = 24;
			this->curTxt = "You're not the only one.";
		}break;
		case 4: {
			this->len = 22;
			this->curTxt = "Try to befriend those.";
			b = this->recycle<Friend>();
			b->revive();
		}break;
		case 5: {
			this->len = 20;
			this->curTxt = "Not enough, I see...";
		}break;
		case 6: {
			int index;
			this->len = 26;
			this->curTxt = "Try to approach some more.";
			index = 0;
			while(index++ < 5) {
				b = this->recycle<Friend>();
				b->revive();
			}
		}break;
		case 7: {
			this->len = 29;
			this->curTxt = "See? You're barely alone\nnow.";
		}break;
		case 8: {
			this->len = 49;
			this->curTxt = "Some aren't happy with your\nlack of loneliness...";
		}break;
		case 9: {
			this->len = 7;
			this->curTxt = "Beware!";
		}break;
		case 10: {
			this->len = 48;
			this->curTxt = "They can make some flee and\nbreak you all apart.";
			b = this->recycle<Enemy>();
			b->revive();
		}break;
		case 11: {
			this->len = 21;
			this->curTxt = "Just keep yourself...";
		}break;
		case 12: {
			this->len = 9;
			this->curTxt = "...not...";
		}break;
		case 13: {
			this->len = 6;
			this->curTxt = "ALONE!";
		}break;
		case 14: {
			CppOGL::Game::switchScene(new Gamestate());
		}break;
	}
	this->text->setBlank(49, 28);
	this->timer += this->len * CHARDELAY + 2.5f;
}

void Introscene::plHit() {
	struct CppOGL::BasicLL *tmp = this->members;
	while (tmp) {
		Friend *f = dynamic_cast<Friend*>(tmp->self);
		tmp = tmp->next;
		if (f)
			f->runway();
	}
}
