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

			is_err = !isValidName(firstName) || !isValidName(lastName);

			if (is_err)
				cerr << endl
					 << "Error: both names must contain at least 2 and at most 30 characters" << endl;
		} while (is_err);

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

			is_err = day < 1 || day > 31 || month < 1 || month > 12 || year > 2023 || year < 1920;

			if (is_err)
				cerr << endl
					 << "Error: invalid date of birth" << endl;

			// TODO: make 2023 and 1920 into a variable
			// TODO: check if driver is of at least 18 years old
		} while (is_err);

		bool phoneNumExists;

		do
		{
			phoneNumExists = false;

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
					phoneNumExists = doesPhoneNumExist(phoneNum, "passengers.txt");

				else if (opt2 == 2)
					phoneNum = doesPhoneNumExist(phoneNum, "drivers.txt");
			}

			if (phoneNumExists)
			{
				cerr << endl
					 << "Error: this phone number is already in use" << endl;
			}

		} while (is_err || phoneNumExists);

		if (opt2 == 2)
		{
			do
			{
				cout << endl
					 << "Enter NIC number (without dashes): ";
				cin >> nic;

				is_err = !isValidNIC(nic);

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

		} while (password.length() < 6 || password != confirmPassword || containsComma(password));

		if (opt2 == 2)
		{ // driver
			int model;
			string plateNum, color, type, name;

			do
			{
				cout << endl
					 << "Enter name of the vehicle: ";
				cin >> name;
			} while (!isValidName(name));

			do
			{

				cout << endl
					 << "Enter model of the vehicle [any year from 2006 to the current year]: ";
				cin >> model;
			} while (model < 2006 || model > 2023); // TODO: make 2023 into a variable & keep incrementing 2006

			do
			{

				cout << endl
					 << "Enter color of the vehicle: ";
				cin >> color;
			} while (!isValidName(color));

			do
			{

				cout << endl
					 << "Enter plate number of the vehicle: ";
				cin >> plateNum;
			} while (!isValidPlateNum(plateNum));

			type = typesMenu();

			// TODO: keep check of id and change 0 to id in next line
			Vehicle vehicle(type, model, name, plateNum, color);

			Driver driver(0, day, month, year, firstName, lastName, phoneNum, password, nic, vehicle);
			driver.appendToFile();
		}
		else
		{ // passenger
			// TODO: keep check of id and change 0 to id in next line
			Passenger passenger(0, day, month, year, firstName, lastName, phoneNum, password);
			passenger.appendToFile();
		}

		// signed up
		// TODO: show main menu again
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
				// show first menu again
				//	main();
				// TODO: think of a more efficient way of going back to start of main
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
			string typeStr, modelStr, nameStr, plateNumStr, colorStr;
			string nicStr;
			string line;

			if (drivers_in)
			{
				istringstream ss;
				while (!found && getline(drivers_in, line))
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
					getline(ss, nicStr, ',');
					getline(ss, typeStr, ',');
					getline(ss, modelStr, ',');
					getline(ss, nameStr, ',');
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
				// show first menu again
				// main();
				// TODO: think of a more efficient way of going back to start of main
			}
			else
			{
				// logged in as driver
				system("cls");
				cout << endl
					 << "Logged in as driver" << endl;

				Vehicle vehicle(typeStr, stoi(modelStr), nameStr, plateNumStr, colorStr);
				Driver driver(stoi(idStr), stoi(dayStr), stoi(monthStr), stoi(yearStr), firstNameStr, lastNameStr, phoneNumStr, passwordStr, nicStr, vehicle);
				int opt = driver.displayMenu();
			}
		}
	}

	system("pause");
}