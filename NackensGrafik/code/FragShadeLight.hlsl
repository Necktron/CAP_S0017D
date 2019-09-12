#version 430
layout(location = 0) out vec4 Color;
in vec2 texCoord;
in vec3 normalInterp;
in vec3 vertPos;

uniform sampler2D testTex;

precision mediump float;

uniform int mode;

const vec3 lightPos = vec3(21.0, 21.0, 0.0);
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const vec3 diffuseColor = vec3(0.1, 0.1, 0.1);
const vec3 specColor = vec3(0.1, 0.1, 0.1);
const float shininess = 16.0;
const float screenGamma = 2.2; // Assume the monitor is calibrated to the sRGB color space

void main()
{
	vec3 normal = normalize(normalInterp);
	vec3 lightDir = normalize(lightPos - vertPos);

	float lambertian = max(dot(lightDir, normal), 0.0);
	float specular = 0.0;

	if (lambertian > 0.0)
	{
		vec3 viewDir = normalize(-vertPos);

		//This is blinn phong
		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, normal), 0.0);
		specular = pow(specAngle, shininess);
	}

	vec3 col = texture(testTex, vec2(texCoord.x, 1.0 - texCoord.y)).rgb;
	vec3 colorLinear = (ambientColor + lambertian * diffuseColor + specular * specColor) * col;

	// apply gamma correction (assume ambientColor, diffuseColor and specColor
	// have been linearized, i.e. have no gamma correction in them)
	vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));

	// use the gamma corrected color in the fragment
	Color = vec4(colorGammaCorrected, 1.0);
}