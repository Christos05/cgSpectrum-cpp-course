#pragma once

class Player;

class Character
{
public:
	int maxHealth = 100;
	int health = 100;
	int damage = 100;
	int positionX = 0;
	int positionY = 0;

	Character();
	~Character();

	void Heal(int amount);
	void Damage(int amount);
	void SetXPosition(int x);
	void SetYPosition(int y);
	void SetInLevel(bool inLevelBool, Player* myPlayer);
};