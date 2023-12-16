#pragma once

class Player;

enum class CharacterType
{
	player,
	enemy,
	merchant,
};

enum class EnemyState
{
	Nothing,
	Attacking,
	Healing,
	HardHitting,
};

class Character
{
public:
	int maxHealth = 100;
	int health = 100;
	int damage = 15;
	int positionX = 0;
	int positionY = 0;

	int CritDamage = 75;
	int CritRate = 25;
	int GuardDamage = 25;
	int HealAmount = 50;

	bool dead = false;

	EnemyState NextMove = EnemyState::Nothing;

	Character();
	~Character();

	void Heal(int amount);
	void Damage(int amount);
	void SetXPosition(int x);
	void SetYPosition(int y);
	void SetInLevel(bool inLevelBool, Player* myPlayer);

	virtual CharacterType GetType() = 0;
};