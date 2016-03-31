#include "MainMenu.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}


void MainMenu::onInit()
{
	shader2D.load("data//shader//texture_shader.vert", "data//shader//texture_shader.frag");
	test.initialise("data//textures//test.png", 512.0f, 512.0f, 128.0f, 128.0f);

	projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
}


void MainMenu::onDispose()
{
	test.dispose();
	shader2D.dispose();
}


void MainMenu::onTick(float delta)
{

}


void MainMenu::onRender(float delta)
{
	shader2D.bind();
	glUniformMatrix4fv(glGetUniformLocation(shader2D.getProgram(), "projection"), 1, false, glm::value_ptr(projection));
	{
		test.draw();
	}
	shader2D.unbind();
}

