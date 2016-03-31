#include "Window.h"
#include <stdlib.h>
#include <iostream>


void Callback::Error(int error, const char* description)
{
	fputs(description, stderr);
}


Window::Window()
{
}


Window::~Window()
{
}


void Window::initialise()
{
	glfwSetErrorCallback(Callback::Error);

	// GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	printf("OpenGL Version %d.%d loaded", GLVersion.major, GLVersion.minor);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}


void Window::dispose()
{
	if(m_window)
		glfwDestroyWindow(m_window);

	glfwTerminate();
}

void Window::pollEvents()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window, true);
	
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_window) != 0;
}

