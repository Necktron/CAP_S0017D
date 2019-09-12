#version 430
layout(location=0) in vec3 pos;
layout(location=1) in vec2 myTexture;
out vec2 texCoord;

uniform mat4 matrix;

void main()
{
	vec4 v = vec4(pos, 1);
	gl_Position = (matrix * v);
	texCoord = myTexture;
};