#pragma once

#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void initialise(const char* filepath, float x, float y, float width, float height);
	void draw();
	void dispose();

	void setPosition(float x, float y);
	void addPosition(float x, float y);

private:
	Texture m_texture;

	float m_x, m_y, m_w, m_h;

	GLuint m_vao;
	GLuint m_vbo;
};

