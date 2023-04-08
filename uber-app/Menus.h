#pragma once
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
        cout << "3) Go back" << endl;
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    return opt;
}

string typesMenu()
{
    int opt = 0;

    do
    {
        cout << endl
             << "1) Uber Auto [Rickshaw] [3 passengers]" << endl;
        cout << "2) Uber Moto [Bike] [1 passenger]" << endl;
        cout << "3) UberX [A private ride at an everyday price] [4 passengers]" << endl;
        cout << "4) UberXL [Affordable rides for groups up to 6] [6 passengers]" << endl;
        cout << "5) Uber Black [Premium rides in luxury cars]" << endl;
        cin >> opt;
    } while (opt < 1 || opt > 5);

    if (opt == 1)
        return "Uber Auto";
    else if (opt == 2)
        return "Uber Moto";
    else if (opt == 3)
        return "UberX";
    else if (opt == 4)
        return "UberXL";
    else
        return "Uber Black";
}
