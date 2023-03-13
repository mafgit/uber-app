#include <iostream>
#include <fstream>
#include <string>
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
	int day, month, year;
	string nic;

	bool is_err;
	if (opt1 == 1) {
		do {
			cout << endl << "Enter first name: ";
			cin >> firstName;

			cout << endl << "Enter last name: ";
			cin >> lastName;
			
			// todo: first name can have only one space

			is_err = firstName.length() < 2 || firstName.length() > 30 || lastName.length() < 2 || lastName.length() > 30;
		} while (is_err);

		// todo: think about reducing the code inside main and increasing the code inside classes (for later)
		// todo: think about making validation functions separately in another file (for later maybe)

		do {
			cout << endl << "Enter date of your date of birth: ";
			cin >> day; 
			cout << endl << "Enter month of your date of birth: ";
			cin >> month; 
			cout << endl << "Enter year of your date of birth: ";
			cin >> year;

			is_err = day < 1 || day > 31 || month < 1 || month > 12 || year > 2023 || year < 1920;

			if (is_err)
				cerr << endl << "Error: invalid date of birth" << endl;

			// todo: make 2023 and 1920 into a variable
			// todo: check if driver is of at least 18 years old
		} while (is_err);
		
		
		if (opt2 == 2) {
			bool flag1;
			bool flag2;
			do {
				flag1 = false;
				flag2 = false;
				cout << endl << "Enter phone number (start with 0): ";
				cin >> phoneNum;

				if (phoneNum[0] != '0' || phoneNum[1] != '3')
					flag1 = true;
				else {
					for (int i = 0; i < phoneNum.length(); i++) {
						if (!isdigit(phoneNum[i])) {
							flag2 = true;
							break;
						}
					}
				}

				is_err = phoneNum.length() != 11 || flag1 == true || flag2 == true;
				if (is_err)
					cerr << endl << "Error: invalid phone number" << endl;
			} while (is_err);

			do {
				flag1 = false;
				flag2 = false;
				cout << endl << "Enter NIC number (without dashes): ";
				cin >> nic;

				if (nic[0] != '4')
					flag1 = true;
				else {
					for (int i = 0; i < nic.length(); i++) {
						if (!isdigit(nic[i])) {
							flag2 = true;
							break;
						}
					}
				}

				is_err = nic.length() != 13 || flag1 || flag2;

				if (is_err)
					cerr << endl << "Error: invalid NIC" << endl;
			} while (is_err);
		}

		cin.ignore();

		do {
			cout << endl << "Enter password: ";
			getline(cin, password);

			cout << endl << "Confirm password: ";
			getline(cin, confirmPassword);

			if (password.length() < 6)
				cerr << endl << "Error: password must be at least six characters long" << endl;

			if (password != confirmPassword)
				cerr << endl << "Error: passwords do not match" << endl;

		} while (password.length() < 6 || password != confirmPassword);

		// todo: ask for vehicle details if driver
		// todo: check if phone no. exists already in file; in that case show that it exists already so try logging instead
		// todo: otherwise append the details to end of the drivers or passengers file
	}
	else { // opt1 = 2 (login)
		// todo: ask for login info
		// it is already stored in opt2 whether the user wants to be logged in as driver or passenger
	}
}
