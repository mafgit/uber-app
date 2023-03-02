#include <iostream>
#include "Header.h"
using namespace std;

int menu1()
{
	int opt;

	do {
		cout << "Enter a number for one of the following commands:" << endl;
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
	do {
		cout << "1) Passenger" << endl;
		cout << "2) Driver" << endl;
		cin >> opt;
	} while (opt != 1 && opt != 2);

	return opt;
}

int main()
{
	int opt1 = menu1();

	if (opt1 == 1) {
		// ask details for signup
	}
	else if (opt1 == 2) {
		// ask details for login
	}
	else
		return 0;
}