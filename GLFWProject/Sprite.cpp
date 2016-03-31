#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::initialise(const char * filepath, float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;
	m_w = width;
	m_h = height;

	m_texture.loadFromFile(filepath);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	float vertices[] = {
		// Left bottom triangle
		m_x, m_y + m_h, 0.0f, 0.0f,
		m_x, m_y, 0.0f, 1.0f,
		m_x + m_w, m_y, 1.0f, 1.0f,
		// Right top triangle
		m_x + m_w, m_y,  1.0f, 1.0f,
		m_x + m_w, m_y + m_h,  1.0f, 0.0f,
		m_x, m_y + m_h, 0.0f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &vertices, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::draw()
{
	m_texture.bind();
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_texture.unbind();
}


void Sprite::dispose()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);

	m_texture.unload();
}

void Sprite::setPosition(float x, float y)
{
	m_x = x; m_y = y;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	float vertices[] = {
		// Left bottom triangle
		m_x, m_y + m_h, 0.0f, 0.0f,
		m_x, m_y, 0.0f, 1.0f,
		m_x + m_w, m_y, 1.0f, 1.0f,
		// Right top triangle
		m_x + m_w, m_y,  1.0f, 1.0f,
		m_x + m_w, m_y + m_h,  1.0f, 0.0f,
		m_x, m_y + m_h, 0.0f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::addPosition(float x, float y)
{
	this->setPosition(m_x + x, m_y + y);
}
