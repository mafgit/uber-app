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
		cout << endl << "1) As passenger" << endl;
		cout << "2) As driver" << endl;
		cout << "3) Go Back" << endl;
		cin >> opt;
	} while (opt != 1 && opt != 2 && opt != 3);
	// todo: handle the "back" option

	return opt;
}

int main()
{
	int opt1 = menu1();
	if (opt1 == 3) return 0; // exit

	int opt2 = menu2();
	// todo: handle the "back" option in menu 2

	int id, age;
	string firstName, lastName, phoneNum, password, confirmPassword;

	if (opt1 == 1) {
		cout << endl << "Enter first name: ";
		cin >> firstName;
		cout << endl << "Enter last name: ";
		cin >> lastName;
		// todo: validations
		// todo: think about reducing the code inside main and increasing the code inside classes (for later)
		// todo: think about making validation functions separately in another file (for later maybe)

		do {
			cout << endl << "Enter age: ";
			cin >> age;
			if (age < 18 && opt2 == 2)
				cout << endl << "Error: age of driver must be at least 18" << endl;
		} while (age < 18 && opt2 == 2);

		cout << endl << "Enter phone number: ";
		cin >> phoneNum;
		// todo: validation

		do {
			cout << endl << "Enter password: ";
			cin >> password;
			cout << endl << "Confirm password: ";
			cin >> confirmPassword;
			// todo: there is a problem when space is entered in string, so counter that problem in all string inputs

			if (password.length() < 6)
				cout << endl << "Error: password must be at least six characters long" << endl;

			if (password != confirmPassword)
				cout << endl << "Error: passwords do not match" << endl;

		} while (password.length() < 6 || password != confirmPassword);

		// todo: input more details if the user is a driver, such as vehicle details, etc
		// todo: check if phone no. exists already in file; in that case show that it exists already so try logging instead
		// todo: otherwise append the details to end of the drivers or passengers file
	}
	else { // opt1 = 2 (login)
		// todo: ask for login info
		// it is already stored in opt2 whether the user wants to be logged in as driver or passenger
	}
}
