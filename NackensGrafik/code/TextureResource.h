#pragma once
#include "core/app.h"
#include "stb_image.h"
#include "Rasterizer.h"
#include <string>

using namespace std;
class TextureResource
{
	public:
		TextureResource();
		~TextureResource();

		void loadFromFile(const char* filePath);
		void loadFromRast(std::shared_ptr<Rasterizer> rastPTR);
		void Bind();

		unsigned char *data;

		int width;
		int height;

		GLuint texBufferID;
		GLuint texCoordID;
		GLuint texID;
		
		GLfloat* uvs;
};