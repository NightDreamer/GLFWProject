#include <stdio.h>
#include "GameEngine.h"
#include "GameState.h"

void Callback::Error(int error, const char* description)
{
	fputs(description, stderr);
}

void GameEngine::Init()
{
	glfwSetErrorCallback(Callback::Error);

	// GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	m_window = glfwCreateWindow(mode->width, mode->height, "GLFW Project", glfwGetPrimaryMonitor(), NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// OpenGL
	if (!gladLoadGL())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	printf("OpenGL Version %d.%d loaded \n", GLVersion.major, GLVersion.minor);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	printf("GameEngine Init\n");
}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	if (m_window)
		glfwDestroyWindow(m_window);

	printf("GameEngine Cleanup\n");

	// shutdown GLFW
	glfwTerminate();
}

void GameEngine::ChangeState(GameState* state)
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(m_window);

}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(m_window);
}

void GameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void GameEngine::HandleEvents()
{
	// let the state handle events
	if (!states.empty()) {
		states.back()->HandleEvents(this);
	}
}

void GameEngine::Update(float delta)
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window, true);

	glfwPollEvents();

	// let the state update the game
	if (!states.empty()) {
		states.back()->Update(this, delta);
	}
}

void GameEngine::Draw(float delta)
{
	// let the state draw the screen
	if (!states.empty()) {
		states.back()->Draw(this, delta);
	}

	glfwSwapBuffers(m_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
