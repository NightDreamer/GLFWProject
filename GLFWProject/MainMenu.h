#pragma once
#include "Scene.h"
#include "Texture.h"


class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu();

	void onInit() override;
	void onDispose() override;

	void onTick(float delta) override;
	void onRender(float delta) override;

private:
	Texture background;
};

