#include "GameOver.h"
#include "MainMenu.h"

void GameOver::Init(GLFWwindow* window)
{
	this->window = window;
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);

	shader2D.load("data//shader//texture_shader.vert", "data//shader//texture_shader.frag");
	projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

	if (player == 0)
	{
		winner.initialise("data//textures//winnerA.png", (static_cast<float>(width) - 1024.0f) * 0.5f, (static_cast<float>(height) - 1024.0f) * 0.5f, 1024.0f, 1024.0f);
	}
	else
	{
		winner.initialise("data//textures//winnerB.png", (static_cast<float>(width) - 1024.0f) * 0.5f, (static_cast<float>(height) - 1024.0f) * 0.5f, 1024.0f, 1024.0f);
	}

	printf("GameOver initialised\n");
}

void GameOver::Cleanup()
{
	winner.dispose();
	shader2D.dispose();

	printf("GameOver cleaned up\n");
}

void GameOver::Pause()
{

}

void GameOver::Resume()
{

}

void GameOver::HandleEvents(GameEngine* game)
{

}

float time = 0.0f;

void GameOver::Update(GameEngine* game, float delta)
{
	time += delta;

	if (time >= 2500.0f)
		ChangeState(game, new MainMenu());
}

void GameOver::Draw(GameEngine* game, float delta)
{
	shader2D.bind();
	glUniformMatrix4fv(glGetUniformLocation(shader2D.getProgram(), "projection"), 1, false, glm::value_ptr(projection));
	glUniform4fv(glGetUniformLocation(shader2D.getProgram(), "color"), 1, glm::value_ptr(glm::vec4(1.0f)));
	{
		winner.draw();
	}
	shader2D.unbind();
}
