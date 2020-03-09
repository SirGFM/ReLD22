#ifndef __SPRITE_H
#define __SPRITE_H

#include <GL/glew.h>
#include <core/object.h>
namespace CppOGL {
	class Animation;
	class Mesh;
	class Tile;
	class Callback;
	
	struct AnimationLL {
		Animation *self;
		struct AnimationLL *next;
	};
	
	class Sprite : public Object {
		public:
			static int translation;
			static int scale;
			static int rotation;
		private:
			/**
			 * Retain the context (e.g., uniforms and vbo) for this sprite.
			 */
			GLuint vao;
			/**
			 * Current mesh representing the sprite.
			 * It won't be cleaned up on deconstruction!
			 */
			Mesh *mesh;
			/**
			 * Current texture associated with this mesh.
			 * A tile is still necessary to make it render properly.
			 */
			Tile *tile;
			/**
			 * Current angle.
			 */
			float angle;
			/**
			 * Angle's cosine.
			 */
			float rx;
			/**
			 * Angle's sine.
			 */
			float ry;
			float flickerTimer;
		public:
			/**
			 * Horizontal scaling factor.
			 */
			float scalex;
			/**
			 * Vertical scaling factor.
			 */
			float scaley;
			/**
			 * 
			 */
			Animation *curAnimation;
			AnimationLL *animList;
			
		public:
			Sprite();
			virtual ~Sprite();
			
			int onScreen();
			
			virtual void draw();
			void setMesh(Mesh *newMesh);
			void setTile(Tile *newTile);
			
			void flicker(float time);
			int isFlickering();
			
			void setAngle(float val);
			float getAngle();
			
			int addAnimation(Tile *Tiles[], int numTile, int fps, int looped);
			int play(int id, int force);
	};
}

#endif
