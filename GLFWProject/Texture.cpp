#include "Texture.h"
#include <iostream>


Texture::Texture()
{
}


Texture::~Texture()
{
}


void Texture::loadFromFile(const char* filepath)
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &tex_2d);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_2d);

	int width = 0, height = 0;
	unsigned char* image = SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	std::cout << std::endl << "Width: " << width << ", Height: " << height << std::endl;
	std::cout << "Image ID: " << tex_2d << std::endl;

	SOIL_free_image_data(image);

	if (tex_2d == -1)
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
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


