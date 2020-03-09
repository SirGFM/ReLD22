#include <core/callback.h>
#include <core/group.hpp>
#include <core/timer.h>
#include <core/utils.h>
#include <core/object.h>

CppOGL::Object::Object() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->vx = 0.0f;
	this->vy = 0.0f;
	this->ax = 0.0f;
	this->ay = 0.0f;
	this->maxvx = 1000.0f;
	this->maxvy = 1000.0f;
	this->radius = 1.0f;
}

void CppOGL::Object::update() {
	if (this->ax != 0)
		if (CppOGL::Utils::abs(this->vx) < this->maxvx)
			this->vx += this->ax*CppOGL::Timer::elapsed;
	if (this->vx != 0)
		this->x += this->vx*CppOGL::Timer::elapsed;
	
	if (this->ay != 0)
		if (CppOGL::Utils::abs(this->vy) < this->maxvy)
			this->vy += this->ay*CppOGL::Timer::elapsed;
	if (this->vy != 0)
		this->y += this->vy*CppOGL::Timer::elapsed;
}

void CppOGL::Object::velocityTo(float X, float Y, float time) {
	this->vx = (X - this->x) / time;
	this->vy = (Y - this->y) / time;
}

void CppOGL::Object::velocityTo(CppOGL::Object *obj, float time) {
	this->vx = (obj->x - this->x) / time;
	this->vy = (obj->y - this->y) / time;
}

float InvSqrt (float x){
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}

void CppOGL::Object::setTopLeft(float X, float Y) {
	this->x = X + this->width / 2;
	this->y = Y + this->height / 2;
}

void CppOGL::Object::normalizeSpeed(float speed) {
	float inv = InvSqrt(this->vx*this->vx + this->vy*this->vy);
	this->vx *= speed*inv;
	this->vy *= speed*inv;
}

int CppOGL::Object::overlaps(CppOGL::Basic *b, CppOGL::Callback *const callback) {
	if (!(overlapable && b->overlapable))
		return 0;
	
	CppOGL::Group *g = dynamic_cast<CppOGL::Group*>(b);
	if (g)
		return g->overlaps(this, callback);
	CppOGL::Object *o = dynamic_cast<CppOGL::Object*>(b);
	if (o)
		return callback->overlapTest(this, o);
	
	return 0;
}
