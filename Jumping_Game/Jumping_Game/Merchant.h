#pragma once
#include "Character.h"

class Merchant : public Character
{
public:
	Merchant(int y, int x)
		: Character()
	{
		positionY = y;
		positionX = x;
	}

	virtual CharacterType GetType() override { return CharacterType::merchant; }
};