namespace CppOGL {
	const char *strVertexShader = 
"#version 330\n\
layout(location = 0) in vec2 _pos;\n\
layout(location = 1) in vec2 texCoord;\n\
\n\
uniform mat4 locToGL;\n\
uniform vec2 scale;\n\
uniform vec2 translation;\n\
uniform vec2 rotation;\n\
uniform vec2 texoffset;\n\
\n\
out vec2 texCoord0;\n\
\n\
void main()\n\
{\n\
	vec2 pos = _pos;\n\
	mat2 rot;\n\
	rot[0].xy = vec2(rotation.x, -rotation.y);\n\
	rot[1].xy = rotation.yx;\n\
	pos *= scale;\n\
	pos *= rot;\n\
	pos += translation;\n\
	vec4 position = vec4(pos.x, pos.y, -1.0f, 1.0f);\n\
	gl_Position = position*locToGL;\n\
	texCoord0 = texCoord+texoffset;\n\
}\n";

	const char *strFragmentShader = 
"#version 330\n\
in vec2 texCoord0;\n\
out vec4 outputColor;\n\
\n\
uniform sampler2D gSampler;\n\
\n\
void main()\n\
{\n\
	outputColor = texture2D(gSampler, texCoord0.st);\n\
}\n";

}
