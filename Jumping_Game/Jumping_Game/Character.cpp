#include "Character.h"
#include "Player.h"

Character::Character()
{

}
Character::~Character()
{

}

void Character::Heal(int amount)
{
	if (health += amount > maxHealth)
	{
		health = maxHealth;
	}
	else
	{
		health += amount;
	}
}
void Character::Damage(int amount)
{
	if (health -= amount < 0)
	{
		health = 0;
	}
	else
	{
		health -= amount;
	}
}
void Character::SetXPosition(int x)
{
	positionX = x;
}
void Character::SetYPosition(int y)
{
	positionY = y;
}
void Character::SetInLevel(bool inLevelBool, Player* myPlayer)
{
	myPlayer->inLevel = inLevelBool;
}