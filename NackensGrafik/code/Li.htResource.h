#pragma once
#include "core/app.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <random>

class LightResource
{
	struct Lighting
	{
		vector3D Diffuse;
		vector3D Specular;
	};

	struct PointLight
	{
		vector3D position;
		vector3D diffuseColor;
		vector3D specularColor;
		GLfloat  diffusePower;
		GLfloat  specularPower;
	};

	public:
		LightResource();
		~LightResource();

		void getPointLight();

		vector3D pos3D;
		vector3D viewDir;
		vector3D normal;
};