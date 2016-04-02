#include "Main.h"
#include <stdlib.h>
#include "MainMenu.h"

int main(int argc, char* argv[])
{
	GameEngine engine;
	engine.Init();
	engine.ChangeState(new MainMenu());

	float last = static_cast<float>(glfwGetTime());
	float delta = 0.0f;

	while (engine.Running())
	{
		float current = static_cast<float>(glfwGetTime());
		delta = current - last;
		last = current;

		engine.HandleEvents();
		engine.Update(delta);
		engine.Draw(delta);
	}

	engine.Cleanup();
	exit(EXIT_SUCCESS);
}

