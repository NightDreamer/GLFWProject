#include "Main.h"
#include <stdlib.h>
#include "MainMenu.h"

int main(int argc, char* argv[])
{
	Window window;
	window.initialise();

	MainMenu mainmenu;
	mainmenu.onInit();

	float last = static_cast<float>(glfwGetTime());
	float delta = 0.0f;

	while (!window.shouldClose())
	{
		float current = static_cast<float>(glfwGetTime());
		delta = current - last;
		last = current;

		window.pollEvents();
		mainmenu.onTick(delta);
		mainmenu.onRender(delta);
		window.swapBuffers();
	}

	mainmenu.onDispose();

	window.dispose();
	exit(EXIT_SUCCESS);
}

