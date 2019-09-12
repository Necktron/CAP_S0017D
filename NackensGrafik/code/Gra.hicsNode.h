#pragma once
#include <iostream>
#include <memory>
#include "core/app.h"
#include "ShaderObject.h"
#include "MeshResource.h"
#include "TextureResource.h"

class GraphicsNode
{
	public:
		GraphicsNode();
		~GraphicsNode();

		void setMesh(shared_ptr<MeshResource> &memory);
		void setTex(shared_ptr<TextureResource> &memory);
		void setShade(shared_ptr<ShaderObject> &memory);

		void Draw();

		std::shared_ptr<MeshResource> getMesh();
		std::shared_ptr<TextureResource> getTex();
		std::shared_ptr<ShaderObject> getShade();

		std::shared_ptr<MeshResource> meshPtr;
		std::shared_ptr<TextureResource> texPtr;
		std::shared_ptr<ShaderObject> shadePtr;
};