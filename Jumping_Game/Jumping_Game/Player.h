#pragma once
#include "Character.h"

class Player : public Character
{
public:
	bool inLevel = false;
	bool jumping = false;
	bool falling = false;
	int maxJumpBlocks = 0;
	int lastDirection = 1;

	int Coins = 0;
	int TimesCanHeal = 3;
	int MaxTimesCanHeal = 3;

	void MoveTo(int x, int y);
	void Jump(int amount);

	CharacterType GetType() { return CharacterType::player; }

	Player();
	~Player();
};