#pragma once

#include "Texture.h"
#include <glm\vec2.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	void initialise(const char* filepath, float x, float y, float width, float height);
	void draw();
	void dispose();

	void accelerate(float x, float y);

	bool collide(Entity* other);

	void collided(glm::vec2 impulse);
	void update(float delta);

	glm::vec2 getAcceleration() { return acceleration; };

private:
	void setPosition();

private:
	Texture m_texture;

	glm::vec2 old_pos;
	glm::vec2 pos;
	glm::vec2 size;

	glm::vec2 acceleration;

	GLuint m_vao;
	GLuint m_vbo;
};

