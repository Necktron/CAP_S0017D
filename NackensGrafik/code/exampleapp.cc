//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <iostream>

using namespace Display;

namespace Example
{

	//------------------------------------------------------------------------------
	/**
	*/
	NackensGrafik::NackensGrafik()
	{

	}

	//------------------------------------------------------------------------------
	/**
	*/
	NackensGrafik::~NackensGrafik()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool NackensGrafik::Open()
	{
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32 a, int32 b, int32 c, int32 d)
		{
			//Keycode for A, position
			if (a == 65 && rotateEnable == false)
			{
				movmentX -= 0.02f;
			}

			//Keycode for S, position
			if (a == 83 && rotateEnable == false)
			{
				movmentY += 0.02f;
			}

			//Keycode for D, position
			if (a == 68 && rotateEnable == false)
			{
				movmentX += 0.02f;
			}

			//Keycode for W, position
			if (a == 87 && rotateEnable == false)
			{
				movmentY -= 0.02f;
			}

			/* ****************************** */

			//Keycode for A, rotation
			if (a == 65 && rotateEnable == true)
			{
				rotIntY -= 1.5f;
			}

			//Keycode for S, rotation
			if (a == 83 && rotateEnable == true)
			{
				rotIntX += 1.5f;
			}

			//Keycode for D, rotation
			if (a == 68 && rotateEnable == true)
			{
				rotIntY += 1.5f;
			}

			//Keycode for W, rotation
			if (a == 87 && rotateEnable == true)
			{
				rotIntX -= 1.5f;
			}
		});

		window->SetMousePressFunction([this](int32 a, int32 b, int32 c)
		{
			if(b == 1)
			{
				rotateEnable = true;
			}

			else
			{
				rotateEnable = false;
			}
		});

		if (this->window->Open())
		{
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			meshPTR  = std::make_shared<MeshResource>();
			meshRastPTR = std::make_shared<MeshResource>();
			texPTR = std::make_shared<TextureResource>();
			shadePTR  = std::make_shared<ShaderObject>();
			lightPTR = std::make_shared<LightResource>();
			rastPTR = std::make_shared<Rasterizer>();

			shadePTR->LoadVertShader("code/VertexShade.hlsl");
			shadePTR->LoadFragShader("code/FragmentShade.hlsl");

			// setup vbo
			meshPTR->loadFromOBJ("code/cube.obj");
			//meshPTR->loadFromOBJ("code/cat.obj");
			meshRastPTR->loadFromOBJ("code/quad.obj");
			//texPTR->loadFromFile("code/StrawHats.jpg");

			lightPTR->getPointLight();
			shadePTR->apply();
			rastPTR->setMesh(meshPTR);
			rastPTR->textureRetriver("code/RedPix.tga");
			//rastPTR->textureRetriver("code/cat_diff.tga");

			auto vertShader = [](vector3D pos, vector3D norm, matrix3D nMat) -> vector3D
			{

				vector3D aColor(1.8f, 1.8f, 1.8f);
				vector3D ambientColor(0.1f, 0.1f, 0.1f);
				vector3D lightPos(0, 10, 20);
				matrix3D mvMat = nMat;

				vector3D modelViewVertex = (mvMat * pos);
				vector3D modelViewNormal = (mvMat * norm);

				vector3D tempLightDir = (lightPos - modelViewVertex);
				vector3D lightVector = tempLightDir.vecNormilisation();

				float diffuse = std::max(modelViewNormal.dotProd(lightVector), 0.1f);
				float ambient = ambientColor.dotProd(vector3D(1.0f, 1.0f, 1.0f));

				vector3D v_Color = aColor * (diffuse + ambient);

				return v_Color;
			};

			auto fragShader = [](vector2D tex, vector3D norm, unsigned char* image, int w, int h, int n) -> Rasterizer::PixelColor
			{

				int u = abs((int)(tex.vecOrigin[0] * (w - 1)) % w);
				int v = abs((int)(tex.vecOrigin[1] * (h - 1)) % h);

				int index = (u * n + v * n *w);

				Rasterizer::PixelColor color;
				color.r = image[index];
				color.g = image[index + 1];
				color.b = image[index + 2];

				return color;
			};

			rastPTR->vertexShade(vertShader);
			rastPTR->fragmentShade(fragShader);

			graphic.setMesh(meshRastPTR);
			graphic.setTex(texPTR);
			graphic.setShade(shadePTR);

			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void NackensGrafik::Run()
	{
		matrix3D matrix;
		matrix3D modelview; //Matrix för transformering
		matrix3D trans; //Translationmatrix
		matrix3D transRast; //Translationmatrix
		matrix3D proj = matrix3D::ProjectionMatrix(90.0f, 0.1f, 1000.0f, this->window->GetWidth(), this->window->GetHeight()).transpose();
		shadePTR->setupMatrix3fv("projection", proj);

		while (this->window->IsOpen())
		{			
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			trans.setPosition(vector3D(movmentX, movmentY, -2.0f));
			transRast.setPosition(vector3D(0.0f, 0.0f, 0.0f));
			Update();

			this->window->Update();

			matrix = matrix3D::scalematrix(1.0f)* rotA * rotB * trans * matrix3D::LookAt(vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 0.0f, -1.0f), vector3D(0.0f, 1.0f, 0.0f));
			modelview = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f))*transRast;
			
			shadePTR->setupMatrix3fv("matrix", proj*modelview.transpose());

			rastPTR->draw(proj, matrix.transpose());

			texPTR->loadFromRast(rastPTR);

			// do stuff
			this->graphic.Draw();

			rastPTR->flush();

			this->window->SwapBuffers();
		}
	}

	void NackensGrafik::Update()
	{
		rotA = matrix3D::mxRotX(rotIntX);
		rotB = matrix3D::mxRotY(rotIntY);
	}

} // namespace Example