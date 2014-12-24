#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc , char *argv[])
{
    //cout << "Please enter a number:" << endl;
    int number;
    //cin >> number;
    number = atoi(argv[1]);
    if (number > 5)
    {
        cout << "Large number" << endl;
    }
    else
    {
        cout << "Small number" << endl;
    }
    return 0;
}
