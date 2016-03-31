#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Entity.h"
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu();

	void onInit() override;
	void onDispose() override;

	void onTick(float delta, GLFWwindow* window) override;
	void onRender(float delta) override;

private:
	Shader shader2D;

	Entity player;
	Entity player_name;

	Entity enemy;
	Entity enemy_name;

	glm::mat4 projection;
};

