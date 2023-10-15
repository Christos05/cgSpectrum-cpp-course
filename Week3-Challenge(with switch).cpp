#include <iostream>

using namespace std;

int main()
{
    constexpr int leapYear = 0;

    int currentYear;

    cout << "Hey, please whrite the current year: " << endl;
    cin >> currentYear;

    switch (currentYear % 4)
    {
        case leapYear:
        {
            cout << currentYear << " is a leap year!" << endl;
            break;
        }
        default:
        {
            cout << currentYear << " is not a leap year!" << endl;
            break;
        }
    }
}

