#pragma once
#include "Texture.h"
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	void initialise(const char* filepath, float x, float y, float width, float height);
	void draw();
	void dispose();

	bool collide(Entity* other);
	void collided(glm::vec2 impulse);
	void update(float delta);

	void setPosition(float x, float y);
	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition() { return pos; };

	void accelerate(float x, float y);
	glm::vec2 getAcceleration() { return acceleration; };

	void setColor(glm::vec4 c) { color = c; };
	glm::vec4 getColor() { return color; };

	glm::vec2 getSize() { return size; };

private:
	void setPosition();

private:
	Texture m_texture;

	glm::vec2 old_pos;
	glm::vec2 pos;
	glm::vec2 size;

	glm::vec2 acceleration;

	glm::vec4 color = glm::vec4(1.0f);

	GLuint m_vao;
	GLuint m_vbo;
};

