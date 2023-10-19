#include <iostream>

using namespace std;

int main()
{
    int myArray[10] = {2, 8, 12, 5, 82, 14, 10, 5, 293, 103};
    int largestNumber = 0;

    for (int i = 0; i <= 10; i++)
    {
        if (myArray[i] > largestNumber)
        {
            largestNumber = myArray[i];
        }
    }

    cout << "The largest number in the array is " << largestNumber << endl;
}

