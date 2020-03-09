#include <game/bar.h>
#include <game/assets/data.h>

#define w	128.0f

Bar::Bar(int Max) {
	this->max = Max;
	this->cur = Max;
	this->updated = 1;
	this->setMesh(Data::getMesh(MESH128x16));
	this->setTile(Data::getTile(BAR));
	this->overlapable = 0;
	
	this->height = 16;
}

Bar::~Bar() {
	
}

void Bar::draw() {
	if (this->updated) {
		float dx = ((float)cur) / max;
		this->scalex = dx;
		this->width = w * dx;
		this->setTopLeft(64, 8);
		this->updated = 0;
	}
	CppOGL::Sprite::draw();
}

void Bar::setval(int val) {
	if (val == this->cur)
		return;
	
	if (val < 0)
		this->cur = 0;
	else if (val > this->max)
		this->cur = this->max;
	else
		this->cur = val;
	this->updated = 1;
}
