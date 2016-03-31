#pragma once

#include "glad.h"
#include <GLFW\glfw3.h>

namespace Callback
{
	void Error(int error, const char* description);
};

class Window
{
public:
	Window();
	~Window();

	void initialise();
	void dispose();

	void pollEvents();
	void swapBuffers();

	bool shouldClose();

	GLFWwindow* getGLFWwindow() { return m_window; };

private:
	GLFWwindow* m_window = nullptr;
};

