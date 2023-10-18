#include <iostream>

using namespace std;

int main()
{
	int number;

	do
	{
		cout << "Please whrite a Possitive Integer: " << endl;
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
			cout << "Invalid number, try again." << endl;
		}
		else
		{
			if (number <= 0)
			{
				cout << "Invalid number, try again." << endl;
			}
			else
			{
				break;
			}
		}
	} while (true);

	system("cls");

	for (int i = 1; i <= number; i++)
	{
		if (number % i == 0)
		{
			if (i + 1 > number)
			{
				cout << i << " are the Factor Values of " << number << endl;
			}
			else
			{
				cout << i << ", ";
			}
		}
	}
}

