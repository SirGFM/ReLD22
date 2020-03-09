#ifndef __MYCALLBACKS_H
#define __MYCALLBACKS_H

namespace CppOGL {
	class Callback;
}

namespace MyCallbacks {
	extern CppOGL::Callback *const toGameBtCB;
	extern CppOGL::Callback *const toIntroBtCB;
	extern CppOGL::Callback *const toMenuBtCB;
	extern CppOGL::Callback *const restartBtCB;
	extern CppOGL::Callback *const gameCollisionCB;
	extern CppOGL::Callback *const introCollisionCB;
}

#endif
