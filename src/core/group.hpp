#ifndef __GROUP_H
#define __GROUP_H

#include <typeinfo>
#include <core/basic.h>
namespace CppOGL {
	class Callback;
	// TODO fix recycle!
	
	struct BasicLL {
		Basic *self;
		struct BasicLL *next;
	};
	
	class Group : public Basic {
		protected:
			struct BasicLL *members;
			struct BasicLL *removed;
			int length;
		public:
			Group();
			virtual ~Group();
			
			virtual void update();
			virtual void draw();
			Basic* add(Basic *basic);
			Basic* remove(Basic *basic, int recycle);
			int countInstances();
			
			int overlaps(Basic *b, Callback *const callback);
			int overlaps(Callback *const callback);
			
			template <class type> Basic *recycle() {
				struct BasicLL *tmp = this->members;
				if (this->length > 0 && tmp) {
					if (typeid(tmp->self) == typeid(type))
						return tmp->self;
					else {
						while (tmp->next && (typeid(*(tmp->next->self)) != typeid(type) || tmp->next->self->exists))
							tmp = tmp->next;
						if (tmp->next && !tmp->next->self->exists) {
							struct BasicLL *tmp2 = tmp->next;
							return tmp2->self;
						}
					}
				}
				return add(new type());
			}
	};
}

#endif
