#ifndef __CALLBACK_H
#define __CALLBACK_H

namespace CppOGL {
	class Object;
	
	class Callback {
		public:
			virtual int overlapTest(Object *obj1, Object *obj2);
			virtual void onOverlap(Object *obj1, Object *obj2);
			virtual void simpleCallback();
	};
	
	class DefaultCallback : public Callback {
		public:
			int overlapTest(Object *obj1, Object *obj2);
	};
}

#endif
