#pragma once
#include "Levels.h"
#include "Player.h"

class Game
{
	Player myPlayer;
	Levels myLevel;

	bool finishedLevel;
	bool finishedGame;

public:
	Game();
	~Game();

	void DrawFrame(int Level);
	void Update(int Level);
	bool Collition(int x, int y, vector<vector<char>> level);

	bool IsLevelFinished() { return finishedLevel; }
	bool IsGameFinished() { return finishedGame; }
};