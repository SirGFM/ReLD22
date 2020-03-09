#include <core/system/glslprogram.h>
#include <game/global.h>
#include <game/colorcamera.h>

const char *strVertexPPColorShader = 
"#version 330\n\
layout(location = 0) in vec2 pos;\n\
out vec2 _texCoord;\n\
\n\
void main()\n\
{\n\
	gl_Position = vec4(pos, -1.0f, 1.0f);\n\
	_texCoord = (pos + 1.0f) * 0.5f;\n\
}\n";

const char *strFragmentPPColorShader = 
"#version 330\n\
in vec2 _texCoord;\n\
out vec4 outputColor;\n\
\n\
uniform sampler2D gSampler;\n\
uniform float offsetY;\n\
uniform vec4 flashColor;\n\
uniform lowp float flashT;\n\
uniform lowp float fadeT;\n\
uniform lowp mat3 toBW;\n\
\n\
void main()\n\
{\n\
	vec2 texCoord = _texCoord;\n\
	\n\
	// Shake effect\n\
	texCoord.t += offsetY;\n\
	lowp vec4 pixel = texture2D(gSampler, texCoord.st);\n\
	\n\
	// Remove colors\n\
	pixel = vec4(vec3(pixel) * toBW, 1.0f);\n\
	\n\
	// Flash effect\n\
	pixel = pixel*(1-flashT) + flashT*flashColor;\n\
	\n\
	// Fade effect\n\
	pixel = pixel*(1-fadeT) + fadeT*vec4(0.0f, 0.0f, 0.0f, 1.0f);\n\
	\n\
	outputColor = pixel;\n\
}\n";

int _TOBW;

ColorCamera::ColorCamera(float X, float Y, float Width, float Height, float ScaleX, float ScaleY) : CppOGL::Camera(X, Y, Width, Height, ScaleX, ScaleY) {
	GLenum shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	const char *postshaders[] = {strVertexPPColorShader, strFragmentPPColorShader, 0};
	
	_TOBW = this->getPostProcessUniforms();
	CppOGL::GLSLProgram *program = new CppOGL::GLSLProgram(shaderTypes, postshaders, _TOBW+1);
	this->setPostProcessProgram(program);
	program->createUniform(_TOBW, "toBW");
	this->setPostProcessUniforms();
	
	this->reset();
}

void ColorCamera::drawFrameBuffer() {
	if (this->wasUpdated) {
		this->_postProcessProgram->setm3fv(_TOBW, this->toBWmat);
		this->wasUpdated = 0;
	}
	CppOGL::Camera::drawFrameBuffer();
}

void ColorCamera::reset() {
	this->_postProcessProgram->use();
	this->toBWmat[0] = this->toBWmat[4] = this->toBWmat[8] = 1.0f;
	this->toBWmat[1] = this->toBWmat[2] = this->toBWmat[3] = 0.0f;
	this->toBWmat[5] = this->toBWmat[6] = this->toBWmat[7] = 0.0f;
	this->_postProcessProgram->setm3fv(_TOBW, this->toBWmat);
	glUseProgram(0);
}

void ColorCamera::update() {
	float r = 0;
	float g = 0;
	float b = 0;
	
	if (Global::maxred != 0)
		r = this->colorComponent(Global::red, Global::maxred);
	if (Global::maxgreen != 0)
		g = this->colorComponent(Global::green, Global::maxgreen);
	if (Global::maxblue != 0)
		b = this->colorComponent(Global::blue, Global::maxblue);
	
	this->toBWmat[0] = 0.30f + r*0.70f;
	this->toBWmat[4] = 0.59f + g*0.41f;
	this->toBWmat[8] = 0.11f + b*0.89f;
	this->toBWmat[3] = this->toBWmat[6] = (1 - r) * 0.30f;
	this->toBWmat[1] = this->toBWmat[7] = (1 - g) * 0.59f;
	this->toBWmat[2] = this->toBWmat[5] = (1 - b) * 0.11f;
	
	this->wasUpdated = 1;
}

float ColorCamera::colorComponent(int val, int maxval) {
	float res = ((float)val)/maxval;
	if (maxval < 4)
		res *= 0.2;
	else if (maxval < 7)
		res *= 0.4;
	else if (maxval < 11)
		res *= 0.6;
	else if (maxval < 14)
		res *= 0.8;
	return res;
}
