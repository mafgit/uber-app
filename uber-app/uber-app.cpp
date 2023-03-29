#include "Classes.h"
#include "Validations.h"
#include "Menus.h"
#include <string>

int main()
{
	// TODO: any string input must not have a comma
	cout << endl
		 << "Welcome to Uber Application!" << endl;
	int opt1, opt2;

	time_t now = time(0);
	tm *timePtr = localtime(&now);
	// const int current_date = timePtr->tm_mday;
	const int current_month = 1 + timePtr->tm_mon;
	const int current_year = 1900 + timePtr->tm_year;

start:
	opt1 = menu1();
	if (opt1 == 3)
		return 0;

	opt2 = menu2();
	if (opt2 == 3)
		goto start;

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

			is_err = !isValidName(firstName) || !isValidName(lastName);

			if (is_err)
				cerr << endl
					 << "Error: both names must contain at least 1 and at most 30 characters" << endl;
		} while (is_err);

		int age;
		do
		{
			cout << endl
				 << "Enter date of your birth [1 to 31]: ";
			// TODO: check for no of days being correct for a particular month can be implemented
			cin >> day;
			cout << endl
				 << "Enter month of your birth [1 to 12]: ";
			cin >> month;
			cout << endl
				 << "Enter year of your birth: ";
			cin >> year;

			is_err = day < 1 || day > 31 || month < 1 || month > 12 || year > current_year || year < current_year - 120;

			if (is_err)
				cerr << endl
					 << "Error: invalid date of birth" << endl;

			if (!is_err && opt2 == 2)
			{
				int years_diff = current_year - year;
				int months_diff = current_month - month;
				// int days_diff = current_date - day;

				age = years_diff + (months_diff < 0 ? -1 : 0);
				if (age < 18)
					cerr << endl
						 << "Error: driver must be at least 18 years old" << endl;
			}
		} while (is_err || (age < 18 && opt2 == 2));

		bool phoneNumExists = false;
		do
		{
			cout << endl
				 << "Enter phone number (start with 0): ";
			cin >> phoneNum;

			is_err = !isPhoneNumValid(phoneNum);

			if (is_err)
				cerr << endl
					 << "Error: invalid phone number" << endl;
			else
			{
				if (opt2 == 1)
					phoneNumExists = doesPhoneNumOrNicExist(phoneNum, true, "passengers.txt");

				else if (opt2 == 2)
					phoneNumExists = doesPhoneNumOrNicExist(phoneNum, true, "drivers.txt");
			}

			if (phoneNumExists)
				cerr << endl
					 << "Error: this phone number is already in use" << endl;

		} while (is_err || phoneNumExists);

		if (opt2 == 2)
		{
			bool nicExists;

			do
			{
				cout << endl
					 << "Enter NIC number (without dashes): ";
				cin >> nic;

				is_err = !isValidNIC(nic);

				if (is_err)
					cerr << endl
						 << "Error: invalid NIC" << endl;

				nicExists = doesPhoneNumOrNicExist(nic, false, "drivers.txt");
				if (nicExists)
					cerr << endl
						 << "Error: this NIC is already in use" << endl;
			} while (is_err || nicExists);
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

		} while (password.length() < 6 || password != confirmPassword || containsComma(password));

		if (opt2 == 2)
		{ // driver

			string type, make, model, trimLevel, plateNum, color;
			int yearOfManufacture;

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
			// TODO: try to remove code duplication in login
			ifstream passengers_in("passengers.txt");
			string idStr, dayStr, monthStr, yearStr, firstNameStr, lastNameStr, phoneNumStr, passwordStr;
			string line;

			if (passengers_in)
			{
				istringstream ss;
				while (!found && getline(passengers_in, line))
				{
					/*
						found	getline	run while loop
						0		0		0
						0		1		1
						1		0		0
						1		1		0
					*/

					ss.clear();
					ss.str(line);

					getline(ss, idStr, ',');
					getline(ss, dayStr, ',');
					getline(ss, monthStr, ',');
					getline(ss, yearStr, ',');
					getline(ss, firstNameStr, ',');
					getline(ss, lastNameStr, ',');
					getline(ss, phoneNumStr, ',');
					getline(ss, passwordStr, ',');

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
				int opt = passenger.displayMenu();
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
				istringstream ss;
				while (!found && getline(drivers_in, line))
				{
					ss.clear();
					ss.str(line);

					getline(ss, idStr, ',');
					getline(ss, dayStr, ',');
					getline(ss, monthStr, ',');
					getline(ss, yearStr, ',');
					getline(ss, firstNameStr, ',');
					getline(ss, lastNameStr, ',');
					getline(ss, phoneNumStr, ',');
					getline(ss, passwordStr, ',');
					getline(ss, nicStr, ',');
					getline(ss, typeStr, ',');
					getline(ss, yearOfManufactureStr, ',');
					getline(ss, makeStr, ',');
					getline(ss, modelStr, ',');
					getline(ss, trimLevelStr, ',');
					getline(ss, plateNumStr, ',');
					getline(ss, colorStr, ',');

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
				int opt = driver.displayMenu();
			}
		}
	}

	system("pause");
}