#include <game/friend.h>
#include <game/assets/data.h>
#include <game/global.h>
#include <core/audio.h>
#include <core/timer.h>
#include <core/utils.h>

Friend::Friend() {
	this->setMesh(Data::getMesh(MESH8x8));
	this->radius = 11;
	this->state = -1;
	this->befriended = 0;
}

void Friend::update() {
	switch (this->state) {
		case WANDER: {
			this->timer -= CppOGL::Timer::elapsed;
			if (this->timer <= 0) {
				this->rndTimer();
				this->rndVelocity();
			}
			this->isOutScreen();
		} break;
		case FOLLOW: {
			float dx = Global::player->x - this->x;
			float dy = Global::player->y - this->y;
			float dist = dx*dx + dy*dy;
			if (dist > 400.0f) {
				dy = dy / dx;
				dx = 100.0f / CppOGL::Utils::sqrt(CppOGL::Utils::abs(dy));
				dy *= dx;
				if ((this->x - Global::player->x) < 0) {
					this->ax = dx;
					this->ay = dy;
				}
				else {
					this->ax = -dx;
					this->ay = -dy;
				}
			}
			else {
				this->ax = 0;
				this->ay = 0;
				this->vx = 0;
				this->vy = 0;
			}
		} break;
		case RUN: {
			this->isOutScreen();
		} break;
	}
	CppOGL::Object::update();
}

void Friend::revive() {
	CppOGL::Basic::revive();
	this->timer = 0;
	this->switchState(WANDER);
	this->x = (CppOGL::Utils::rand() * 1000) % 230 + 10;
	this->y = (CppOGL::Utils::rand() * 1000) % 230 + 10;
	this->color = (CppOGL::Utils::rand() * 10) % 3;
	switch (this->color) {
		case RED: {
			this->setTile(Data::getTile(BRED));
			Global::maxred++;
		} break;
		case GREEN: {
			this->setTile(Data::getTile(BGREEN));
			Global::maxgreen++;
		} break;
		case BLUE: {
			this->setTile(Data::getTile(BBLUE));
			Global::maxblue++;
		} break;
	}
	Global::updatecolors = 1;
	this->unbefriend();
	this->befriended = 0;
}

void Friend::kill() {
	CppOGL::Basic::kill();
	switch (this->color) {
		case RED: Global::maxred--; break;
		case GREEN: Global::maxgreen--; break;
		case BLUE: Global::maxblue--; break;
	}
	Global::updatecolors = 1;
}

void Friend::rndVelocity() {
	float X = (CppOGL::Utils::rand() * 1000) % 230 + 10;
	float Y = (CppOGL::Utils::rand() * 1000) % 230 + 10;
	this->velocityTo(X, Y, this->timer);
	if (CppOGL::Utils::abs(this->vx) > 120 || CppOGL::Utils::abs(this->vy) > 120)
		this->normalizeSpeed(120);
}

void Friend::rndTimer() {
	this->timer += (CppOGL::Utils::rand() * 10) % 4 + 1;
}

void Friend::isOutScreen() {
	if (!this->onScreen())
		this->kill();
}

void Friend::befriend() {
	if (this->befriended)
		return;
	Data::getAudio(FRIENDSFX)->play();
	switch (this->color) {
		case RED: Global::red++; break;
		case GREEN: Global::green++; break;
		case BLUE: Global::blue++; break;
	}
	this->befriended = 1;
}

void Friend::unbefriend() {
	if (!this->befriended)
		return;
	switch (this->color) {
		case RED: Global::red--; break;
		case GREEN: Global::green--; break;
		case BLUE: Global::blue--; break;
	}
	this->befriended = 0;
}

void Friend::runway() {
	if (this->state == FOLLOW)
		this->switchState(RUN);
}

void Friend::switchState(int State) {
	if (State == RUN)
		Data::getAudio(HITSFX)->play();
	
	if (State == this->state)
		return;
	
	switch (State) {
		case WANDER: {
			this->rndTimer();
			this->rndVelocity();
			this->ax = 0;
			this->ay = 0;
		} break;
		case FOLLOW: {
			this->befriend();
		} break;
		case RUN: {
			this->unbefriend();
			this->timer = 3;
			this->velocityTo(Global::player, this->timer);
			if (CppOGL::Utils::abs(this->vx) < 150 || CppOGL::Utils::abs(this->vy) < 150)
				this->normalizeSpeed(150);
			this->vx *= -1;
			this->vy *= -1;
			this->ax = 0;
			this->ay = 0;
		} break;
	}
	
	if (State != WANDER)
		Global::updatecolors = 1;
	
	this->state = State;
}
