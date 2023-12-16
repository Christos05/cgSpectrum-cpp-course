#pragma once
#include "Levels.h"
#include "Player.h"
#include "Enemy.h"
#include "AudioManager.h"
#include "Character.h"
#include <string>
#include <vector>

enum class ScreenOutput
{
	MainMenu,
	Game,
	Battle,
	Shop,
};

class Game
{
	Player myPlayer;
	Levels myLevel;
	AudioManager myAudio;

	vector<Character*> Characters;

	bool finishedLevel;
	bool finishedGame;

	int Cicle = 1;

public:
	ScreenOutput ScreenType = ScreenOutput::Game;
	Character* BattlingEnemy;

	Game();
	~Game();

	void LoadLevel(int Level);
	void DrawFrame(int Level);
	void Update(int Level);
	void MoveLeft(int Level, int newX, int newY);
	void MoveRight(int Level, int newX, int newY);
	void MoveDown(int Level, int newXFalling, int newYFalling);
	void HandleJumping(int Level, int newX, int newY);

	void HandleDrawing(int level);
	void DrawGame(vector<vector<char>> level);
	void DrawBattle();
	void DrawShop();
	void EnemysTurn();

	bool Collition(int x, int y, vector<vector<char>> level);
	bool AnyCharactersClose();

	Character* ClosestCharacter();

	bool CanUpdateGame();
	bool CanUpdateBattle();
	bool IsLevelFinished() { return finishedLevel; }
	bool IsGameFinished() { return finishedGame; }
};