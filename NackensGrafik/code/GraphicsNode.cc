#include "GraphicsNode.h"
#include "config.h"

GraphicsNode::GraphicsNode()
{

}

GraphicsNode::~GraphicsNode()
{

}

void GraphicsNode::setMesh(shared_ptr<MeshResource> &memory)
{
	meshPtr = memory;
}

void GraphicsNode::setTex(shared_ptr<TextureResource> &memory)
{
	texPtr = memory;
}

void GraphicsNode::setShade(shared_ptr<ShaderObject> &memory)
{
	shadePtr = memory;
}

std::shared_ptr<MeshResource> GraphicsNode::getMesh()
{
	return meshPtr;
}

std::shared_ptr<TextureResource> GraphicsNode::getTex()
{
	return texPtr;
}

std::shared_ptr<ShaderObject> GraphicsNode::getShade()
{
	return shadePtr;
}

void GraphicsNode::Draw()
{
	texPtr->Bind();
	meshPtr->DrawOBJ();
}