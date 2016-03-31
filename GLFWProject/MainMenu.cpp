#include "MainMenu.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}


void MainMenu::onInit()
{
	background.loadFromFile("data//textures//test.png");
}


void MainMenu::onDispose()
{
	background.unload();
}


void MainMenu::onTick(float delta)
{
}


void MainMenu::onRender(float delta)
{
}

