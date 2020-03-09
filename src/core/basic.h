#ifndef __BASIC_H
#define __BASIC_H

namespace CppOGL {
	class Callback;
	
	class Basic {
		public:
			int exists;
			int active;
			int visible;
			int id;
			int overlapable;
		public:
			Basic();
			virtual ~Basic();
			
			virtual void update()=0;
			virtual void draw()=0;
			
			virtual void kill();
			virtual void revive();
			
			virtual int overlaps(Basic *b, Callback *const callback);
	};
}

#endif
