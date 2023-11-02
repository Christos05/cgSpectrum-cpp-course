#include <iostream>

using namespace std;

int main()
{
    int a;
    int b;

    cout << "Please give an Integer for this two Values:" << endl;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    int* ptrA = &a;
    int* ptrB = &b;

    cout << endl;
    cout << "a: " << ptrA << endl;
    cout << "b: " << ptrB << endl;
}
