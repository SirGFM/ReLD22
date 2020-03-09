#include <game/enemy.h>
#include <game/assets/data.h>
#include <core/timer.h>
#include <core/utils.h>

Enemy::Enemy() {
	this->setMesh(Data::getMesh(MESH32x32));
	CppOGL::Tile *anim[] = {Data::getTile(BADDY0), Data::getTile(BADDY1), Data::getTile(BADDY0), Data::getTile(BADDY2)};
	this->addAnimation(anim, 4, 8, 1);
	this->play(0, 0);
	
	this->radius = 11;
}

void Enemy::update() {
	this->timer -= CppOGL::Timer::elapsed;
	if (this->timer <= 0 && this->moveCount) {
		moveCount--;
		this->seekRandomPos();
		this->scalex = ((this->vx > 0) - 0.5f) * 2.0f;
	}
	else if (!this->onScreen()) {
		this->kill();
		return;
	}
	
	CppOGL::Object::update();
}

void Enemy::revive() {
	CppOGL::Basic::revive();
	this->x = (CppOGL::Utils::rand()*1000)%230 + 10;
	this->y = (CppOGL::Utils::rand()*1000)%230 + 10;
	this->seekRandomPos();
	this->moveCount = (CppOGL::Utils::rand() * 10) % 4 + 1;
	this->flicker(3.0f);
}

void Enemy::seekRandomPos() {
	float X = (CppOGL::Utils::rand()*1000)%230 + 10;
	float Y = (CppOGL::Utils::rand()*1000)%230 + 10;
	this->timer = (CppOGL::Utils::rand()*10)%3 + 1;
	this->velocityTo(X, Y, this->timer);
	if (CppOGL::Utils::abs(this->vx) > 120 || CppOGL::Utils::abs(this->vy) > 120)
		this->normalizeSpeed(120);
}
