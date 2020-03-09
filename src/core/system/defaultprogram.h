#ifndef __DEFAULTPROGRAM_H
#define __DEFAULTPROGRAM_H

#include <core/system/glslprogram.h>

namespace CppOGL {
	enum {
		LOCTOGL = 0,
		TRANSLATION,
		SCALE,
		ROTATION,
		TEXTOFFSET,
		GSAMPLER,
		MAXUNIFORM
	};
	
	class DefaultProgram : public GLSLProgram {
		public:
			DefaultProgram();
	};
}

#endif
