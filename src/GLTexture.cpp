#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <GL/gl3w.h>

void GLTexture::Load(char* FilePath)
{
	if(this->Id > 0)
	{
		return;
	}

	unsigned char *PixelData = stbi_load(FilePath, &this->Width, &this->Height, &this->Channels, STBI_rgb_alpha);

	glGenTextures(1, &this->Id);
	glBindTexture(GL_TEXTURE_2D, this->Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->Width, this->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, PixelData);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(PixelData);
}

GLTextureRegion::GLTextureRegion(GLTexture Atlas, float Width, float Height, float Row, float Collumn)
{
	this->Texture	= Atlas;
	this->Width		= Width;
	this->Height	= Height;
	
	float NumVerticalTiles = this->Texture.Width / Width;
	float NumHorizontalTiles = this->Texture.Height / Height;

	this->U0	= Row * (1 / NumVerticalTiles);
	this->V0	= Collumn * (1 / NumHorizontalTiles);
	this->U1	= (Row + 1) * (1 / NumVerticalTiles);
	this->V1	= (Collumn + 1) * (1 / NumHorizontalTiles);
	
}