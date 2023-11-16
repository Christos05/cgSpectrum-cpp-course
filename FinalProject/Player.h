#pragma once
#include "PlacableActor.h"
#include "Key.h"

using namespace std;

class Player : public PlacableActor
{
	Point m_position;
	bool m_hasKey;

public:
	Player();

	bool HasKey();
	bool HasKey(int color);
	void PickUpKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual void Draw() override;

private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
};
