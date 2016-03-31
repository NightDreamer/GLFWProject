#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Sprite.h"
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

	void onTick(float delta) override;
	void onRender(float delta) override;

private:
	Shader shader2D;
	Sprite test;

	glm::mat4 projection;
};

