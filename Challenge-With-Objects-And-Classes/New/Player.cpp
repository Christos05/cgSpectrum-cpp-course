#include <iostream>
#include "Player.h"
#include "Item.h"
#include <string>

using namespace std;

Player::Player(string name, int health)
	: m_damageAmountOfStoredItems(0)
	, m_healingAmountOfStoredItems(0)
{
	m_name = name;
	m_health = health;
}

Player::~Player()
{

}

void Player::Damage(int amount)
{
	m_health -= amount;
}
void Player::Heal(int amount)
{
	m_health += amount;
}
void Player::UseItems()
{
	int remainingDamage = 0;
	if (m_damageAmountOfStoredItems > 0)
	{
		if (m_health - m_damageAmountOfStoredItems >= 0)
		{
			m_health -= m_damageAmountOfStoredItems;
		}
		else
		{
			remainingDamage = m_damageAmountOfStoredItems - m_health;
			m_health = 0;
		}
	}

	if (m_healingAmountOfStoredItems > 0)
	{
		if (remainingDamage > m_healingAmountOfStoredItems)
		{
			m_health = 0;
		}
		else
		{
			m_health += m_healingAmountOfStoredItems - remainingDamage;
		}
	}
}
void Player::GiveItem(Item* item)
{
	m_damageAmountOfStoredItems += item->m_damage;
	m_healingAmountOfStoredItems += item->m_healing;
	
}
void Player::Display()
{
	cout << "~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Name: " << m_name << endl;
	cout << "Health: " << m_health << endl;
}
