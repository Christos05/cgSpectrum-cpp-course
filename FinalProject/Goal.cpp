#include <iostream>
#include "Goal.h"

using namespace std;

Goal::Goal(int x, int y)
	: PlacableActor(x, y)
{

}

void Goal::Draw()
{
	cout << 'X';
}