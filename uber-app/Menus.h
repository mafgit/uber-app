#include <iostream>
using namespace std;

int menu1()
{
    int opt;

    do
    {
        cout << endl
             << "Enter a number for one of the following commands:" << endl;
        cout << "1) Signup" << endl;
        cout << "2) Login" << endl;
        cout << "3) Exit" << endl;
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    return opt;
}

int menu2()
{
    int opt = 0;

    do
    {
        cout << endl
             << "1) As passenger" << endl;
        cout << "2) As driver" << endl;
        cout << "3) Go Back" << endl;
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    return opt;
}

string typesMenu()
{
    int opt = 0;

    cout << endl
         << "Enter a number for the type of your vehicle: " << endl;
    do
    {
        cout << endl
             << "1) Bike" << endl;
        cout << "2) Ride AC" << endl;
        cout << "3) Ride" << endl;
        cout << "4) Ride Mini" << endl;
        cout << "5) Auto" << endl;
        cin >> opt;
    } while (opt < 1 || opt > 5);

    if (opt == 1)
        return "Bike";
    else if (opt == 2)
        return "Ride AC";
    else if (opt == 3)
        return "Ride";
    else if (opt == 4)
        return "Ride Mini";
    else
        return "Auto";
}
