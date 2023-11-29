#include <iostream>
#include "Money.h"

using namespace std;

Money::Money(int x, int y, int worth)
	: PlacableActor(x, y)
	, m_worth(worth)
{

}

void Money::Draw()
{
	cout << '$';
}