#ifndef __COLORCAMERA_H
#define __COLORCAMERA_H

#include <GL/glew.h>
#include <core/camera.h>

class ColorCamera : public CppOGL::Camera {
	public:
		GLfloat toBWmat[9];
	private:
		int wasUpdated;
	public:
		ColorCamera(float X, float Y, float Width, float Height, float ScaleX, float ScaleY);
		
		void drawFrameBuffer();
		
		void reset();
		void update();
	private:
		float colorComponent(int val, int maxval);
};

#endif
