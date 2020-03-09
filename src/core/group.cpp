#include <cstdio>
#include <core/basic.h>
#include <core/callback.h>
#include <core/group.hpp>

CppOGL::Group::Group() {
	members = NULL;
	removed = NULL;
	length = 0;
}

CppOGL::Group::~Group() {
	struct CppOGL::BasicLL *tmp2;
	struct CppOGL::BasicLL *tmp1 = this->members;
	while (tmp1) {
		tmp2 = tmp1->next;
		delete tmp1->self;
		delete tmp1;
		tmp1 = tmp2;
	}
	tmp1 = this->removed;
	while (tmp1) {
		tmp2 = tmp1->next;
		delete tmp1->self;
		delete tmp1;
		tmp1 = tmp2;
	}
}

void CppOGL::Group::update() {
	struct CppOGL::BasicLL *tmp = this->members;
	while (tmp) {
		CppOGL::Basic *basic = tmp->self;
		if (basic->exists && basic->active)
			basic->update();
		tmp = tmp->next;
	}
}

void CppOGL::Group::draw() {
	struct CppOGL::BasicLL *tmp = this->members;
	while (tmp) {
		CppOGL::Basic *basic = tmp->self;
		if (basic->exists && basic->visible)
			basic->draw();
		tmp = tmp->next;
	}
}

CppOGL::Basic* CppOGL::Group::add(CppOGL::Basic *basic) {
	struct CppOGL::BasicLL *tmp;
	if (!basic)
		return NULL;
	tmp = this->members;
	if (!tmp) {
		this->members = new struct CppOGL::BasicLL();
		tmp = this->members;
	}
	else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new struct BasicLL();
		tmp = tmp->next;
	}
	tmp->self = basic;
	tmp->next = NULL;
	length++;
	return basic;
}

CppOGL::Basic* CppOGL::Group::remove(CppOGL::Basic *basic, int recycle) {
	struct CppOGL::BasicLL* tmp1;
	struct CppOGL::BasicLL* tmp2;
	if (!basic || length == 0)
		return NULL;
	tmp1 = this->members;
	if (tmp1->self == basic) {
		this->members = this->members->next;
		tmp2 = tmp1;
	}
	else {
		while (tmp1->next && tmp1->next->self != basic)
			tmp1 = tmp1->next;
		if (!tmp1->next)
			return NULL;
		tmp2 = tmp1->next;
		tmp1->next = tmp2->next;
	}
	if (recycle) {
		tmp1 = this->removed;
		if (!tmp1)
			this->removed = tmp2;
		else {
			while (tmp1->next)
				tmp1 = tmp1->next;
			tmp1->next = tmp2;
		}
		tmp2->next = NULL;
		return tmp2->self;
	}
	delete tmp2->self;
	delete tmp2;
	return NULL;
}

int CppOGL::Group::countInstances() {
	int i = 0;
	/*struct BasicLL *tmp = this->removed;
	while (tmp) {
		tmp = tmp->next;
		i++;
	}*/
	return this->length+i;
}

int CppOGL::Group::overlaps(CppOGL::Basic *b, CppOGL::Callback *const callback) {
	int didCollide = 0;
	CppOGL::BasicLL *tmp = members;
	while (tmp) {
		CppOGL::Basic *tmpobj = tmp->self;
		if (tmpobj->exists && tmpobj->overlapable)
			didCollide |= b->overlaps(tmpobj, callback);
		tmp = tmp->next;
	}
	return didCollide;
}

int CppOGL::Group::overlaps(CppOGL::Callback *const callback) {
	int didCollide = 0;
	CppOGL::BasicLL *cur = this->members;
	while (cur) {
		CppOGL::Basic *curobj = cur->self;
		if (curobj->exists && curobj->overlapable) {
			CppOGL::BasicLL *tmp = cur->next;
			while (tmp) {
				CppOGL::Basic *tmpobj = tmp->self;
				if (tmpobj->exists && tmpobj->overlapable)
					didCollide |= curobj->overlaps(tmpobj, callback);
				tmp = tmp->next;
			}
		}
		cur = cur->next;
	}
	return didCollide;
}
