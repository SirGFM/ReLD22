#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <GL/glew.h>

namespace CppOGL {
	class Texture {
		public:
			static GLuint sampler;
		private:
			/**
			 * Texture's id used by OpenGL.
			 */
			GLuint texId;
		public:
			/**
			 * Creates a new texture
			 * 
			 * @param	Width {int}		How many pixels wide is the texture.
			 * @param	Height {int}	How many pixels tall is the texture.
			 * @param	data {float *}	Array of RGBA pixels in the range [0, 1].
			 */
			Texture(int Width, int Height, char *data);
			~Texture();
			
			/**
			 * Sets this as the texture being used by OpenGL.
			 */
			void use();
	};
}

#endif
