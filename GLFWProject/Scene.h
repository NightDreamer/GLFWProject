#pragma once

struct GLFWwindow;

class Scene
{
public:
	Scene() {};
	~Scene() {};

	virtual void onInit() = 0;
	virtual void onDispose() = 0;

	virtual void onTick(float delta, GLFWwindow* window) = 0;
	virtual void onRender(float delta) = 0;
};

