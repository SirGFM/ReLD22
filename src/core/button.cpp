#include <core/audio.h>
#include <core/callback.h>
#include <core/data/coredata.h>
#include <core/pointer.h>
#include <core/text.h>
#include <core/button.h>

CppOGL::Button::Button(char *Label, CppOGL::Callback *const CB) {
	this->label = new CppOGL::Text();
	this->label->setText(Label, 12);
	this->cb = (CppOGL::Callback*)CB;
	this->mouseState = 0;
	this->setMesh(CppOGL::CoreData::getMesh(CppOGL::BTMESH));
	
	CppOGL::Tile *anim0[] = {CppOGL::CoreData::getTile(CppOGL::BTTILENONE)};
	int a = this->addAnimation(anim0, 1, 1, 0);
	CppOGL::Tile *anim1[] = {CppOGL::CoreData::getTile(CppOGL::BTTILEOVER)};
	int b = this->addAnimation(anim1, 1, 1, 0);
	CppOGL::Tile *anim2[] = {CppOGL::CoreData::getTile(CppOGL::BTTILEPRES)};
	int c = this->addAnimation(anim2, 1, 1, 0);
	
	this->mouseState = -1;
	this->width = 128;
	this->height = 16;
}

CppOGL::Button::~Button() {
	delete this->label;
}

void CppOGL::Button::update() {
	this->label->x = this->x -53 + 5;
	this->label->y = this->y -9 + 3;
	
	if (Pointer::x >= this->x - 52 && Pointer::x <= this->x + 52 &&
		Pointer::y >= this->y - 8 && Pointer::y <= this->y + 8)
	{
		if (this->mouseState == CppOGL::BTNONE && !CppOGL::Pointer::left) {
			this->mouseState = CppOGL::BTOVER;
			this->play(BTOVER, 0);
		}
		else if (this->mouseState == BTOVER && CppOGL::Pointer::left) {
			this->mouseState = CppOGL::BTPRES;
			this->play(BTPRES, 0);
		}
		else if (this->mouseState == CppOGL::BTPRES && !CppOGL::Pointer::left) {
			this->cb->simpleCallback();
			CppOGL::CoreData::getAudio(CppOGL::BTSFX)->play();
			this->mouseState = CppOGL::BTNONE;
			this->play(BTNONE, 0);
		}
	}
	else if (this->mouseState != CppOGL::BTNONE) {
		this->mouseState = CppOGL::BTNONE;
		this->play(BTNONE, 0);
	}
	
	if (this->mouseState == BTOVER)
		this->label->y--;
	else if (this->mouseState == BTPRES)
		this->label->y++;
}

void CppOGL::Button::draw() {
	CppOGL::Sprite::draw();
	this->label->draw();
}
