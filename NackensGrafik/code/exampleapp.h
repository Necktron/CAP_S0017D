#pragma once
//------------------------------------------------------------------------------
/**
Application class used for example application.

(C) 2015-2016 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include <memory>
#include <conio.h>
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "GraphicsNode.h"
#include "Matrix3D.h"
#include "LightResource.h"
#include "Rasterizer.h"

namespace Example
{
	class NackensGrafik : public Core::App
	{
		public:
			/// constructor
			NackensGrafik();

			/// destructor
			~NackensGrafik();

			/// open app
			bool Open();
			/// run app
			void Run();

			void Update();

			float rotInt = 0;
			float rotIntX = 0;
			float rotIntY = 0;
			float movmentX = 0;
			float movmentY = 0;
			
			bool rotateEnable;

			matrix3D trans;
			matrix3D matrix;
			matrix3D rotA;
			matrix3D rotB;
			std::shared_ptr<MeshResource> meshPTR;
			std::shared_ptr<MeshResource> meshRastPTR;
			std::shared_ptr<TextureResource> texPTR;
			std::shared_ptr<ShaderObject> shadePTR;
			std::shared_ptr<LightResource> lightPTR;
			std::shared_ptr<Rasterizer> rastPTR;
			GraphicsNode graphic;
			float mouseRotX = 0;
			float mouseRotY = 0;

		private:
			GLuint triangle;
			Display::Window* window;
	};
} // namespace Example