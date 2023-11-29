#include <iostream>
#include <windows.h>
#include "Door.h"

using namespace std;

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, color)
	, m_isOpen(false)
	, m_closedDoor(closedColor)
{

}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, (int)m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_closedDoor);
	}
	cout << '|';
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}