#pragma once
#include "GameState.h"
#include "Shader.h"
#include "Entity.h"
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class GameOver : public GameState
{
public:
	GameOver(int p) { player = p; };

	void Init(GLFWwindow* window) override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

	void HandleEvents(GameEngine* game) override;
	void Update(GameEngine* game, float delta) override;
	void Draw(GameEngine* game, float delta) override;

private:
	Shader shader2D;
	glm::mat4 projection;
	GLFWwindow* window;

	Entity winner;

	// 0 = Player A, 1 = Player B
	int player;
};

