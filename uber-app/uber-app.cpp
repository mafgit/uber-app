#include "Classes.h"
#include "Functions.h"
#include "Questions.h"
#include <string>

int main()
{
	// LATER: any string input must not have a comma
	cout << endl
		 << "Welcome to Uber Application!" << endl;
	int opt1, opt2;

start:
	opt1 = menu1();
	if (opt1 == 3)
		return 0;

	opt2 = menu2();
	if (opt2 == 3)
		goto start;

	string firstName, lastName, phoneNum, password;
	int day, month, year;
	string nic;

	bool is_err;
	if (opt1 == 1)
	{
		askFirstAndLastNames(firstName, lastName);
		askDOB(day, month, year, opt2);
		askPhoneNum(phoneNum, opt2);

		if (opt2 == 2)
			askNIC(nic);

		askPassword(password, false);

		if (opt2 == 2)
		{ // driver
			string type, make, model, trimLevel, plateNum, color;
			int yearOfManufacture;

			cout << endl
				 << "Enter a number to select the type of your vehicle: " << endl;
			type = typesMenu();

			int minYearOfManufacture = current_year - 17;
			do
			{
				cout << endl
					 << "Enter year of manufacture of your vehicle [" << minYearOfManufacture << " - " << current_year << "]: ";
				cin >> yearOfManufacture;
			} while (yearOfManufacture < minYearOfManufacture || yearOfManufacture > current_year);

			do
			{
				cout << endl
					 << "Enter make (manufacturer) of the vehicle [e.g. Toyota]: ";
				cin >> make;
			} while (!isValidName(make));

			do
			{
				cout << endl
					 << "Enter model of the vehicle [e.g. Corolla]: ";
				cin >> model;
			} while (!isValidName(model));

			do
			{

				cout << endl
					 << "Enter trim level of the vehicle [e.g. LE]: ";
				cin >> trimLevel;
			} while (!isValidName(trimLevel));

			do
			{

				cout << endl
					 << "Enter plate number of the vehicle [e.g. AAA-1111]: ";
				cin >> plateNum;
			} while (!isValidPlateNum(plateNum));

			do
			{

				cout << endl
					 << "Enter color of the vehicle [e.g. blue]: ";
				cin >> color;
			} while (!isValidName(color));

			Vehicle vehicle(type, yearOfManufacture, make, model, trimLevel, plateNum, color);

			int newId = getLastId("drivers.txt") + 1;
			Driver driver(newId, day, month, year, firstName, lastName, phoneNum, password, nic, vehicle);
			driver.appendToFile();
		}
		else
		{ // passenger
			int newId = getLastId("passengers.txt") + 1;
			Passenger passenger(newId, day, month, year, firstName, lastName, phoneNum, password);
			passenger.appendToFile();
		}

		// signed up
		system("cls");
		cout << endl
			 << "Signed up!" << endl;
		goto start;
	}
	else
	{ // opt1 = 2 (login)
		// it is already stored in opt2 whether the user wants to be logged in as driver or passenger
		cout << endl
			 << "Enter phone number: " << endl;
		cin >> phoneNum;

		cout << endl
			 << "Enter password: " << endl;
		cin >> password;

		bool found = 0;
		if (opt2 == 1)
		{
			ifstream passengers_in("passengers.txt");
			string idStr, dayStr, monthStr, yearStr, firstNameStr, lastNameStr, phoneNumStr, passwordStr;
			string line;

			if (passengers_in)
			{
				while (!found && getline(passengers_in, line))
				{
					/*
						found	getline	run while loop
						0		0		0
						0		1		1
						1		0		0
						1		1		0
					*/

					string *fields[8] = {&idStr, &dayStr, &monthStr, &yearStr, &firstNameStr, &lastNameStr, &phoneNumStr, &passwordStr};
					getFields(line, fields, 8);

					if (phoneNum == phoneNumStr && password == passwordStr)
					{
						found = 1;
						break;
					}
				}
			}

			passengers_in.close();

			if (!found)
			{
				system("cls");
				cerr << endl
					 << "Error: invalid credentials" << endl;
				goto start;
			}
			else
			{
				// logged in as passenger
				system("cls");
				cout << endl
					 << "Logged in as passenger" << endl;
				Passenger passenger(stoi(idStr), stoi(dayStr), stoi(monthStr), stoi(yearStr), firstNameStr, lastNameStr, phoneNumStr, passwordStr);

			passengerMenu:
				int opt = passenger.displayMenu();

				if (opt == 1)
					passenger.bookARide();
				else if (opt == 3)
					passenger.viewProfile();

				if (opt != 5)
				{
					goto passengerMenu;
				}
				else
				{

					system("cls");
					cout << endl
						 << "Logged out!" << endl;
					goto start;
				}
			}
		}
		else if (opt2 == 2)
		{
			ifstream drivers_in("drivers.txt");
			string idStr, dayStr, monthStr, yearStr, firstNameStr, lastNameStr, phoneNumStr, passwordStr;
			string typeStr, yearOfManufactureStr, modelStr, makeStr, trimLevelStr, plateNumStr, colorStr;
			string nicStr;
			string line;

			if (drivers_in)
			{
				while (!found && getline(drivers_in, line))
				{
					string *fields[16] = {&idStr, &dayStr, &monthStr, &yearStr, &firstNameStr, &lastNameStr, &phoneNumStr, &passwordStr, &nicStr, &typeStr, &yearOfManufactureStr, &makeStr, &modelStr, &trimLevelStr, &plateNumStr, &colorStr};
					getFields(line, fields, 16);

					if (phoneNum == phoneNumStr && password == passwordStr)
					{
						found = 1;
						break;
					}
				}
			}

			drivers_in.close();

			if (!found)
			{
				system("cls");
				cerr << endl
					 << "Error: invalid credentials" << endl;
				goto start;
			}
			else
			{
				// logged in as driver
				system("cls");
				cout << endl
					 << "Logged in as driver" << endl;

				Vehicle vehicle(typeStr, stoi(yearOfManufactureStr), modelStr, makeStr, trimLevelStr, plateNumStr, colorStr);
				Driver driver(stoi(idStr), stoi(dayStr), stoi(monthStr), stoi(yearStr), firstNameStr, lastNameStr, phoneNumStr, passwordStr, nicStr, vehicle);

			driverMenu:
				int opt = driver.displayMenu();

				if (opt == 1)
				{
					// TODO: try to move this code into Classes.h

					int acceptedId = -1;
					bool found = false;

					while (acceptedId != -2 && found == false)
					{
						driver.viewAvailableRides(acceptedId, found);
						if (found)
						{
							// TODO: something like below
							// updateBooking(booking, acceptedId, "accepted", driver.getId(), "-");
						}
					}
				}
				else if (opt == 3)
					driver.viewProfile();

				if (opt != 5)
				{
					goto driverMenu;
				}
				else
				{
					system("cls");
					cout << endl
						 << "Logged out!" << endl;
					goto start;
				}
			}
		}
	}

	system("pause");
}