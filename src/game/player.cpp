#include <game/player.h>
#include <game/assets/data.h>
#include <core/pointer.h>
#include <core/timer.h>
#include <core/utils.h>
#include <core/tile.h>
#include <game/global.h>

Player::Player() {
	this->setMesh(Data::getMesh(MESH32x32));
	CppOGL::Tile *anim0[] = {Data::getTile(HAPPY0), Data::getTile(HAPPY1), Data::getTile(HAPPY0), Data::getTile(HAPPY2)};
	CppOGL::Tile *anim1[] = {Data::getTile(NORM0), Data::getTile(NORM1), Data::getTile(NORM0), Data::getTile(NORM2)};
	CppOGL::Tile *anim2[] = {Data::getTile(SAD0), Data::getTile(SAD1), Data::getTile(SAD0), Data::getTile(SAD2)};
	CppOGL::Tile *anim3[] = {Data::getTile(HAPPY0)};
	CppOGL::Tile *anim4[] = {Data::getTile(NORM0)};
	CppOGL::Tile *anim5[] = {Data::getTile(SAD0)};
	this->addAnimation(anim0, 4, 8, 1);
	this->addAnimation(anim1, 4, 8, 1);
	this->addAnimation(anim2, 4, 8, 1);
	this->addAnimation(anim3, 1, 0, 0);
	this->addAnimation(anim4, 1, 0, 0);
	this->addAnimation(anim5, 1, 0, 0);
	this->play(PLHAPPY, 0);
	
	this->x = CppOGL::Pointer::x;
	this->y = CppOGL::Pointer::y;
	this->radius = 14;
}

void Player::update() {
	float dx = CppOGL::Pointer::x - x;
	float dy = CppOGL::Pointer::y - y;
	
	this->vx = dx;
	if (dx < 16.0f)
		this->vx *= 2.0f;
	this->vy = dy;
	if (dy < 16.0f)
		this->vy *= 2.0f;
	
	// too slow... stop!
	if (CppOGL::Utils::abs(this->vx) <= 1.0f && CppOGL::Utils::abs(this->vy) <= 1.0f) {
		this->vx = 0.0f;
		this->vy = 0.0f;
	}
	
	// this->scalex = (((int)this->vx & 0x80000000) >> 31) * 2.0f + 1.0f;
	this->scalex = ((this->vx > 0) - 0.5f) * 2.0f;
	// this->scalex = (this->vx & -0.0f) | 1.0f;
	// this->scalex = (((float)((((int)this->vx) & 0x80000000) >> 31)) - 0.5f) * -2.0f;
	
	if (Global::health < 25)
		if (this->vx != 0)
			this->play(PLSAD, 0);
		else
			this->play(PLSADST, 0);
	else if (Global::health < 75)
		if (this->vx != 0)
			this->play(PLNORM, 0);
		else
			this->play(PLNORMST, 0);
	else
		if (this->vx != 0)
			this->play(PLHAPPY, 0);
		else
			this->play(PLHAPPYST, 0);
	
	CppOGL::Object::update();
}
