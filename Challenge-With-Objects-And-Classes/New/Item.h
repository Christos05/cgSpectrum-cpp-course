#pragma once
#include <iostream>
#include <string>

class Player;
using namespace std;

class Item
{
public:
    //Variables
    string m_name;
    int m_damage;
    int m_healing;

    //Functions
    Item(string name, int damage, int healing);
    ~Item();

    void Use(Player* p);
};