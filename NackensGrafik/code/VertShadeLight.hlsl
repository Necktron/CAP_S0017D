#version 430
layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 myTexture;
layout(location = 2) in vec4 inputNormal;
out vec3 normalInterp;
out vec3 vertPos;
out vec4 vertPos4;

out vec2 texCoord;

uniform mat4 matrix, projection, modelView;

void main()
{
	vec4 v = pos;
	gl_Position = (projection * modelView * pos);
	texCoord = myTexture;
	vertPos4 = modelView * pos;
	vertPos = vec3(vertPos4) / vertPos4.w;
	normalInterp = normalize(vec3(matrix * inputNormal));
}