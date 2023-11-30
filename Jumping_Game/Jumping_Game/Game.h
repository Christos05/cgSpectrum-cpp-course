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
	void MoveLeft(int Level, int newX, int newY);
	void MoveRight(int Level, int newX, int newY);
	void MoveDown(int Level, int newXFalling, int newYFalling);
	void HandleJumping(int Level, int newX, int newY);

	bool Collition(int x, int y, vector<vector<char>> level);

	bool CanUpdate();
	bool IsLevelFinished() { return finishedLevel; }
	bool IsGameFinished() { return finishedGame; }
};