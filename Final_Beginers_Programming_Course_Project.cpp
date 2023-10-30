﻿#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;
constexpr char kPlayerSymbol = '@';
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
constexpr char GOL = 36;
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;

int getIndexFromCordinates(int x, int y, int width);
void drawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey);
void PlayDoorClosedSound();
void PlayDoorOpenSound();
void PlayKeyPickUpSound();
void PlayWinSound();
char* LoadLevel(string levelName, int& width, int& height);
bool ConvertLevel(char* level, int width, int height, int& playerX, int& playerY);

int main()
{
	int width = 25;
	int height = 15;

	char* levelArray = LoadLevel("level1.txt", width, height);

	int playerX = 1;
	int playerY = 1;
	bool anyWarnings = ConvertLevel(levelArray, width, height, playerX, playerY);
	if (anyWarnings)
	{
		cout << "There were some warnings in the level data, see above," << endl;
		system("pause");
	}

	bool playerHasKey = false;
	bool gameOver = false;

	while (!gameOver)
	{
		system("cls");
		drawLevel(levelArray, width, height, playerX, playerY, playerHasKey);
		gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, width, playerHasKey);
	}
	system("cls");
	drawLevel(levelArray, width, height, playerX, playerY, playerHasKey);
	cout << "You Won!" << endl;
	PlayWinSound();

	delete[] levelArray;
}

char* LoadLevel(string levelName, int& width, int& height)
{
	levelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile)
	{
		cout << "Opening file Failed!" << endl;
		return nullptr;
	}
	else
	{
		constexpr int tempSize = 25;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		width = atoi(temp);

		levelFile.getline(temp, tempSize, '\n');
		height = atoi(temp);

		char* levelData = new char[width * height];
		levelFile.read(levelData, width * height);
		return levelData;

	}
}
bool ConvertLevel(char* level, int width, int height, int& playerX, int& playerY)
{
	bool anyWarnings = false;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = getIndexFromCordinates(x, y, width);

			switch (level[index])
			{
			case '+':
			case '-':
			case '|':
				level[index] = WAL;
				break;
			case '*':
				level[index] = KEY;
				break;
			case 'D':
				level[index] = DOR;
				break;
			case 'X':
				level[index] = GOL;
				break;
			case '@':
				level[index] = ' ';
				playerX = x;
				playerY = y;
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << level[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}
	return anyWarnings;
}

int getIndexFromCordinates(int x, int y, int width)
{
	return x + y * width;
}

void drawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (playerX == x && playerY == y)
			{
				cout << kPlayerSymbol;
			}
			else
			{
				int indexToPrint = getIndexFromCordinates(x, y, width);
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				if (level[indexToPrint] == DOR)
				{
					if (playerHasKey)
					{
						SetConsoleTextAttribute(console, kOpenDoorColor);
					}
					else
					{
						SetConsoleTextAttribute(console, kClosedDoorColor);
					}
				}
				else
				{
					SetConsoleTextAttribute(console, kRegularColor);
				}
				cout << level[indexToPrint];
			}
		}
		cout << endl;
	}
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey)
{
	char input = _getch();
	
	int newPlayerX = playerX;
	int newPlayerY = playerY;

	switch (input)
	{
		case 'w':
		case 'W':
		{
			newPlayerY--;
			break;
		}
		case 's':
		case 'S':
		{
			newPlayerY++;
			break;
		}
		case 'a':
		case 'A':
		{
			newPlayerX--;
			break;
		}
		case 'd':
		case 'D':
		{
			newPlayerX++;
			break;
		}
		default:
		{
			break;
		}
	}

	int index = getIndexFromCordinates(newPlayerX, newPlayerY, width);
	if (level[index] == ' ')
	{
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == KEY)
	{
		playerHasKey = true;
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		PlayKeyPickUpSound();
	}
	else if (level[index] == DOR && playerHasKey == true)
	{
		playerHasKey = false;
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		PlayDoorOpenSound();
	}
	else if (level[index] == DOR && !playerHasKey == true)
	{
		PlayDoorClosedSound();
	}
	else if (level[index] == GOL)
	{
		playerX = newPlayerX;
		playerY = newPlayerY;
		return true;
	}
	return false;
}

void PlayDoorClosedSound()
{
	Beep(500, 75);
	Beep(500, 75);
}
void PlayDoorOpenSound()
{
	Beep(1379, 200);
}
void PlayKeyPickUpSound()
{
	Beep(1568, 200);
}
void PlayWinSound()
{
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1245, 1000);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1175, 1000);
}