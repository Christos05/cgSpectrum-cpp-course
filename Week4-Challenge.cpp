#include <iostream>

using namespace std;

int CubedNumber(int number);

int main()
{
	int number;
	cout << "Please whrite a number and I will return you that number Cubed: ";
	cin >> number;

	int cubedNumber = CubedNumber(number);
	cout << "your cubed number is " << cubedNumber;
}

int CubedNumber(int number)
{
	return number * number * number;
}