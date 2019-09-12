#version 430
out vec4 Color;
layout(location=0) in vec2 texCoord;

uniform sampler2D testTex;

void main()
{
	vec3 col = texture(testTex, vec2(texCoord.x, 1.0 - texCoord.y)).rgb;
	Color = vec4(col, 1);
};