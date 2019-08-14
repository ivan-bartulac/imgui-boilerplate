#ifndef _GL_TEXTURE
#define _GL_TEXTURE

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <GL/gl3w.h>

struct GLTexture
{
	int		Width		= 0;
	int		Height		= 0;
	int		Channels	= 0;
	GLuint	Id			= 0;

	void Load(char* FilePath)
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
};

#endif 