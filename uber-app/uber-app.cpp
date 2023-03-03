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
		cout << endl << "1) Passenger" << endl;
		cout << "2) Driver" << endl;
		cin >> opt;
	} while (opt != 1 && opt != 2);

	return opt;
}

int main()
{
	int opt1 = menu1();
	int opt2 = menu2();
	// todo: add "back" option in menu 2

	int id, age;
	string firstName, lastName, phoneNum, password, confirmPassword;

	if (opt1 == 1 || opt1 == 2) {
		cout << endl << "Enter first name: ";
		cin >> firstName;
		cout << endl << "Enter last name: ";
		cin >> lastName;

		do {
			cout <<  endl << "Enter age: ";
			cin >> age;
			if(age < 18 && opt2 == 2)
				cout << endl << "Error: age of driver must be at least 18" << endl;
		} while (age < 18 && opt2 == 2);

		cout << endl << "Enter phone number: ";
		cin >> phoneNum;

		do {
			cout << endl << "Enter password: ";
			cin >> password;
			cout << endl << "Confirm password: ";
			cin >> confirmPassword;

			if (password.length() < 6)
				cout << endl << "Error: password must be at least six characters long" << endl;
			
			if (password != confirmPassword)
				cout << endl << "Error: passwords do not match" << endl;

		} while (password.length() < 6 || password != confirmPassword);
	}

	// todo: check if driver is signing up, and in that case, ask for vehicle details
	// todo: inheritance in header file
	// todo: filing
}		