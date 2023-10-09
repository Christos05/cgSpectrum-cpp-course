#include <iostream>

using namespace std;

int main()
{
    int number1;
    int number2;
    int number3;

    cout << "Please whrite 3 Numbers: " << endl;

    cout << "Number 1: ";
    cin >> number1;

    cout << "Number 2: ";
    cin >> number2;

    cout << "Number 3: ";
    cin >> number3;

    float sum = number1 + number2 + number3;

    cout << "Here is the Sum and Average of these 3 Numbers: " << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << sum / 3.0f << endl;
}
