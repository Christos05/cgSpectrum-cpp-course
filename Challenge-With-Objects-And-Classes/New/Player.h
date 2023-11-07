#pragma once
#include <iostream>
#include <string>

class Item;
using namespace std;

class Player
{
public:
	//Variables
	string m_name;
	int m_health;
	int m_damageAmountOfStoredItems;
	int m_healingAmountOfStoredItems;

	//Functions

	Player(string name, int health);
	~Player();

	void Damage(int amount);
	void Heal(int amount);
	void UseItems();
	void GiveItem(Item* item);
	void Display();
};