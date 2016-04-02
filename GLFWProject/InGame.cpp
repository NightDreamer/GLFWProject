#include "InGame.h"

#define MOVEMENT_SPEED 16.0f
#define BUMPINESS 1.0f
#define FRACTION 2.0f

void InGame::Init(GLFWwindow* window)
{
	this->window = window;
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);

	shader2D.load("data//shader//texture_shader.vert", "data//shader//texture_shader.frag");
	projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

	player.initialise("data//textures//player.png", 0.0f, (static_cast<float>(height) - 128.0f) * 0.5f, 128.0f, 128.0f);
	player_name.initialise("data//textures//player_name.png", 0.0f, (static_cast<float>(height) - 128.0f) * 0.5f, 128.0f, 128.0f);
	enemy.initialise("data//textures//enemy.png", static_cast<float>(width) - 128.0f, (static_cast<float>(height) - 128.0f) * 0.5f, 128.0f, 128.0f);
	enemy_name.initialise("data//textures//enemy_name.png", static_cast<float>(width) - 128.0f, (static_cast<float>(height) - 128.0f) * 0.5f, 128.0f, 128.0f);
}

void InGame::Cleanup()
{
	enemy.dispose();
	enemy_name.dispose();

	player.dispose();
	player_name.dispose();

	shader2D.dispose();
}

void InGame::Pause()
{

}

void InGame::Resume()
{

}

void InGame::HandleEvents(GameEngine* game)
{

}

void InGame::Update(GameEngine* game, float delta)
{
	// Player
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		player.accelerate(-delta * MOVEMENT_SPEED, 0.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_D))
	{
		player.accelerate(delta * MOVEMENT_SPEED, 0.0f);

	}
	else
	{
		player.accelerate(-delta * player.getAcceleration().x * 2.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		player.accelerate(0.0f, -delta * MOVEMENT_SPEED);
	}
	else if (glfwGetKey(window, GLFW_KEY_W))
	{
		player.accelerate(0.0f, delta * MOVEMENT_SPEED);
	}
	else
	{
		player.accelerate(0.0f, -delta * player.getAcceleration().y  * 2.0f);
	}

	// Enemy
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		enemy.accelerate(-delta * MOVEMENT_SPEED, 0.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		enemy.accelerate(delta * MOVEMENT_SPEED, 0.0f);

	}
	else
	{
		enemy.accelerate(-delta * enemy.getAcceleration().x * FRACTION, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		enemy.accelerate(0.0f, -delta * MOVEMENT_SPEED);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP))
	{
		enemy.accelerate(0.0f, delta * MOVEMENT_SPEED);
	}
	else
	{
		enemy.accelerate(0.0f, -delta * enemy.getAcceleration().y  * FRACTION);
	}

	// Game logic
	if (enemy.collide(&player))
	{
		glm::vec2 accelPlayer = glm::vec2(player.getAcceleration().x, player.getAcceleration().y);
		glm::vec2 accelEnemy = glm::vec2(enemy.getAcceleration().x, enemy.getAcceleration().y);

		enemy.collided(accelPlayer * BUMPINESS);
		player.collided(accelEnemy * BUMPINESS);
	}

	// TODO: check if anyone is outside the screen -> GAME OVER, BITCH!

	// General logic
	enemy.update(delta);
	enemy_name.setPosition(enemy.getPosition() + glm::vec2(0.0f, 96.0f));

	player.update(delta);
	player_name.setPosition(player.getPosition() + glm::vec2(0.0f, 96.0f));
}

void InGame::Draw(GameEngine* game, float delta)
{
	shader2D.bind();
	glUniformMatrix4fv(glGetUniformLocation(shader2D.getProgram(), "projection"), 1, false, glm::value_ptr(projection));
	glUniform4fv(glGetUniformLocation(shader2D.getProgram(), "color"), 1, glm::value_ptr(glm::vec4(1.0f)));
	{
		player.draw();
		player_name.draw();
		enemy.draw();
		enemy_name.draw();
	}
	shader2D.unbind();
}
