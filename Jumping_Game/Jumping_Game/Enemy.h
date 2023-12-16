#pragma once
#include "Character.h"



class Enemy : public Character
{

public:
	Enemy(int y, int x)
		: Character()
	{
		positionY = y;
		positionX = x;

		int healthVariant = (10 * x)/2;
		int DamageVariant = (2 * x) / 2;
		maxHealth = healthVariant;
		health = healthVariant;
		damage = DamageVariant;
		NextMove = EnemyState::Attacking;
	}

	virtual CharacterType GetType() override { return CharacterType::enemy; }
};