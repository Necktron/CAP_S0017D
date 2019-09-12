#include "TextureResource.h"
#include "config.h"
#include <string>
#include <memory>

TextureResource::TextureResource()
{

}

TextureResource::~TextureResource()
{

}

void TextureResource::loadFromRast(std::shared_ptr<Rasterizer> rastPTR)
{
	glGenTextures(1, &texBufferID);

	glBindTexture(GL_TEXTURE_2D, texBufferID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rastPTR->width, rastPTR->height, 0, GL_RGB, GL_UNSIGNED_BYTE, &rastPTR->pixelRetriver()[0]);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureResource::loadFromFile(const char *filePath)
{
	int bitdepth;

	//OBS! These are tested: ( StrawHats.jpg, Ace.jpg, Corazon.jpg, cat_diff.tga )

	data = stbi_load(filePath, &width, &height, &bitdepth, STBI_rgb_alpha);

	glGenTextures(1, &texBufferID);

	glBindTexture(GL_TEXTURE_2D, texBufferID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(bitdepth == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	else if(bitdepth == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
}

void TextureResource::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texBufferID);
}