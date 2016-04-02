#pragma once
#include <vector>
#include "glad.h"
#include <GLFW\glfw3.h>

namespace Callback
{
	void Error(int error, const char* description);
};

class GameState;

class GameEngine
{
public:

	void Init();
	void Cleanup();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update(float delta);
	void Draw(float delta);

	bool Running() { return glfwWindowShouldClose(m_window) == 0; }

private:
	// the stack of states
	std::vector<GameState*> states = std::vector<GameState*>();
	GLFWwindow* m_window = nullptr;
};
