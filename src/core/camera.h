#ifndef __CAMERA_H
#define __CAMERA_H

#include <GL/glew.h>

namespace CppOGL {
	
	class Object;
	class GLSLProgram;
	
	class Camera {
		public:
			/**
			 * Horizontal position of the camera inside the window.
			 */
			float x;
			/**
			 * Vertical position of the camera inside the window.
			 */
			float y;
			/**
			 * Horizontal position of the camera in the game world.
			 */
			float scrollX;
			/**
			 * Vertical position of the camera in the game world.
			 */
			float scrollY;
			/**
			 * Camera's visible rect width.
			 * Is multiplied by scaleX when rendered.
			 */
			float width;
			/**
			 * Camera's visible rect height.
			 * Is multiplied by scaleY when rendered.
			 */
			float height;
			/**
			 * Horizontal scale factor for the camera.
			 */
			float scaleX;
			/**
			 * Vertical scale factor for the camera.
			 */
			float scaleY;
		private:
			float _defX;
			float _defY;
			float _defWidth;
			float _defHeight;
			float _defScaleX;
			float _defScaleY;
			
			GLfloat worldMatrix[16];
			GLfloat flashColor[4];
			float flashTime;
			float flashLength;
			float fadeTime;
			float fadeDuration;
			float shakeTime;
			float shakeStrength;
			
			GLuint fbo;
			GLuint fbo_texture;
			//GLuint rbo_depth;
			GLuint vbo_fbo_vertices;
			GLSLProgram *_program;
		protected:
			GLSLProgram *_postProcessProgram;
		public:
			Camera(float X, float Y, float Width, float Height, float ScaleX, float ScaleY);
			virtual ~Camera();
			
			void start();
			void setTransform(float x, float y);
			void setScale(float sx, float sy);
			void setRotation(float rx, float ry);
			void setTextureOffset(float x, float y);
			virtual void drawFrameBuffer();
			virtual void postProcess();
			
			void resetScreen(float X, float Y, float Width, float Height, float ScaleX, float ScaleY);
			void resizeHorizontalLeft(float left, float Width);
			void resizeHorizontalRight(float right, float Width);
			void resizeVerticalBottom(float bottom, float Height);
			void resizeVerticalTop(float top, float Height);
			
			void follow(Object *target);
			
			void flash(int Color, float duration, int force);
			void updateFlash();
			void shake(float duration, float strength, int force);
			void updateShake();
			void fade(float duration, int force);
			void updateFade();
			
			void setPostProcessProgram(GLSLProgram *program);
			void setPostProcessUniforms();
			int getPostProcessUniforms();
	};
}

#endif
