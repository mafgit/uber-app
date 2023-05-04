#include "Classes.h"
#include "Functions.h"
#include "Questions.h"
#include <string>

int main()
{
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
	int age;

	bool is_err;
	if (opt1 == 1)
	{
		askName(firstName, true, false);
		askName(lastName, false, false);
		do
		{
			askDate(1, day, 1, 31, false);
			askDate(2, month, 1, 12, false);
			askDate(3, year, current_year - 120, current_year, false);

			age = getAge(day, month, year);
			if (opt2 == 2)
			{
				if (age < 18)
					cerr << endl
						 << "Error: driver must be at least 18 years old" << endl;
			}
		} while (opt2 == 2 && age < 18);

		// askDOB(day, month, year, opt2 == 1, false);
		askPhoneNum(phoneNum, opt2 == 1, false);

		if (opt2 == 2)
			askNIC(false, nic);

		askPassword(password, "-", false);

		if (opt2 == 2)
		{ // driver
			string type, make, model, trimLevel, plateNum, color;
			int yearOfManufacture;

			askVehicle(false, type, yearOfManufacture, make, model, trimLevel, plateNum, color);

			Vehicle vehicle(type, yearOfManufacture, make, model, trimLevel, plateNum, color);

			int newId = getLastId("drivers.csv") + 1;
			Driver driver(newId, day, month, year, firstName, lastName, phoneNum, password, nic, vehicle);
			driver.appendToFile();
		}
		else
		{ // passenger
			int newId = getLastId("passengers.csv") + 1;
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
			ifstream passengers_in("passengers.csv");
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
				if (opt == 2)
					passenger.viewHistory(true);
				else if (opt == 3)
					passenger.viewProfile();
				else if (opt == 4)
					passenger.updateProfile(true);

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
			ifstream drivers_in("drivers.csv");
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
					// LATER: try to move this code into Classes.h

					int acceptedId = -1;
					bool found = false;
					Booking booking;

					// BUG:
					while (1)
					{
						driver.viewAvailableRides(acceptedId, booking, found);
						if (acceptedId == -2)
							break;
						if (found)
						{
							updateBooking(booking, "accepted", driver.getId(), "-", "-");
							break;
						}
					}

					if (found)
					{
						int startRide;

						do
						{
							cout << "Enter 1 to start ride: ";
							cin >> startRide;
						} while (startRide != 1);

						string startedAt = getCurrentTime();
						updateBooking(booking, "started", driver.getId(), startedAt, booking.getCompletedAt());

						cout << "Ride started" << endl;

						for (int i = 0; i < booking.getAvgDistance(); i++)
						{
							cout << endl
								 << "Wait... " << i;
							Sleep(1000);
						}
						cout << endl;

						string completedAt = getCurrentTime();
						updateBooking(booking, "completed", driver.getId(), startedAt, completedAt);
						cout << "Ride completed" << endl;
					}
				}
				if (opt == 2)
					driver.viewHistory(false);
				else if (opt == 3)
					driver.viewProfile();
				else if (opt == 4)
					driver.updateProfile(false);

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