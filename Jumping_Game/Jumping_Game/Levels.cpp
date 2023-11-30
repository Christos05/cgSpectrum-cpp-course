#include <iostream>
#include "Levels.h"
#include "Player.h"

Levels::Levels()
	: levelPivot(0)
	, MaxLevelWidth(0)
	, MaxLevelHeight(0)
{

}
Levels::~Levels()
{

}

void Levels::UpdateMaxLevelSizes(vector<vector<char>> Level)
{
	SetMaxLevelHeight(Level.size());
	SetMaxLevelWidth(Level[1].size());
}

void Levels::HandlePivot(Player myPlayer)
{
	if (myPlayer.positionX >= levelScreenWidth / 2 + levelPivot)
	{
		if (levelScreenWidth + levelPivot + 1 <= MaxLevelWidth)
		{
			levelPivot++;
		}
	}
	if (myPlayer.positionX <= levelScreenWidth / 2 + levelPivot && myPlayer.positionX >= levelScreenWidth / 2)
	{
		if (levelScreenWidth + levelPivot - 1 <= MaxLevelWidth)
		{
			levelPivot--;
		}
	}
}