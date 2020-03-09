#include <GL/glew.h>
#include <core/game.h>
#include <core/sprite.h>
#include <core/tile.h>
#include <core/texture.h>
#include <core/system/defaultprogram.h>

namespace CppOGL {
	extern char *strVertexShader;
	extern char *strFragmentShader;
	GLenum shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	const char *shaders[] = {CppOGL::strVertexShader, CppOGL::strFragmentShader, NULL};
}

CppOGL::DefaultProgram::DefaultProgram() : CppOGL::GLSLProgram::GLSLProgram (CppOGL::shaderTypes, CppOGL::shaders, 6) {
	this->createUniform(CppOGL::LOCTOGL, "locToGL");
	this->createUniform(CppOGL::TRANSLATION, "translation");
	this->createUniform(CppOGL::SCALE, "scale");
	this->createUniform(CppOGL::ROTATION, "rotation");
	this->createUniform(CppOGL::TEXTOFFSET, "texoffset");
	this->createUniform(CppOGL::GSAMPLER, "gSampler");
	
	//CppOGL::Game::locToGL = LOCTOGL;
	CppOGL::Sprite::translation = CppOGL::TRANSLATION;
	CppOGL::Sprite::scale = CppOGL::SCALE;
	CppOGL::Sprite::rotation = CppOGL::ROTATION;
	CppOGL::Tile::textureoffset = CppOGL::TEXTOFFSET;
	CppOGL::Texture::sampler = CppOGL::GSAMPLER;
}
