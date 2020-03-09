#include <core/audio.h>
#include <core/callback.h>
#include <core/camera.h>
#include <core/timer.h>
#include <core/game.h>
#include <game/assets/data.h>
#include <game/enemy.h>
#include <game/friend.h>
#include <game/global.h>
#include <game/introscene.h>
#include <game/menuscene.h>
#include <game/player.h>
#include <game/mycallbacks.h>

class ToGameBtCBclass : public CppOGL::Callback {
	public:
		void simpleCallback() {
			CppOGL::Game::switchScene(new Gamestate());
		}
} tgbcbc;

class ToIntroBtCBclass : public CppOGL::Callback {
	public:
		void simpleCallback() {
			CppOGL::Game::switchScene(new Introscene());
		}
} tibcbc;

class ToMenuBtCBClass : public CppOGL::Callback {
	public:
		void simpleCallback() {
			CppOGL::Game::switchScene(new Menuscene());
			Global::cc->reset();
		};
} tmbcbc;

class RestartBtCBclass : public CppOGL::Callback {
	public:
		void simpleCallback() {Global::restart = 1;};
} rbcbc;

class GameCollisionCBclass : public CppOGL::DefaultCallback {
	public:
		void onOverlap(CppOGL::Object *obj1, CppOGL::Object *obj2) {
			Enemy *e = 0;
			Friend *f = 0;
			Player *p = 0;
			
			if (obj1 == Global::player)
				p = (Player*)obj1;
			else if (obj2 == Global::player)
				p = (Player*)obj2;
			
			f = dynamic_cast<Friend*>(obj1);
			if (!f)
				f = dynamic_cast<Friend*>(obj2);
			
			if (!(e && p)) {
				e = dynamic_cast<Enemy*>(obj1);
				if (!e)
					e = dynamic_cast<Enemy*>(obj2);
			}
			
			if (e && e->isFlickering())
				return;
			
			if (p && f)
				f->switchState(FOLLOW);
			else if (e && f)
				f->switchState(RUN);
			else if (p && e) {
				Global::health -= 25 * CppOGL::Timer::elapsed;
				Data::getAudio(HITSFX)->play();
				if (Global::red + Global::green + Global::blue != 0)
					Global::gamestate->plHit();
			}
			
		} 
} gccbc;

class IntroCollisionCBclass : public CppOGL::DefaultCallback {
	public:
		void onOverlap(CppOGL::Object *obj1, CppOGL::Object *obj2) {
			Enemy *e = 0;
			Friend *f = 0;
			Player *p = 0;
			
			if (obj1 == Global::player)
				p = (Player*)obj1;
			else if (obj2 == Global::player)
				p = (Player*)obj2;
			
			f = dynamic_cast<Friend*>(obj1);
			if (!f)
				f = dynamic_cast<Friend*>(obj2);
			
			if (!(e && p)) {
				e = dynamic_cast<Enemy*>(obj1);
				if (!e)
					e = dynamic_cast<Enemy*>(obj2);
			}
			
			if (e && e->isFlickering())
				return;
			
			if (p && f)
				f->switchState(FOLLOW);
			else if (e && f)
				f->switchState(RUN);
			else if (p && e) {
				Global::health -= 25 * CppOGL::Timer::elapsed;
				Data::getAudio(HITSFX)->play();
				if (Global::red + Global::green + Global::blue != 0)
					Global::introscene->plHit();
			}
			
		} 
} iccbc;

CppOGL::Callback *const  MyCallbacks::toGameBtCB = &tgbcbc;
CppOGL::Callback *const  MyCallbacks::toIntroBtCB = &tibcbc;
CppOGL::Callback *const  MyCallbacks::toMenuBtCB = &tmbcbc;
CppOGL::Callback *const  MyCallbacks::restartBtCB = &rbcbc;
CppOGL::Callback *const  MyCallbacks::gameCollisionCB = &gccbc;
CppOGL::Callback *const  MyCallbacks::introCollisionCB = &iccbc;
