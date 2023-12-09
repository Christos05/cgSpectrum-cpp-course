#pragma once
#include <vector>
#include "Player.h"

using namespace std;

class Levels
{
public:

	int MaxLevelWidth;
	int MaxLevelHeight;
	int levelScreenWidth = 30;
	int levelScreenHeight = 10;
	int levelPivot;
	bool levelNeedsReDraw = true;

	vector<vector<char>> Level1{
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ',},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', ' ', ' ', ' ', ' ', ' ',},
		{' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ',},
		{'_', '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '_', ' ', ' ', ' ', '_', '_', '_', ' ', ' ', ' ', '|', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ',},
		{' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', '=', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ',},
		{' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '=', '=', '=', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', '_', ' ',},
		{'=', '|', '>', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '=', '=', '=', '=', '=', '=', '|', ' ', ' ', ' ', ' ', '=', '=', '=', ' ', ' ', ' ', ' ', ' ', '|', ' ', '=', ' ', ' ', '|', ' ',},
		{'=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=', '=',},
	};

	void HandlePivot(Player myPlayer);
	void SetMaxLevelWidth(int number) { MaxLevelWidth = number; }
	void SetMaxLevelHeight(int number) { MaxLevelHeight = number; }
	void UpdateMaxLevelSizes(vector<vector<char>> Level);

	Levels();
	~Levels();

};
