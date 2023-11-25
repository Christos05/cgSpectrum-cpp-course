#include "Player.h"

Player::Player()
	: Character()
{

}
Player::~Player()
{

}

void Player::MoveTo(int x, int y)
{
	SetXPosition(x);
	SetYPosition(y);
}
void Player::Jump(int amount)
{
	jumping = true;
	maxJumpBlocks = amount;
}