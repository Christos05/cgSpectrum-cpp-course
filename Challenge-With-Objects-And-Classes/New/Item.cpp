#include <iostream>
#include <string>
#include "Item.h"
#include "Player.h"

using namespace std;

Item::Item(string name, int damage, int healing)
{
	m_name = name;
	m_damage = damage;
	m_healing = healing;

	
}

Item::~Item()
{

}

void Item::Use(Player* p)
{
	if (p->m_health - m_damage >= 0)
	{
		p->m_health -= m_damage;
	}
	else
	{
		p->m_health = 0;
	}
	p->m_health += m_healing;
}