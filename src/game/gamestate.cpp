#include <core/audio.h>
#include <core/basic.h>
#include <core/game.h>
#include <core/object.h>
#include <core/pointer.h>
#include <core/save.h>
#include <core/text.h>
#include <core/timer.h>
#include <core/utils.h>
#include <core/system/audioutils.h>
#include <core/system/audioll.h>
#include <game/bar.h>
#include <game/assets/data.h>
#include <game/enemy.h>
#include <game/friend.h>
#include <game/gameoverwindow.h>
#include <game/global.h>
#include <game/player.h>
#include <game/mycallbacks.h>

#include <game/gamestate.h>
#include <GL/glew.h>

//#define writestuff

#ifdef writestuff
	CppOGL::Text *red;
	CppOGL::Text *green;
	CppOGL::Text *blue;
	CppOGL::Text *count;
#endif

void Gamestate::create() {
	Global::init();
	
	Global::gamestate = this;
	Global::player = new Player();
	add(Global::player);
	
	this->bar = new Bar(100);
	this->gmw = new GameOverWindow();
	
	this->score = 0;
	this->scoreText = new CppOGL::Text();
	this->scoreText->x = 191;
	this->scoreText->y = 8;
	this->scoreText->setText(" SCORE       0", 7);
	this->timer = 2;
	this->gameover = 0;
	
	CppOGL::AudioUtils::sfxVolume = 1.0f;
	int stmp = Data::getAudio(SADSONG)->play();
	int ntmp = Data::getAudio(NORMSONG)->play();
	int htmp = Data::getAudio(HAPPYSONG)->play();
	this->sad = CppOGL::AudioUtils::getAudioReference(stmp);
	this->norm = CppOGL::AudioUtils::getAudioReference(ntmp);
	this->happy = CppOGL::AudioUtils::getAudioReference(htmp);
	this->sad->volume = 0.0f;
	this->norm->volume = 0.0f;
	this->happy->volume = 0.0f;
	
	#ifdef writestuff
		red = new CppOGL::Text();
		red->x = 216;
		red->y = 186;
		red->setText("red\n    ", 4);
		green = new CppOGL::Text();
		green->x = 216;
		green->y = 200;
		green->setText("gre\n0000", 4);
		blue = new CppOGL::Text();
		blue->x = 216;
		blue->y = 216;
		blue->setText("blu\n0000", 4);
		count = new CppOGL::Text();
		count->x = 216;
		count->y = 232;
		count->setText("num\n    ", 4);
		add(red);
		add(green);
		add(blue);
		add(count);
	#endif
}

Gamestate::~Gamestate() {
	delete this->bar;
	delete this->scoreText;
	CppOGL::Audio::stop(this->sad->id);
	CppOGL::Audio::stop(this->norm->id);
	CppOGL::Audio::stop(this->happy->id);
}

void Gamestate::update() {
	//int n;
	//float h;
	
	if (this->gameover) {
		this->gmw->update();
		if (Global::restart == 1) {
			this->score = 0;
			this->scoreText->updateText(" SCORE       0");
			this->gameover = 0;
			Global::restart = 0;
			Global::health = 12.5;
			struct CppOGL::BasicLL *tmp = members;
			while (tmp) {
				if (tmp->self != Global::player)
					tmp->self->kill();
				tmp = tmp->next;
			}
		}
		return;
	}
	
	this->timer -= CppOGL::Timer::elapsed;
	if (this->timer <= 0) {
		this->timer += (CppOGL::Utils::rand() * 10) % 4 + 1;
		float rnd = CppOGL::Utils::frand();
		CppOGL::Basic *b;
		if (rnd < 0.6f)
			b = this->recycle<Friend>();
		else
			b = this->recycle<Enemy>();
		b->revive();
	}
	this->overlaps(MyCallbacks::gameCollisionCB);
	
	if (this->timer > 1 && this->timer-1 <= CppOGL::Timer::elapsed) {
		int n = n = Global::red + Global::green + Global::blue;
		this->score += (int)(Global::health/20.0f) + n*2;
		this->scoreText->writeInt(7, 7, this->score, 0);
	}
	Global::updateHealth();
	this->bar->setval((int)Global::health);
	this->updateMusic(Global::health);
	
	CppOGL::Group::update();
	
	if (Global::health == 0) {
		int hs;
		this->gameover = 1;
		CppOGL::Save *s = new CppOGL::Save();
		s->bind("save.sav");
		s->read("hc", &hs);
		if (this->score > hs) {
			s->write("hc", &(this->score), sizeof(int));
		}
		this->gmw->restart(this->score, hs);
		Global::restart = 0;
	}
}

void Gamestate::draw() {
	#ifdef writestuff
		count->writeInt(4, 4, this->countInstances(), 0);
	#endif
	if (Global::updatecolors) {
		
		#ifdef writestuff
			red->writeInt(4, 4, Global::red, 1);
			green->writeInt(4, 4, Global::green, 1);
			blue->writeInt(4, 4, Global::blue, 1);
		#endif
		
		Global::cc->update();
		Global::updatecolors = 0;
	}
	
	CppOGL::Group::draw();
	this->bar->draw();
	this->scoreText->draw();
	if (this->gameover)
		this->gmw->draw();
}

void Gamestate::plHit() {
	struct CppOGL::BasicLL *tmp = this->members;
	while (tmp) {
		Friend *f = dynamic_cast<Friend*>(tmp->self);
		tmp = tmp->next;
		if (f)
			f->runway();
	}
}

void Gamestate::updateMusic(float h) {
	if (h < 35.0f)
		this->sad->volume = 1.0f - h / 35.0f;
	else
		this->sad->volume = 0.0f;
	if (h < 15)
		this->norm->volume = 0.0f;
	else if (h < 50)
		this->norm->volume = 1.0f - (50.0f - h) / 35.0f;
	else if (h < 85.0f)
		this->norm->volume = (85.0f - h) / 35.0f;
	else
		this->norm->volume = 0.0f;
	if (h > 65.0f)
		this->happy->volume = (h - 65.0f) / 35.f;
	else
		this->happy->volume = 0.0f;
}
