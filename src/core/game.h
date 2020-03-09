#ifndef __GAME_H
#define __GAME_H

namespace CppOGL {
	class Camera;
	class Scene;
	
	namespace Game {
		extern int screenwidth;
		extern int screenheight;
		
		extern Camera *camera;
		extern Scene *_curScene;
		
		extern void openConsole();
		extern int init(const char *name, const char *icon, unsigned char *mask, int Width, int Height, int Zoom, int FPS);
		extern int run(Scene *scene);
		extern void clear();
		
		extern void switchScene(Scene *scene);
		
		extern void setWidth(int Width);
		extern void setHeight(int Height);
		extern void setZoom(int Zoom);
	}
}

#endif
