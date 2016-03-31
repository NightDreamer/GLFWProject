#include "Entity.h"
#include <glm\glm.hpp>


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::initialise(const char * filepath, float x, float y, float width, float height)
{
	acceleration = glm::vec2(0.0f);
	old_pos = pos = glm::vec2(x, y);
	size = glm::vec2(width, height);
	m_texture.loadFromFile(filepath);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	float vertices[] = {
		// Left bottom triangle
		pos.x, pos.y + size.y, 0.0f, 0.0f,
		pos.x, pos.y, 0.0f, 1.0f,
		pos.x + size.x, pos.y, 1.0f, 1.0f,
		// Right top triangle
		pos.x + size.x, pos.y,  1.0f, 1.0f,
		pos.x + size.x, pos.y + size.y,  1.0f, 0.0f,
		pos.x, pos.y + size.y, 0.0f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Entity::draw()
{
	m_texture.bind();
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_texture.unbind();
}


void Entity::dispose()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	m_texture.unload();
}

void Entity::setPosition()
{
	old_pos = pos;
	pos += acceleration;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	float vertices[] = {
		// Left bottom triangle
		pos.x, pos.y + size.y, 0.0f, 0.0f,
		pos.x, pos.y, 0.0f, 1.0f,
		pos.x + size.x, pos.y, 1.0f, 1.0f,
		// Right top triangle
		pos.x + size.x, pos.y,  1.0f, 1.0f,
		pos.x + size.x, pos.y + size.y,  1.0f, 0.0f,
		pos.x, pos.y + size.y, 0.0f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, &vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Entity::accelerate(float x, float y)
{
	acceleration += glm::vec2(x, y);

	if (acceleration.x > 16.0f)
		acceleration.x = 16.0f;
	if (acceleration.x < -16.0f)
		acceleration.x = -16.0f;

	if (acceleration.y > 16.0f)
		acceleration.y = 16.0f;
	if (acceleration.y < -16.0f)
		acceleration.y = -16.0f;
}

bool Entity::collide(Entity* other)
{
	glm::vec2 centerA = glm::vec2(pos.x + (0.5f * size.x), pos.y + (0.5f * size.y));
	glm::vec2 centerB = glm::vec2(other->pos.x + (0.5f * other->size.x), other->pos.y + (0.5f * other->size.y));

	float x, y, dist;
	x = centerA.x - (centerB.x);
	y = (centerA.y - (centerB.y));
	dist = glm::sqrt(glm::pow(x, 2) + glm::pow(y, 2));
	return dist < (0.5f * size.x) + (0.5f * other->size.x);
}

void Entity::collided(glm::vec2 impulse)
{
	this->acceleration = impulse;
}

void Entity::update(float delta)
{
	this->setPosition();
}
