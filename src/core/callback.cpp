#include <core/object.h>
#include <core/callback.h>
#include <core/utils.h>

int CppOGL::Callback::overlapTest(CppOGL::Object *obj1, CppOGL::Object *obj2) { return 0; }
void CppOGL::Callback::onOverlap(CppOGL::Object *obj1, CppOGL::Object *obj2) { }
void CppOGL::Callback::simpleCallback() { }

int CppOGL::DefaultCallback::overlapTest(CppOGL::Object *obj1, CppOGL::Object *obj2) {
	float d, sqrdist, maxdist;
	
	d = obj1->x - obj2->x;
	sqrdist = d*d;
	d = obj1->y - obj2->y;
	sqrdist += d*d;
	maxdist = obj1->radius + obj2->radius;
	
	if (sqrdist <= maxdist*maxdist) {
		this->onOverlap(obj1, obj2);
		return 1;
	}
	
	return 0;
}
