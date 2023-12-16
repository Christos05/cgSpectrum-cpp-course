#include "Game.h"
#include "Player.h"
#include "Levels.h"
#include "Enemy.h"
#include "Merchant.h"
#include "AudioManager.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

constexpr int arrowRight = 100;
constexpr int arrowLeft = 97;
constexpr int arrowUp = 119;
constexpr int Space = 32;
constexpr int LeftArrowKey = 75;
constexpr int RightArrowKey = 77;
constexpr int InteractKey = 101; //E
constexpr int ExitBattleKey = 120; //X
constexpr int Key1 = 49;
constexpr int Key2 = 50;
constexpr int Key3 = 51;

vector<vector<char>> GetLevel(int level, Levels myLevel);
void SetColor(char character);

Game::Game()
	: finishedLevel(false)
	, finishedGame(false)
{

}
Game::~Game()
{
	while (!Characters.empty())
	{
		delete Characters.back();
		Characters.pop_back();
	}
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
		HandleDrawing(Level);
	}
	Update(Level);
}

void Game::Update(int Level)
{
	if (CanUpdateGame())
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
			myAudio.PlayJumpSound();
			myPlayer.Jump(3);
			myLevel.levelNeedsReDraw = true;
		}
		else if (input == RightArrowKey)
		{
			if (myPlayer.lastDirection == -1)
			{
				myAudio.PlaySwichSideSound();
				myPlayer.lastDirection = 1;
				myLevel.levelNeedsReDraw = true;
			}
		}
		else if (input == LeftArrowKey)
		{
			if (myPlayer.lastDirection == 1)
			{
				myAudio.PlaySwichSideSound();
				myPlayer.lastDirection = -1;
				myLevel.levelNeedsReDraw = true;
			}
		}
		else if (input == InteractKey)
		{
			if (AnyCharactersClose())
			{
				switch(ClosestCharacter()->GetType())
				{
				case CharacterType::enemy:
					myAudio.PlayEnteringBattle();
					ScreenType = ScreenOutput::Battle;
					BattlingEnemy = ClosestCharacter();
					BattlingEnemy->health = BattlingEnemy->maxHealth;
					myPlayer.health = myPlayer.maxHealth;
					Cicle = 1;
					myPlayer.TimesCanHeal = myPlayer.MaxTimesCanHeal;
					break;
				case CharacterType::merchant:
					ScreenType = ScreenOutput::Shop;
					break;
				default:
					break;
				}
				myLevel.levelNeedsReDraw = true;
			}
		}
	}
	else if (CanUpdateBattle())
	{
		int input = _getch();
		if (input == ExitBattleKey)
		{
			myAudio.PlayExitingBattle();
			ScreenType = ScreenOutput::Game;
			myLevel.levelNeedsReDraw = true;
		}
		else if (input == Key1)
		{
			myAudio.PlayAttack();
			BattlingEnemy->Damage(myPlayer.damage);
			Cicle += 2;
			EnemysTurn();
			myLevel.levelNeedsReDraw = true;
		}
		else if (input == Key2)
		{
			myAudio.PlayGuard();
			Cicle += 2;
			EnemysTurn();
			myLevel.levelNeedsReDraw = true;
		}
		else if (input == Key3 && myPlayer.TimesCanHeal != 0)
		{
			myAudio.PlayHeal();
			myPlayer.TimesCanHeal -= 1;
			myPlayer.Heal(myPlayer.HealAmount);
			Cicle += 2;
			EnemysTurn();
			myLevel.levelNeedsReDraw = true;
		}
	}

	if (ScreenType == ScreenOutput::Battle)
	{
		if (myPlayer.health == 0 || BattlingEnemy->health == 0)
		{
			myPlayer.health = myPlayer.maxHealth;
			ScreenType = ScreenOutput::Game;
			if (BattlingEnemy->health == 0)
			{
				BattlingEnemy->dead = true;
				myPlayer.Coins += BattlingEnemy->maxHealth / 2;
				myAudio.PlayWinBattle();
			}
			else
			{
				myAudio.PlayLooseBattle();
			}
			myLevel.levelNeedsReDraw = true;
		}
	}

}

bool Game::Collition(int x, int y, vector<vector<char>> level)
{
	if (x < 0 + myLevel.levelPivot || y < 0 || x > myLevel.levelScreenWidth -1 + myLevel.levelPivot || y > myLevel.levelScreenHeight - 1)
	{
		return true;
	}
	if (level[y][x] == ' ' || level[y][x] == '>' || level[y][x] == '|' || level[y][x] == '_' || level[y][x] == '*' || level[y][x] == '%')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Game::HandleDrawing(int level)
{
	//Output Controlls
	cout << "Controls:" << endl;
	cout << "Move: A, D" << endl;
	cout << "Jump: W, Space" << endl;
	cout << "Change Direction: Left Arrow, Right Arrow" << endl;

	//Drawing the current stage of the Game
	if (ScreenType == ScreenOutput::Game)
	{
		DrawGame(GetLevel(level, myLevel));
	}
	else if (ScreenType == ScreenOutput::Battle)
	{
		DrawBattle();
	}
	else if (ScreenType == ScreenOutput::Shop)
	{
		DrawShop();
	}
	
	//Outputing player actions-stats
	for (int i = 1; i <= myLevel.levelScreenWidth; i++)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, 8);
		cout << '-';
	}
	cout << endl;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 7);
	if (ScreenType == ScreenOutput::Game)
	{
		cout << "~Coins: " << myPlayer.Coins << endl;
	}
	cout << endl;

	//Outputting player interactions
	if (AnyCharactersClose() && ScreenType == ScreenOutput::Game)
	{
		if (ClosestCharacter()->dead == false)
		{
			switch (ClosestCharacter()->GetType())
			{
			case CharacterType::enemy:
				cout << "[E] ~Battle with the Enemy" << endl;
				break;
			case CharacterType::merchant:
				cout << "[E] ~Merchant's Shop" << endl;
				break;
			default:
				break;
			}
		}
	}
	else if (ScreenType == ScreenOutput::Battle)
	{
			if (Cicle % 2 != 0)
			{
				cout << "-Its your turn! What shall you do?" << endl;
				cout << " [1] ~Attack: " << myPlayer.damage << " Damage, if Crit " << myPlayer.damage+(myPlayer.damage * myPlayer.CritDamage)/100 << " Damage" << endl;
				cout << " [2] ~Guard: " << myPlayer.GuardDamage << " Damage Deflect" << endl;
				if (myPlayer.TimesCanHeal != 0)
				{
					cout << " [3] ~Heal(" << myPlayer.TimesCanHeal << "): " << myPlayer.HealAmount << " Health" << endl;
				}
				cout << endl;
				cout << "-Battle Info:" << endl;
				if (BattlingEnemy->NextMove == EnemyState::Attacking)
				{
					cout << " Enemy is getting ready for an Attck" << endl;
					cout << endl;
				}
				else if (BattlingEnemy->NextMove == EnemyState::HardHitting)
				{
					cout << " Enemy seems to be preparing a really Hard Hit!" << endl;
					cout << endl;
				}
				else if (BattlingEnemy->NextMove == EnemyState::Healing)
				{
					cout << " Enemy is backing up to Heal" << endl;
					cout << endl;
				}
			}

			SetConsoleTextAttribute(console, 9);
			cout << " -Player Stats-" << endl;
			SetConsoleTextAttribute(console, 7);
			cout << "  Health: " << myPlayer.health << "/" << myPlayer.maxHealth << endl;
			cout << endl;
			SetConsoleTextAttribute(console, 4);
			cout << " -Enemy Stats-" << endl;
			SetConsoleTextAttribute(console, 7);
			cout << "  Health: " << ClosestCharacter()->health << "/" << ClosestCharacter()->maxHealth << endl;
			cout << endl;
			cout << "[X] ~Exit" << endl;
		}
}

void Game::EnemysTurn()
{
	if (BattlingEnemy->NextMove == EnemyState::Attacking)
	{
		myPlayer.Damage(BattlingEnemy->damage);
	}
}

void Game::DrawGame(vector<vector<char>> level)
{
	for (int y = 0; y < level.size(); y++)
	{
		for (int x = myLevel.levelPivot; x < level[y].size() + myLevel.levelPivot; x++)
		{
			SetColor(' ');
			if (x + 1 <= myLevel.levelScreenWidth + myLevel.levelPivot && y + 1 <= myLevel.levelScreenHeight)
			{
				if (level[y][x] == '>' || level[y][x] == '<')
				{
					if (!myPlayer.inLevel)
					{
						myPlayer.SetXPosition(x);
						myPlayer.SetYPosition(y);
						myPlayer.SetInLevel(true, &myPlayer);
					}

					if (myPlayer.positionX == x && myPlayer.positionY == y)
					{

						SetColor('>');
						SetColor('<');
						if (myPlayer.lastDirection == 1)
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
					if (myPlayer.positionX == x && myPlayer.positionY == y && myPlayer.inLevel)
					{
						SetColor('>');
						SetColor('<');
						if (myPlayer.lastDirection == 1)
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
						if (level[y][x] == '*')
						{
							for (int i = 0; i < Characters.size(); i++)
							{
								if (Characters[i]->positionY == y && Characters[i]->positionX == x)
								{
									if (Characters[i]->dead == true)
									{
										SetColor(' ');
										cout << ' ';
									}
									else
									{
										SetColor(level[y][x]);
										cout << level[y][x];
									}
									break;
								}
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
		}
		cout << endl;
	}
}

void Game::DrawBattle()
{
	for (int y = 0; y < myLevel.BattleScenery.size(); y++)
	{
		for (int x = 0; x < myLevel.BattleScenery[y].size(); x++)
		{
			SetColor(myLevel.BattleScenery[y][x]);
			cout << myLevel.BattleScenery[y][x];
		}
		cout << endl;
	}
}

void Game::DrawShop()
{
	cout << "----------" << endl;
	cout << "Coming Soon!" << endl;
}

vector<vector<char>> GetLevel(int level, Levels myLevel)
{
	if (level == 1)
	{
		return myLevel.Level1;
	}
	return myLevel.Level1;
}

bool Game::CanUpdateGame()
{
	return myPlayer.inLevel && myPlayer.jumping == false && myPlayer.falling == false && ScreenType == ScreenOutput::Game;
}
bool Game::CanUpdateBattle()
{
	return ScreenType == ScreenOutput::Battle;
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
			myAudio.PlayLandingSound();
			myPlayer.falling = true;
			myLevel.levelNeedsReDraw = true;
		}
		myPlayer.jumping = false;
	}
}
void SetColor(char character)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (character == '>' || character == '<')
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
	else if (character == '*')
	{
		SetConsoleTextAttribute(console, 4); //Red
	}
	else if (character == '%')
	{
		SetConsoleTextAttribute(console, 1); //Blue
	}
	else
	{
		SetConsoleTextAttribute(console, 7); //White
	}
}

void Game::LoadLevel(int Level)
{
	
	for (int y = 0; y < GetLevel(Level, myLevel).size(); y++)
	{
		for (int x = 0; x < GetLevel(Level, myLevel)[y].size(); x++)
		{
			if (GetLevel(Level, myLevel)[y][x] == '*')
			{
				Characters.push_back(new Enemy(y, x));
			}
			else if (GetLevel(Level, myLevel)[y][x] == '%')
			{
				Characters.push_back(new Merchant(y, x));
			}
		}
	}

	
}

bool Game::AnyCharactersClose()
{
	for (int i = 0; i < Characters.size(); i++)
	{
		if (abs(myPlayer.positionX - Characters[i]->positionX) <= 1 && abs(myPlayer.positionY - Characters[i]->positionY) <= 1)
		{
			return true;
		}
	}
	return false;
}

Character* Game::ClosestCharacter()
{
	for (int i = 0; i < Characters.size(); i++)
	{
		if (abs(myPlayer.positionX - Characters[i]->positionX) <= 1 && abs(myPlayer.positionY - Characters[i]->positionY) <= 1)
		{
			return Characters[i];
		}
	}
	return Characters[0];
}