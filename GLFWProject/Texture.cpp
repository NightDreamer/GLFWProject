#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}


void Texture::loadFromFile(const char * filepath)
{
	tex_2d = SOIL_load_OGL_texture(
				filepath,
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			 );
}


void Texture::unload()
{
	this->unbind();
	glDeleteTextures(1, &tex_2d);
}


void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
}


void Texture::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


