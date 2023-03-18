#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

int main()
{
	cout << endl
		<< "Welcome to Uber Application!" << endl;
	int opt1, opt2;

	do
	{
		opt1 = menu1();
		if (opt1 == 3)
			return 0; // exit
		opt2 = menu2();
	} while (opt2 == 3);

	string firstName, lastName, phoneNum, password, confirmPassword;
	int day, month, year;
	string nic;

	bool is_err;
	if (opt1 == 1)
	{
		do
		{
			cout << endl
				<< "Enter first name: ";
			cin >> firstName;

			cout << endl
				<< "Enter last name: ";
			cin >> lastName;

			// todo: validation of names regarding spaces

			is_err = firstName.length() < 2 || firstName.length() > 30 || lastName.length() < 2 || lastName.length() > 30;
		} while (is_err);

		// todo: think about reducing the code inside main and increasing the code inside classes (for later)
		// todo: think about making validation functions separately in another file (for later maybe)

		do
		{
			cout << endl
				<< "Enter date of your date of birth: ";
			cin >> day;
			cout << endl
				<< "Enter month of your date of birth: ";
			cin >> month;
			cout << endl
				<< "Enter year of your date of birth: ";
			cin >> year;

			is_err = day < 1 || day > 31 || month < 1 || month > 12 || year > 2023 || year < 1920;

			if (is_err)
				cerr << endl
				<< "Error: invalid date of birth" << endl;

			// todo: make 2023 and 1920 into a variable
			// todo: check if driver is of at least 18 years old
		} while (is_err);

		bool flag1;
		bool flag2;
		bool phoneNumExists;

		do
		{
			flag1 = false;
			flag2 = false;
			phoneNumExists = false;

			cout << endl
				<< "Enter phone number (start with 0): ";
			cin >> phoneNum;

			if (phoneNum[0] != '0' || phoneNum[1] != '3')
				flag1 = true;
			else
			{
				for (int i = 0; i < phoneNum.length(); i++)
				{
					if (!isdigit(phoneNum[i]))
					{
						flag2 = true;
						break;
					}
				}
			}

			is_err = phoneNum.length() != 11 || flag1 == true || flag2 == true;
			if (is_err)
				cerr << endl
				<< "Error: invalid phone number" << endl;
			else
			{
				if (opt2 == 1)
				{
					ifstream passengers_cin("passengers.txt");
					if (passengers_cin)
					{
						Passenger passenger;
						while (passengers_cin.eof() == 0)
						{
							passengers_cin.read((char*)&passenger, sizeof(passenger));
							if (passenger.getPhoneNum() == phoneNum)
							{
								cerr << endl
									<< "Error: passenger already exists with this phone number" << endl;
								phoneNumExists = true;
								break;
							}
						}
					}
					passengers_cin.close();
				}
				else if (opt2 == 2)
				{
					ifstream drivers_cin("drivers.txt");
					if (drivers_cin)
					{
						Driver driver;
						while (drivers_cin.eof() == 0)
						{
							drivers_cin.read((char*)&driver, sizeof(driver));
							if (driver.getPhoneNum() == phoneNum)
							{
								cerr << endl
									<< "Error: driver already exists with this phone number" << endl;
								phoneNumExists = true;
								break;
							}
						}
					}
					drivers_cin.close();
				}
			}
		} while (is_err || phoneNumExists);

		if (opt2 == 2)
		{
			do
			{
				flag1 = false;
				flag2 = false;
				cout << endl
					<< "Enter NIC number (without dashes): ";
				cin >> nic;

				if (nic[0] != '4')
					flag1 = true;
				else
				{
					for (int i = 0; i < nic.length(); i++)
					{
						if (!isdigit(nic[i]))
						{
							flag2 = true;
							break;
						}
					}
				}

				is_err = nic.length() != 13 || flag1 || flag2;

				if (is_err)
					cerr << endl
					<< "Error: invalid NIC" << endl;
			} while (is_err);
		}

		do
		{
			cout << endl
				<< "Enter password: ";
			cin >> password;

			cout << endl
				<< "Confirm password: ";
			cin >> confirmPassword;

			if (password.length() < 6)
				cerr << endl
				<< "Error: password must be at least six characters long" << endl;

			if (password != confirmPassword)
				cerr << endl
				<< "Error: passwords do not match" << endl;

		} while (password.length() < 6 || password != confirmPassword);

		if (opt2 == 2)
		{ // driver
			int model, noOfSeats;
			string plateNum, color, type, name;

			cout << endl << "Enter name of the vehicle: ";
			cin >> name;

			cout << endl << "Enter model of the vehicle: ";
			cin >> model;

			cout << endl << "Enter number of seats in the vehicle: ";
			cin >> noOfSeats;

			cout << endl << "Enter color of the vehicle: ";
			cin >> color;

			cout << endl << "Enter plate Number of the vehicle: ";
			cin >> plateNum;
			// todo: validation of name, model, noOfSeats, color, plateNum

			type = typesMenu();

			// todo: keep check of id and change 0 to id in next line
			Vehicle vehicle(model, noOfSeats, name, plateNum, color, type);
			Driver driver(0, day, month, year, firstName, lastName, phoneNum, password, vehicle, nic);
			driver.appendToFile();
		}
		else
		{ // passenger
			// todo: keep check of id and change 0 to id in next line
			Passenger passenger(0, day, month, year, firstName, lastName, phoneNum, password);
			passenger.appendToFile();
		}
	}
	else
	{ // opt1 = 2 (login)
		// todo: ask for login info
		// it is already stored in opt2 whether the user wants to be logged in as driver or passenger
		cout << endl
			<< "Enter phone number: " << endl;
		cin >> phoneNum;

		cout << endl << "Enter password: " << endl;
		cin >> password;

		if (opt2 == 1)
		{
			bool found = 0;
			ifstream passengers_cin("passengers.txt");

			Passenger passenger;
			while (!found && !passengers_cin.eof())
			{
				/*
					found	eof		run while loop
					0		0		1
					0		1		0
					1		0		0
					1		1		0
				*/
				passengers_cin.read((char*)&passenger, sizeof(passenger));
				//cout << endl << passenger.getPassword() << endl << passenger.getPhoneNum() << endl;
				if (password == passenger.getPassword() && phoneNum == passenger.getPhoneNum())
				{
					found = 1;
				}
			}

			passengers_cin.close();

			if (!found)
			{
				cerr << endl
					<< "Error: invalid credentials" << endl;
				// todo: show first menu again
			}
			else
			{
				// logged in as passenger
				cout << endl << "Logged in as passenger" << endl;
				return 0;
				// todo: correct error
			}
		}
		else if (opt2 == 2)
		{
			bool found = 0;
			ifstream drivers_cin("drivers.txt");

			Driver driver;
			while (!drivers_cin.eof() && !found)
			{
				drivers_cin.read((char*)&driver, sizeof(driver));
				if (password == driver.getPassword() && phoneNum == driver.getPhoneNum())
				{
					found = 1;
				}
			}

			drivers_cin.close();

			if (!found)
			{
				cerr << endl
					<< "Error: invalid credentials" << endl;
				// todo: show first menu again
			}
			else
			{
				// logged in as driver
				cout << endl << "Logged in as driver" << endl;
				return 0;
				// todo: correct error
			}
		}
	}
}