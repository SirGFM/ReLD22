#include <core/object.h>
#include <core/timer.h>
#include <core/utils.h>
#include <core/system/defaultprogram.h>
#include <core/system/glslprogram.h>
#include <core/camera.h>

// http://en.wikibooks.org/wiki/OpenGL_Programming/Post-Processing
namespace CppOGL {
	enum {
		CAM_GSAMPLER = 0,
		CAM_OFFY,
		CAM_FLCOLOR,
		CAM_FLTIME,
		CAM_FATIME,
		CAM_ZOOM,
		CAM_MAX
	};
	
	const char *strVertexPPShader = 
"#version 330\n\
layout(location = 0) in vec2 pos;\n\
out vec2 _texCoord;\n\
\n\
void main()\n\
{\n\
	gl_Position = vec4(pos, -1.0f, 1.0f);\n\
	_texCoord = (pos + 1.0f) * 0.5f;\n\
}\n";

	const char *strFragmentPPShader = 
"#version 330\n\
in vec2 _texCoord;\n\
out vec4 outputColor;\n\
\n\
uniform sampler2D gSampler;\n\
uniform float offsetY;\n\
uniform vec4 flashColor;\n\
uniform lowp float flashT;\n\
uniform lowp float fadeT;\n\
\n\
void main()\n\
{\n\
	vec2 texCoord = _texCoord;\n\
	\n\
	// Shake effect\n\
	texCoord.t += offsetY;\n\
	lowp vec4 pixel = texture2D(gSampler, texCoord.st);\n\
	// Flash effect\n\
	pixel = pixel*(1-flashT) + flashT*flashColor;\n\
	// Fade effect\n\
	pixel = pixel*(1-fadeT) + fadeT*vec4(0.0f, 0.0f, 0.0f, 1.0f);\n\
	\n\
	outputColor = pixel;\n\
}\n";
}

CppOGL::Camera::Camera(float X, float Y, float Width, float Height, float ScaleX, float ScaleY) {
	GLenum shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	const char *postshaders[] = {CppOGL::strVertexPPShader, CppOGL::strFragmentPPShader, 0};
	
	this->_program = new DefaultProgram();
	
	this->_postProcessProgram = new GLSLProgram(shaderTypes, postshaders, 5);
	this->setPostProcessUniforms();
	
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &(this->fbo_texture));
	glBindTexture(GL_TEXTURE_2D, this->fbo_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//glGenRenderbuffers(1, &(this->rbo_depth));
	this->resetScreen(X, Y, Width, Height, ScaleX, ScaleY);
	
	glGenFramebuffers(1, &(this->fbo));
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->fbo_texture, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rbo_depth);
	
	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
		//printf("Fuck! Can't return errors on the constructor... xD \n");
		// FIXME !!!
	}
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
	
	GLfloat fbo_vertices[] = {-1, -1, 1, -1, -1, 1, 1, 1};
	glGenBuffers(1, &(this->vbo_fbo_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_fbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	this->worldMatrix[0] = 1.0f;
	  this->worldMatrix[1] = 0.0f;
	    this->worldMatrix[2] = 0.0f;
		  this->worldMatrix[3] = -1.0f;
	this->worldMatrix[4] = 0.0f;
	  this->worldMatrix[5] = 1.0f;
	    this->worldMatrix[6] = 0.0f;
		  this->worldMatrix[7] = 1.0f;
	this->worldMatrix[8] = 0.0f;
	  this->worldMatrix[9] = 0.0f;
	    this->worldMatrix[10] = 1.0f;
		  this->worldMatrix[11] = 0.0f;
	this->worldMatrix[12] = 0.0f;
	  this->worldMatrix[13] = 0.0f;
	    this->worldMatrix[14] = 0.0f;
		  this->worldMatrix[15] = 1.0f;
	this->resetScreen(X, Y, Width, Height, ScaleX, ScaleY);
	
	this->flashColor[0] = 1.0f;
	this->flashColor[1] = 1.0f;
	this->flashColor[2] = 1.0f;
	this->flashColor[3] = 1.0f;
	
	this->flashTime = 0;
	this->flashLength = 0;
	this->fadeTime = 0;
	this->fadeDuration = 0;
	this->shakeTime = 0;
	this->shakeStrength = 0;
}

CppOGL::Camera::~Camera() {
	delete _program;
	delete _postProcessProgram;
	//glDeleteRenderbuffers(1, &(this->rbo_depth));
	glDeleteTextures(1, &(this->fbo_texture));
	glDeleteFramebuffers(1, &(this->fbo));
	glDeleteBuffers(1, &(this->vbo_fbo_vertices));
}

void CppOGL::Camera::start() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo); 
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	this->_program->use();
}

void CppOGL::Camera::setTransform(float x, float y) {
	this->_program->set2f(CppOGL::TRANSLATION, x, y);
}

void CppOGL::Camera::setScale(float sx, float sy) {
	this->_program->set2f(CppOGL::SCALE, sx, sy);
}

void CppOGL::Camera::setRotation(float rx, float ry) {
	this->_program->set2f(CppOGL::ROTATION, rx, ry);
}

void CppOGL::Camera::setTextureOffset(float x, float y) {
	this->_program->set2f(CppOGL::TEXTOFFSET, x, y);
}

void CppOGL::Camera::drawFrameBuffer() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->fbo_texture);
	glBindSampler(CppOGL::CAM_GSAMPLER, GL_TEXTURE0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_fbo_vertices);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void CppOGL::Camera::postProcess() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// remove those for awesomeness!!
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	this->_postProcessProgram->use();
	if (this->flashTime > 0.0f)
		this->updateFlash();
	if (this->fadeTime > 0.0f)
		this->updateFade();
	if (this->shakeTime > 0.0f)
		this->updateShake();
	this->drawFrameBuffer();
}

void CppOGL::Camera::resetScreen(float X, float Y, float Width, float Height, float ScaleX, float ScaleY) {
	this->_defX = X;
	this->_defY = Y;
	this->_defWidth = Width;
	this->_defHeight = Height;
	this->_defScaleX = ScaleX;
	this->_defScaleY = ScaleY;
	
	this->x = X;
	this->y = Y;
	this->scrollX = 0;
	this->scrollY = 0;
	this->width = Width;
	this->height = Height;
	this->scaleX = ScaleX;
	this->scaleY = ScaleY;
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)Width*ScaleX, (int)Height*ScaleY, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	worldMatrix[0] = 2.0f / Width;
	worldMatrix[5] = -2.0f / Height;
	this->_program->use();
	this->_program->setm4fv(CppOGL::LOCTOGL, this->worldMatrix);
	//this->_postProcessProgram->use();
	//this->_postProcessProgram->set2f(CppOGL::CAM_ZOOM, ScaleX, ScaleY);
	
	/*
	glBindRenderbuffer(GL_RENDERBUFFER, this->rbo_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, (int)Width, (int)Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	*/
}

void CppOGL::Camera::resizeHorizontalLeft(float left, float Width) {
	
}

void CppOGL::Camera::resizeHorizontalRight(float right, float Width) {
	
}

void CppOGL::Camera::resizeVerticalBottom(float bottom, float Height) {
	
}

void CppOGL::Camera::resizeVerticalTop(float top, float Height) {
	
}

void CppOGL::Camera::follow(Object *target) {
	
}

void CppOGL::Camera::flash(int Color, float duration, int force) {
	if (duration == 0 || this->flashTime == 0 || force) {
		this->flashColor[0] = ((Color >> 24)&0xff)/0xff;
		this->flashColor[1] = ((Color >> 16)&0xff)/0xff;
		this->flashColor[2] = ((Color >> 8)&0xff)/0xff;
		this->flashColor[3] = (Color&0xff)/0xff;
		this->flashTime = CppOGL::Timer::elapsed;
		this->flashLength = duration;
	}
	if (duration == 0)
		this->_postProcessProgram->setFloat(CppOGL::CAM_FLTIME, 0.0f);
}

void CppOGL::Camera::updateFlash() {
	this->flashTime += CppOGL::Timer::elapsed;
	
	float val = CppOGL::Utils::abs(this->flashTime/this->flashLength - 0.5f);
	this->_postProcessProgram->setFloat(CppOGL::CAM_FLTIME, 1.0f - val*2.0f);
	
	if (this->flashTime >= this->flashLength)
		this->flashTime = 0.0f;
	
	this->_postProcessProgram->set4fv(CppOGL::CAM_FLCOLOR, this->flashColor);
}

void CppOGL::Camera::shake(float duration, float strength, int force) {
	if (duration == 0.0f || this->shakeTime == 0.0f || force) {
		this->shakeTime = duration;
		this->shakeStrength = strength;
	}
}

void CppOGL::Camera::updateShake() {
	float s;
	this->shakeTime -= CppOGL::Timer::elapsed * this->shakeStrength;
	if (this->shakeTime < 0.0f)
		this->shakeTime = 0.0f;
	
	s = this->shakeTime;
	if (this->shakeTime > 1.0f)
		s -= ((int)this->shakeTime);
	s = CppOGL::Utils::sin((int)(s*360.0f));
	
	this->_postProcessProgram->setFloat(CppOGL::CAM_OFFY, s*this->shakeStrength * 0.1f);
}

void CppOGL::Camera::fade(float duration, int force) {
	if (duration == 0.0f || this->fadeTime >= this->fadeDuration || force) {
		this->fadeTime = CppOGL::Timer::elapsed;
		this->fadeDuration = duration;
	}
	if (duration == 0.0f)
		this->_postProcessProgram->setFloat(CppOGL::CAM_FATIME, 0.0f);
}

void CppOGL::Camera::updateFade() {
	if (this->fadeTime > this->fadeDuration)
		this->_postProcessProgram->setFloat(CppOGL::CAM_FATIME, 1.0f);
	else {
		this->fadeTime += CppOGL::Timer::elapsed;
		this->_postProcessProgram->setFloat(CppOGL::CAM_FATIME, this->fadeTime/this->fadeDuration);
	}
}

void CppOGL::Camera::setPostProcessProgram(CppOGL::GLSLProgram *program) {
	if (this->_postProcessProgram)
		delete this->_postProcessProgram;
	this->_postProcessProgram = program;
}

void CppOGL::Camera::setPostProcessUniforms() {
	this->_postProcessProgram->createUniform(CppOGL::CAM_GSAMPLER, "gSampler");
	this->_postProcessProgram->createUniform(CppOGL::CAM_OFFY, "offsetY");
	this->_postProcessProgram->createUniform(CppOGL::CAM_FLCOLOR, "flashColor");
	this->_postProcessProgram->createUniform(CppOGL::CAM_FLTIME, "flashT");
	this->_postProcessProgram->createUniform(CppOGL::CAM_FATIME, "fadeT");
	this->_postProcessProgram->createUniform(CppOGL::CAM_ZOOM, "zoom");
}

int CppOGL::Camera::getPostProcessUniforms() {
	return CAM_MAX;
}
