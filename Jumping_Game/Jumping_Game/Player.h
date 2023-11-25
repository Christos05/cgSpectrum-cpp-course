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

	void MoveTo(int x, int y);
	void Jump(int amount);

	Player();
	~Player();
};