#include <core/basic.h>
#include <core/sprite.h>
#include <core/text.h>
#include <core/data/coredata.h>

const char nwlchar = 0xfe;
const char nochar = 0xff;

CppOGL::Text::Text() {
	this->len = 0;
	this->text = 0;
	this->spr = new CppOGL::Sprite();
	this->spr->setMesh(CppOGL::CoreData::getMesh(CppOGL::FONTMESH));
	this->x = 0;
	this->y = 0;
}

CppOGL::Text::~Text() {
	if (this->text)
		delete[] this->text;
}

void CppOGL::Text::update() { }

void CppOGL::Text::draw() {
	int i;
	int n;
	
	if (!this->text)
		return;
	
	i = 0;
	n = 0;
	this->spr->x = this->x+4;
	this->spr->y = this->y+4;
	while (i < len) {
		char c = this->text[i++];
		if (c == nwlchar) {
			this->spr->x = this->x+4;
			this->spr->y += 8;
			n = 0;
			continue;
		}
		else if (c != nochar) {
			this->spr->setTile(CppOGL::CoreData::getTile(c));
			this->spr->draw();
		}
		n++;
		if (n % this->width != 0)
			this->spr->x += 8;
		else {
			this->spr->x = this->x+4;
			this->spr->y += 8;
		}
	}
}

void CppOGL::Text::setBlank(int Length, int Width) {
	int i;
	
	if (this->text && this->len != Length)
		delete[] this->text;
	if (!this->text)
		this->text = new char[Length];
	
	i = -1;
	while (++i < Length)
		this->text[i] = nochar;
	
	this->len = Length;
	this->width = Width;
}

void CppOGL::Text::setText(const char *Text, int Width) {
	int i, l;
	if (this->text)
		delete[] this->text;
	
	l = -1;
	while (Text[++l] != '\0');
	if (l == 0) {
		this->visible = 0;
		this->text = 0;
		this->len = 0;
		return;
	}
	this->len = l;
	this->text = new char[l];
	
	i = -1;
	while (++i < this->len)
		this->text[i] = this->getChar(Text[i]);
	this->width = Width;
	this->visible = 1;
}

void CppOGL::Text::updateText(const char *Text) {
	int i;
	while (i < this->len && Text[i] != '\0')
		this->text[i] = this->getChar(Text[i++]);
}

void CppOGL::Text::updateChar(int index, char c) {
	this->text[index] = this->getChar(c);
}

void CppOGL::Text::writeInt(int index, int digits, int val, int zerofill) {
	int d = 1;
	while (digits-- > 0 && (zerofill || d <= val)) {
		this->text[index+digits] = this->getChar(val / d % 10 + '0');
		d *= 10;
	}
}

char CppOGL::Text::getChar(char c) {
	if (c >= 'a' && c <= 'z')
			c += 'A'-'a';
	if (c == '\n')
		c = nwlchar;
	else if (c < '!' && c > '`')
		c = nochar;
	else
		c -= '!';
	return c;
}
