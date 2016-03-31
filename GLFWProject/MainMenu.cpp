#include "MainMenu.h"
#include <GLFW\glfw3.h>
#include <windows.h>

#define MOVEMENT_SPEED 16.0f
#define BUMPINESS 1.0f

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}


void MainMenu::onInit()
{
	shader2D.load("data//shader//texture_shader.vert", "data//shader//texture_shader.frag");

	player.initialise("data//textures//player.png", 0.0f, 540.0f, 128.0f, 128.0f);
	player_name.initialise("data//textures//player_name.png", 0.0f, 604.0f, 128.0f, 128.0f);

	enemy.initialise("data//textures//enemy.png", 1792.0f, 540.0f, 128.0f, 128.0f);
	enemy_name.initialise("data//textures//enemy_name.png", 1792.0f, 604.0f, 128.0f, 128.0f);

	projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
}


void MainMenu::onDispose()
{
	enemy.dispose();
	enemy_name.dispose();

	player.dispose();
	player_name.dispose();

	shader2D.dispose();
}


void MainMenu::onTick(float delta, GLFWwindow* window)
{
	// Player
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		player.accelerate(-delta * MOVEMENT_SPEED, 0.0f);
	}
	else if(glfwGetKey(window, GLFW_KEY_D))
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
		enemy.accelerate(-delta * enemy.getAcceleration().x * 2.0f, 0.0f);
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
		enemy.accelerate(0.0f, -delta * enemy.getAcceleration().y  * 2.0f);
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
	enemy_name.setPosition(enemy.getPosition() + glm::vec2(0.0f, 64.0f));

	player.update(delta);
	player_name.setPosition(player.getPosition() + glm::vec2(0.0f, 64.0f));
}


void MainMenu::onRender(float delta)
{
	shader2D.bind();
	glUniformMatrix4fv(glGetUniformLocation(shader2D.getProgram(), "projection"), 1, false, glm::value_ptr(projection));
	{
		player.draw();
		player_name.draw();
		enemy.draw();
		enemy_name.draw();
	}
	shader2D.unbind();
}

