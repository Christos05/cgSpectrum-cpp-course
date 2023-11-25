#include "Game.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

constexpr int arrowRight = 100;
constexpr int arrowLeft = 97;
constexpr int arrowUp = 119;
constexpr int Space = 32;

void Draw(vector<vector<char>> level, int levelPivot, int levelWidth, int levelHeight, Player* myPlayer);
vector<vector<char>> GetLevel(int level, Levels myLevel);

Game::Game()
	: finishedLevel(false)
	, finishedGame(false)
{

}
Game::~Game()
{

}


void Game::DrawFrame(int Level)
{
	if (myLevel.levelNeedsReDraw)
	{
		myLevel.levelNeedsReDraw = false;
		system("cls");

		int newXGeneral = 0;
		int newYGeneral = 0;
		newXGeneral = myPlayer.positionX;
		newYGeneral = myPlayer.positionY + 1;
		if (!Collition(newXGeneral, newYGeneral, GetLevel(Level, myLevel)))
		{
			myPlayer.falling = true;
		}

		if (myPlayer.falling == true)
		{
			int newXFalling = 0;
			int newYFalling = 0;
			newXFalling = myPlayer.positionX;
			newYFalling = myPlayer.positionY + 1;
			if (!Collition(newXFalling, newYFalling, GetLevel(Level, myLevel)))
			{
				myPlayer.MoveTo(newXFalling, newYFalling);
				myLevel.levelNeedsReDraw = true;
			}
			else
			{
				myPlayer.falling = false;
			}
		}

		int newX = 0;
		int newY = 0;
		newX = myPlayer.positionX+myPlayer.lastDirection;
		newY = myPlayer.positionY-1;
		if (myPlayer.jumping == true && myPlayer.maxJumpBlocks != 0 && !Collition(newX, newY, GetLevel(Level, myLevel)))
		{
			myLevel.levelNeedsReDraw = true;
			myPlayer.maxJumpBlocks -= 1;
			myPlayer.MoveTo(newX, newY);
		}
		else
		{
			if (myPlayer.jumping == true)
			{
				myPlayer.falling = true;
				myLevel.levelNeedsReDraw = true;
			}
			myPlayer.jumping = false;
		}
		
		Draw(GetLevel(Level, myLevel), myLevel.levelPivot, myLevel.levelWidth, myLevel.levelHeight, &myPlayer);
	}

	Update(Level);
}

void Game::Update(int Level)
{
	if (myPlayer.inLevel && myPlayer.jumping == false && myPlayer.falling == false)
	{
		int input = _getch();
		int newX = 0;
		int newY = 0;
		if (input == arrowRight)
		{
			myPlayer.lastDirection = 1;
			newX = myPlayer.positionX + 1;
			newY = myPlayer.positionY;
			if (!Collition(newX, newY, GetLevel(Level, myLevel)))
			{
				myPlayer.MoveTo(newX, newY);
				myLevel.levelNeedsReDraw = true;
			}
		}
		else if (input == arrowLeft)
		{
			myPlayer.lastDirection = -1;
			newX = myPlayer.positionX - 1;
			newY = myPlayer.positionY;
			if (!Collition(newX, newY, GetLevel(Level, myLevel)))
			{
				myPlayer.MoveTo(newX, newY);
				myLevel.levelNeedsReDraw = true;
			}
		}
		else if (input == arrowUp || input == Space)
		{
			myPlayer.Jump(3);
			myLevel.levelNeedsReDraw = true;
		}
	}
}

bool Game::Collition(int x, int y, vector<vector<char>> level)
{
	if (x < 0 || y < 0 || x > myLevel.levelWidth-1 || y > myLevel.levelHeight-1)
	{
		return true;
	}
	if (level[y][x] == ' ' || level[y][x] == '@' || level[y][x] == '|' || level[y][x] == '_')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Draw(vector<vector<char>> level, int levelPivot, int levelWidth, int levelHeight, Player* myPlayer)
{
	for (int y = 0; y < level.size(); y++)
	{
		for (int x = levelPivot; x < level[y].size(); x++)
		{
			if (x + 1 <= levelWidth && y + 1 <= levelHeight)
			{
				if (level[y][x] == '@')
				{
					if (!myPlayer->inLevel)
					{
						myPlayer->SetXPosition(x);
						myPlayer->SetYPosition(y);
						myPlayer->SetInLevel(true, myPlayer);
					}
					
					if (myPlayer->positionX == x && myPlayer->positionY == y)
					{
						cout << '@';
					}
					else
					{
						cout << ' ';
					}
				}
				else
				{
					if (myPlayer->positionX == x && myPlayer->positionY == y && myPlayer->inLevel)
					{
						cout << '@';
					}
					else
					{
						cout << level[y][x];
					}
				}
				
			}
		}
		cout << endl;
	}
}

vector<vector<char>> GetLevel(int level, Levels myLevel)
{
	if (level == 1)
	{
		return myLevel.Level1;
	}
	return myLevel.Level1;
}