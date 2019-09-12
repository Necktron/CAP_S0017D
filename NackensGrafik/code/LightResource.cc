#include "LightResource.h"
#include "config.h"

LightResource::LightResource()
{

}

LightResource::~LightResource()
{
	
}

void LightResource::getPointLight()
{
	Lighting OUT;
	PointLight pLight;

	if (pLight.diffusePower > 0)
	{
		vector3D lightDir = pLight.position - pos3D;
		float distance = lightDir.vecLength();
		lightDir = lightDir / distance;
		distance = distance * distance;

		//Intensity of the diffuse light. Saturate is to keep it within 0 - 1 range
		float NdotL = normal.dotProd(lightDir);

		//CLAMP THAT SHIT - TODO
		float intensity = GLclampf(NdotL);

		//Calculate the diffuse light factoring in light color, power and the attenuation
		OUT.Diffuse = (pLight.diffuseColor * intensity) * pLight.diffusePower / distance;

		//Calculate the half vector between the light vector and the view vector.
		//This is typically slower than calculating the actual reflection vector due to the normalize function's reciprocal square root
		vector3D H = lightDir.vecNormilisation() + viewDir.vecNormilisation();

		//Intensity of the specular light
		float NdotH = normal.dotProd(H);
		
		//CLAMP 2.0
		intensity = pow(GLclampf(NdotH), 1);

		//Sum up the specular light factoring
		OUT.Specular = (pLight.specularColor * intensity) * pLight.specularPower / distance;
	}
}