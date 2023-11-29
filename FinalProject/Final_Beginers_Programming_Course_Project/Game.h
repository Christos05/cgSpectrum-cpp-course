#pragma once
#include "Player.h"
#include "Level.h"

class Game
{
	Player m_player;
	Level m_level;

	bool m_isGameOver;
	bool m_userQuit;

public:
	Game();
	~Game();

	bool Load();
	void Run();

	bool IsGameOver();
	bool DidUserQuit() { return m_userQuit; }
	int GetPlayerLives() { return m_player.GetLives(); }


private:
	bool Update();
	void Draw();

	bool HandleCollision(int newPlayerX, int newPlayerY);
};