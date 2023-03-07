#include <iostream>
#include "Header.h"
using namespace std;

int menu1()
{
	int opt;

	do {
		cout << endl << "Enter a number for one of the following commands:" << endl;
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

	return opt;
}

int main()
{
	cout << endl << "Welcome to Uber Application!" << endl;
	int opt1, opt2;

	do {
		opt1 = menu1();
		if (opt1 == 3) return 0; // exit
		opt2 = menu2();
	} while (opt2 == 3);

	string firstName, lastName, phoneNum, password, confirmPassword;
	int age;
	string nic;

	if (opt1 == 1) {
		cout << endl << "Enter first name: ";
		cin >> firstName;
		cout << endl << "Enter last name: ";
		cin >> lastName;
		// todo: name validations

		// todo: think about reducing the code inside main and increasing the code inside classes (for later)
		// todo: think about making validation functions separately in another file (for later maybe)

		// todo: input DOB instead of age (we need DOB only for driver or for both?)
		// todo: take nic only for driver
		do {
			cout << endl << "Enter age: ";
			cin >> age;
			if (age < 18 && opt2 == 2)
				cout << endl << "Error: age of driver must be at least 18" << endl;
		} while (age < 18 && opt2 == 2);

		bool flag1;
		bool flag2;
		do {
			flag1 = false;
			flag2 = false;
			cout << endl << "Enter phone number (start with 0): ";
			cin >> phoneNum;

			if(phoneNum[0] != '0' || phoneNum[1] != '3')
				flag1 = true;
			else {
				for (int i = 0; i < phoneNum.length(); i++) {
					if (!isdigit(phoneNum[i])) {
						flag2 = true;
						break;
					}
				}
			}

		} while (phoneNum.length() != 11 || flag1 == true || flag2 == true);

		do{
			flag1 = false;
			flag2 = false;
			cout << endl << "Enter NIC number (without dashes): ";
			cin >> nic;

			if(nic[0] != '4')
				flag1 = true;
			else {
				for (int i = 0; i < nic.length(); i++) {
					if (!isdigit(nic[i])) {
						flag2 = true;
						break;
					}
				}
			}
		} while(nic.length() !=  13 || flag1 || flag2);

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

		// todo: input more details if the user is a driver, such as vehicle details, nic, etc
		// todo: check if phone no. exists already in file; in that case show that it exists already so try logging instead
		// todo: otherwise append the details to end of the drivers or passengers file
	}
	else { // opt1 = 2 (login)
		// todo: ask for login info
		// it is already stored in opt2 whether the user wants to be logged in as driver or passenger
	}
}
