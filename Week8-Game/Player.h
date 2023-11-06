#pragma once
#include "Point.h"

using namespace std;

class Player
{
	Point m_position;
	bool m_hasKey;

public:
	Player();
	~Player();

	int GetXPosition() { return m_position.x; }
	int GetYPosition() { return m_position.y; }

	int* GetXPositionPointer() { return &(m_position.x); }
	int* GetYPositionPointer() { return &(m_position.y); }


	void SetPosition(int x, int y);

	bool HasKey();
	void PickupKey();
	void UseKey();

	void Draw();
};
