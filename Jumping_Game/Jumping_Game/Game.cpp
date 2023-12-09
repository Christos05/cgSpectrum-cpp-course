#include "Game.h"
#include "Player.h"
#include "Levels.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

constexpr int arrowRight = 100;
constexpr int arrowLeft = 97;
constexpr int arrowUp = 119;
constexpr int Space = 32;
constexpr int LeftArrowKey = 75;
constexpr int RightArrowKey = 77;

void Draw(vector<vector<char>> level, int levelPivot, int levelWidth, int levelHeight, Player* myPlayer, Levels myLevel);
vector<vector<char>> GetLevel(int level, Levels myLevel);
void SetColor(char character);

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

		//Falling System
		int newXGeneral = 0;
		int newYGeneral = 0;
		newXGeneral = myPlayer.positionX;
		newYGeneral = myPlayer.positionY + 1;
		MoveDown(Level, newXGeneral, newYGeneral);

		//Jumping System
		int newX = 0;
		int newY = 0;
		newX = myPlayer.positionX+myPlayer.lastDirection;
		newY = myPlayer.positionY-1;
		HandleJumping(Level, newX, newY);
		
		//Draw The Level
		myLevel.UpdateMaxLevelSizes(GetLevel(Level, myLevel));
		myLevel.HandlePivot(myPlayer);
		Draw(GetLevel(Level, myLevel), myLevel.levelPivot, myLevel.levelScreenWidth, myLevel.levelScreenHeight, &myPlayer, myLevel);
	}
	Update(Level);
}

void Game::Update(int Level)
{
	if (CanUpdate())
	{
		int input = _getch();
		int newX = 0;
		int newY = 0;
		
		if (input == arrowRight)
		{
			if (myPlayer.lastDirection == -1)
			{
				myPlayer.lastDirection = 1;
				myLevel.levelNeedsReDraw = true;
			}
			newX = myPlayer.positionX + 1;
			newY = myPlayer.positionY;
			MoveRight(Level, newX, newY);
		}
		else if (input == arrowLeft)
		{
			if (myPlayer.lastDirection == 1)
			{
				myPlayer.lastDirection = -1;
				myLevel.levelNeedsReDraw = true;
			}
			newX = myPlayer.positionX - 1;
			newY = myPlayer.positionY;
			MoveLeft(Level, newX, newY);
		}
		else if (input == arrowUp || input == Space)
		{
			myPlayer.Jump(3);
			myLevel.levelNeedsReDraw = true;
		}
		else if (input == RightArrowKey)
		{
			if (myPlayer.lastDirection == -1)
			{
				myPlayer.lastDirection = 1;
				myLevel.levelNeedsReDraw = true;
			}
		}
		else if (input == LeftArrowKey)
		{
			if (myPlayer.lastDirection == 1)
			{
				myPlayer.lastDirection = -1;
				myLevel.levelNeedsReDraw = true;
			}
		}
	}
}

bool Game::Collition(int x, int y, vector<vector<char>> level)
{
	if (x < 0 + myLevel.levelPivot || y < 0 || x > myLevel.levelScreenWidth -1 + myLevel.levelPivot || y > myLevel.levelScreenHeight - 1)
	{
		return true;
	}
	if (level[y][x] == ' ' || level[y][x] == '>' || level[y][x] == '|' || level[y][x] == '_')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Draw(vector<vector<char>> level, int levelPivot, int levelWidth, int levelHeight, Player* myPlayer, Levels myLevel)
{
	cout << "Controls:" << endl;
	cout << "Move: A, D" << endl;
	cout << "Jump: W, Space" << endl;
	cout << "Change Direction: Left Arrow, Right Arrow" << endl;
	for (int y = 0; y < level.size(); y++)
	{
		for (int x = levelPivot; x < level[y].size() + levelPivot; x++)
		{
			SetColor(' ');
			if (x + 1 <= levelWidth + levelPivot && y + 1 <= levelHeight)
			{
				if (level[y][x] == '>' || level[y][x] == '<')
				{
					if (!myPlayer->inLevel)
					{
						myPlayer->SetXPosition(x);
						myPlayer->SetYPosition(y);
						myPlayer->SetInLevel(true, myPlayer);
					}
					
					if (myPlayer->positionX == x && myPlayer->positionY == y)
					{
						
						SetColor('>');
						SetColor('<');
						if (myPlayer->lastDirection == 1)
						{
							cout << '>';
						}
						else
						{
							cout << '<';
						}
						
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
						SetColor('>');
						SetColor('<');
						if (myPlayer->lastDirection == 1)
						{
							cout << '>';
						}
						else
						{
							cout << '<';
						}
					}
					else
					{
						SetColor(level[y][x]);
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

bool Game::CanUpdate()
{
	return myPlayer.inLevel && myPlayer.jumping == false && myPlayer.falling == false;
}

void Game::MoveDown(int Level, int newXGeneral, int newYGeneral)
{
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
}
void Game::MoveLeft(int Level, int newX, int newY)
{
	if (!Collition(newX, newY, GetLevel(Level, myLevel)))
	{
		myPlayer.MoveTo(newX, newY);
		myLevel.levelNeedsReDraw = true;
	}
}
void Game::MoveRight(int Level, int newX, int newY)
{
	if (!Collition(newX, newY, GetLevel(Level, myLevel)))
	{
		myPlayer.MoveTo(newX, newY);
		myLevel.levelNeedsReDraw = true;
	}
}

void Game::HandleJumping(int Level, int newX, int newY)
{
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
}
void SetColor(char character)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (character == '>')
	{
		SetConsoleTextAttribute(console, 9); //Light blue
	}
	else if (character == '|')
	{
		SetConsoleTextAttribute(console, 8); //Gray
	}
	else if (character == '_')
	{
		SetConsoleTextAttribute(console, 42); //Light green
	}
	else if (character == '=')
	{
		SetConsoleTextAttribute(console, 42); //Light green
	}
	else
	{
		SetConsoleTextAttribute(console, 7); //White
	}
}