#include "MainMenu.h"
#include "InGame.h"

void MainMenu::Init(GLFWwindow* window)
{
	this->window = window;
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);

	shader2D.load("data//shader//texture_shader.vert", "data//shader//texture_shader.frag");
	projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

	heading.initialise("data//textures//heading.png", (static_cast<float>(width) - 512.0f) * 0.5f, (static_cast<float>(height) - 64.0f) * 0.5f, 512.0f, 512.0f);
	start.initialise("data//textures//startmsg.png", (static_cast<float>(width) - 512.0f) * 0.5f, 64.0f, 512.0f, 64.0f);
}

void MainMenu::Cleanup()
{
	start.dispose();
	heading.dispose();
	shader2D.dispose();
}

void MainMenu::Pause()
{

}

void MainMenu::Resume()
{

}

void MainMenu::HandleEvents(GameEngine* game)
{

}

float alpha = 1.0f;
bool dir = true;

void MainMenu::Update(GameEngine* game, float delta)
{
	if (glfwGetKey(window, GLFW_KEY_ENTER))
		this->ChangeState(game, new InGame());

	if (alpha <= 0.25f)
	{
		alpha = 0.25f;
		dir = false;
	}
	else if (alpha >= 1.0f)
	{
		alpha = 1.0f;
		dir = true;
	}

	if (dir)
		alpha -= delta * 1.5f;
	else
		alpha += delta * 1.5f;

	start.setColor(glm::vec4(1.0f, 1.0f, 1.0f, alpha));
}

void MainMenu::Draw(GameEngine* game, float delta)
{
	shader2D.bind();
	glUniformMatrix4fv(glGetUniformLocation(shader2D.getProgram(), "projection"), 1, false, glm::value_ptr(projection));
	glUniform4fv(glGetUniformLocation(shader2D.getProgram(), "color"), 1, glm::value_ptr(glm::vec4(1.0f)));
	{
		heading.draw();

		glUniform4fv(glGetUniformLocation(shader2D.getProgram(), "color"), 1, glm::value_ptr(start.getColor()));
		start.draw();
	}
	shader2D.unbind();
}
