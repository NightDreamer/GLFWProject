
#pragma once
#include "GameEngine.h"

class GameState
{
public:
	virtual void Init(GLFWwindow* window) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine* game) = 0;
	virtual void Update(GameEngine* game, float delta) = 0;
	virtual void Draw(GameEngine* game, float delta) = 0;

	void ChangeState(GameEngine* game, GameState* state) {
		game->ChangeState(state);
	}

protected:
	GameState() { }
};
