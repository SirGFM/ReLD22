#ifndef __OBJECT_H
#define __OBJECT_H

#include <core/basic.h>
namespace CppOGL {
	class Object : public Basic {
		public:
			/**
			 * Current horizontal position.
			 */
			float x;
			/**
			 * Current vertical position.
			 */
			float y;
			/**
			 * Current horizontal velocity.
			 */
			float vx;
			/**
			 * Current vertical velocity.
			 */
			float vy;
			/**
			 * Current horizontal acceleration.
			 */
			float ax;
			/**
			 * Current vertical acceleration.
			 */
			float ay;
			/**
			 * Maximum horizontal velocity.
			 */
			float maxvx;
			/**
			 * Maximum vertical velocity.
			 */
			float maxvy;
			/**
			 * Used to check for overlap;
			 */
			float radius;
			
			float width;
			float height;
		public:
			Object();
			
			virtual void update();
			
			void setTopLeft(float X, float Y);
			void velocityTo(float X, float Y, float time);
			void velocityTo(Object *obj, float time);
			void normalizeSpeed(float speed);
			
			int overlaps(Basic *b, Callback *const callback);
	};
}

#endif
