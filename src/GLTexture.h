#ifndef _GL_TEXTURE
#define _GL_TEXTURE

#include <GL/gl3w.h>

struct GLTexture
{
	int		Width		= 0;
	int		Height		= 0;
	int		Channels	= 0;
	GLuint	Id			= 0;

	void Load(char* FilePath);
};

struct GLTextureRegion
{
	float		Width		= 0.f;
	float		Height		= 0.f;
	float		U0			= 0.f;
	float		V0			= 0.f;
	float		U1			= 0.f;
	float		V1			= 0.f;
	GLTexture	Texture;

	GLTextureRegion(GLTexture Atlas, float Width, float Height, float Row, float Collumn);
};

#endif 