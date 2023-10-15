#include <iostream>

using namespace std;

int main()
{
    int currentYear;

    cout << "Hey, please whrite the current year: " << endl;
    cin >> currentYear;

    if ((currentYear & 4) == 0)
    {
        cout << currentYear << " is a leap year!" << endl;
    }
    else 
    {
        cout << currentYear << " is not a leap year!" << endl;
    }
}
