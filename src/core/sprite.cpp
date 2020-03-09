#include <core/camera.h>
#include <core/game.h>
#include <core/mesh.h>
#include <core/tile.h>
#include <core/timer.h>
#include <core/utils.h>
#include <core/system/animation.h>
#include <core/system/glslprogram.h>
#include <core/sprite.h>

int CppOGL::Sprite::translation;
int CppOGL::Sprite::scale;
int CppOGL::Sprite::rotation;

CppOGL::Sprite::Sprite() {
	glGenVertexArrays(1, &(this->vao));
	this->mesh = NULL;
	this->tile = NULL;
	this->scalex = 1.0f;
	this->scaley = 1.0f;
	this->curAnimation = 0;
	this->animList = 0;
	this->setAngle(0.0f);
	this->flickerTimer = 0.0f;
}

CppOGL::Sprite::~Sprite() {
	glDeleteVertexArrays(1, &(this->vao));
	this->mesh = 0;
	this->curAnimation = 0;
	struct CppOGL::AnimationLL *tmp;
	while (this->animList) {
		tmp = this->animList->next;
		delete this->animList->self;
		delete this->animList;
		this->animList = tmp;
	}
}

int CppOGL::Sprite::onScreen() {
	CppOGL::Camera *c = CppOGL::Game::camera;
	float _x = this->x - c->scrollX;
	float _y = this->y - c->scrollY;
	return !(_x < 0 || _x > c->width || _y < 0 || _y > c->height);
}

void CppOGL::Sprite::draw() {
	if (!this->mesh)
		return;
	else if (this->flickerTimer > 0) {
		this->flickerTimer -= Timer::elapsed;
		if (CppOGL::Utils::mod(this->flickerTimer, 0.075) <= 0.0375)
			return;
	}
	
	if (this->curAnimation) {
		if (this->curAnimation->update())
			this->setTile(this->curAnimation->getTile());
	}
	glBindVertexArray(this->vao);
	
	CppOGL::Game::camera->setTransform(CppOGL::Utils::floor(this->x), CppOGL::Utils::floor(this->y));
	CppOGL::Game::camera->setScale(this->scalex, this->scaley);
	CppOGL::Game::camera->setRotation(this->rx, this->ry);
	/*
	CppOGL::Game::shaderProgram->set2f(CppOGL::Sprite::translation, CppOGL::Utils::floor(this->x), CppOGL::Utils::floor(this->y));
	CppOGL::Game::shaderProgram->set2f(CppOGL::Sprite::scale, this->scalex, this->scaley);
	CppOGL::Game::shaderProgram->set2f(CppOGL::Sprite::rotation, this->rx, this->ry);
	*/
	
	if (this->tile)
		this->tile->use();
	this->mesh->render();
	
	glBindVertexArray(0);
}

void CppOGL::Sprite::setMesh(CppOGL::Mesh *newMesh) {
	this->mesh = newMesh;
	
	glBindVertexArray(this->vao);
	this->mesh->associate();
	glBindVertexArray(0);
}
void CppOGL::Sprite::setTile(CppOGL::Tile *newTile) {
	this->tile = newTile;
	
	glBindVertexArray(this->vao);
	this->tile->associate();
	glBindVertexArray(0);
}

void CppOGL::Sprite::flicker(float time) {
	this->flickerTimer = time;
}

int CppOGL::Sprite::isFlickering() {
	return this->flickerTimer > 0;
}

void CppOGL::Sprite::setAngle(float val) {
	this->angle = val;
	this->rx = Utils::cos(val);
	this->ry = Utils::sin(val);
}

float CppOGL::Sprite::getAngle() {
	return this->angle;
}

int CppOGL::Sprite::addAnimation(CppOGL::Tile *Tiles[], int numTile, int fps, int looped) {
	int i = 0;
	struct CppOGL::AnimationLL *tmp;
	if (!this->animList) {
		this->animList = new struct CppOGL::AnimationLL();
		tmp = this->animList;
	}
	else {
		tmp = this->animList;
		while (tmp->next) {
			tmp = tmp->next;
			i++;
		}
		tmp->next = new struct CppOGL::AnimationLL();
		tmp = tmp->next;
	}
	tmp->self = new CppOGL::Animation(Tiles, numTile, fps, looped);
	tmp->next = 0;
	return i;
}

int CppOGL::Sprite::play(int id, int force) {
	int i = 0;
	struct CppOGL::AnimationLL *tmp = this->animList;
	while (i++ < id && tmp)
		tmp = tmp->next;
	if (!tmp)
		return 0;
	if (force || this->curAnimation != tmp->self) {
		this->curAnimation = tmp->self;
		this->curAnimation->restart();
		this->setTile(this->curAnimation->getTile());
	}
	return 1;
}
