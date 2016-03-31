#pragma once

#include <SOIL\SOIL.h>
#include "glad.h"

class Texture
{
public:
	Texture();
	~Texture();

	void loadFromFile(const char* filepath);
	void unload();

	void bind();
	void unbind();

private:
	GLuint tex_2d;
};

