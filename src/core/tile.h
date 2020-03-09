#ifndef __TILE_H
#define __TILE_H

#include <GL/glew.h>
namespace CppOGL {
	class Buffer;
	class Texture;
	
	class Tile {
		public:
			static int textureoffset;
		private:
			/**
			 * Used to set the texture position on the shader.
			 */
			Buffer *buffer;
			/**
			 * Texture from which the tile is gotten.
			 */
			Texture *texture;
		public:
			/**
			 * Horizontal offset.
			 */
			float offx;
			/**
			 * Vertical offset.
			 */
			float offy;
		public:
			Tile(Buffer *_Buffer, Texture *_Texture, float OffX, float OffY);
			~Tile();
			
			void associate();
			void use();
	};
}

#endif
