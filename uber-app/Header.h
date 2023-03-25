#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// TODO: admin class

class User
{
protected:
    int id, day, month, year;
    string firstName, lastName, phoneNum, password;

public:
    User()
    {
        id = -1;
        day = 0;
        month = 0;
        year = 0;
        firstName = "";
        lastName = "";
        phoneNum = "";
        password = "";
    }

    User(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password) : id(id), day(day), month(month), year(year), firstName(firstName), lastName(lastName), phoneNum(phoneNum), password(password) {}

    string getPhoneNum()
    {
        return phoneNum;
    }

    string getPassword()
    {
        return password;
    }

    void viewProfile()
    {
        // TODO: view profile
    }

    static bool doesPhoneNumExist(string phoneNum, string fileName) {
        ifstream file_in("passengers.txt");
        istringstream ss;
        bool phoneNumExists = false;

        if (file_in)
        {
            string line;
            string skipString, phoneNumString;
            while (getline(file_in, line))
            {
                ss.clear();
                ss.str(line);

                for (int i = 0; i < 6; i++) {
                    getline(ss, skipString, ',');
                }

                getline(ss, phoneNumString, ',');

                if (phoneNumString == phoneNum) {
                    phoneNumExists = true;
                    break;
                }
            }
        }

        file_in.close();
        return phoneNumExists;
    }
};

class Passenger : public User
{
public:
    Passenger() {}

    Passenger(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password)
        : User(id, day, month, year, firstName, lastName, phoneNum, password) {}

    void appendToFile()
    {
        ofstream file("passengers.txt", ios::app);
        file << id << "," << day << "," << month << "," << year << "," << firstName << "," << lastName << "," << phoneNum << "," << password << "\n";
        file.close();
    }

    int displayMenu()
    {
        // could've been done using inheritance but didn't do that coz it would be difficult if we need to add more options in either passenger or driver
        int opt = 0;

        do
        {
            cout << endl
                 << "1) Book a ride" << endl;
            cout << "2) View history" << endl;
            cout << "3) View profile" << endl;
            cout << "4) Update profile" << endl;
            cout << "5) Logout" << endl;
            // TODO: 6) Delete account
            cin >> opt;
        } while (opt > 5 || opt < 1);

        return opt;
    }
};

class Vehicle
{
    int model, noOfSeats;
    string name, plateNum, color, type;
    // types: bike, ride_ac, ride, ride_mini, auto
public:
    Vehicle()
    {
        model = 0;
        noOfSeats = 0;
        name = "";
        plateNum = "";
        color = "";
        type = "";
    }

    Vehicle(int model, int noOfSeats, string name, string plateNum, string color, string type)
    {
        this->model = model;
        this->noOfSeats = noOfSeats;
        this->name = name;
        this->plateNum = plateNum;
        this->color = color;
        this->type = type;
    }

    // getters
    int getModel() { return model; }
    int getNoOfSeats() { return noOfSeats; }
    string getName() { return name; }
    string getPlateNum() { return plateNum; }
    string getColor() { return color; }
    string getType() { return type; }
};

class Driver : public User
{
    int sumOfRatings, userCountOfRating;
    Vehicle vehicle;
    string nic;

public:
    Driver()
    {
        sumOfRatings = 0;
        userCountOfRating = 0;
        nic = "";
    }

    Driver(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password, Vehicle vehicle, string nic)
        : User(id, day, month, year, firstName, lastName, phoneNum, password), sumOfRatings(0), userCountOfRating(0), vehicle(vehicle), nic(nic) {}

    void appendToFile()
    {
        ofstream file("drivers.txt", ios::app);
        file << id << "," << day << "," << month << "," << year << "," << firstName << "," << lastName << "," << phoneNum << "," << password << ","
             << vehicle.getModel() << "," << vehicle.getNoOfSeats() << "," << vehicle.getName() << "," << vehicle.getPlateNum() << "," << vehicle.getColor() << "," << vehicle.getType() << "\n";
        file.close();
    }

    int displayMenu()
    {
        int opt = 0;

        do
        {
            cout << endl
                 << "1) View users currently searching for ride" << endl;
            cout << "2) View history" << endl;
            cout << "3) View profile" << endl;
            cout << "4) Update profile" << endl;
            cout << "5) Logout" << endl;
            // TODO: 6) Delete account
            cin >> opt;
        } while (opt > 5 || opt < 1);

        return opt;
    }
};

class Booking
{
    char pickupLocation, dropoffLocation;
    int fare; // TODO: check if fare should be taken in float
    Passenger passenger;
    Driver driver;
    // TODO: bookedAt (time of booking)
    // TODO: completedAt
    string status; // arriving, arrived, in_progress, completed, cancelled
};

int menu1()
{
    int opt;

    do
    {
        cout << endl
             << "Enter a number for one of the following commands:" << endl;
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

    do
    {
        cout << endl
             << "1) As passenger" << endl;
        cout << "2) As driver" << endl;
        cout << "3) Go Back" << endl;
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    return opt;
}

string typesMenu()
{
    int opt = 0;

    cout << endl
         << "Enter a number for the type of your vehicle: " << endl;
    do
    {
        cout << endl
             << "1) Bike" << endl;
        cout << "2) Ride AC" << endl;
        cout << "3) Ride" << endl;
        cout << "4) Ride Mini" << endl;
        cout << "5) Auto" << endl;
        cin >> opt;
    } while (opt < 1 || opt > 5);

    if (opt == 1)
        return "Bike";
    else if (opt == 2)
        return "Ride AC";
    else if (opt == 3)
        return "Ride";
    else if (opt == 4)
        return "Ride Mini";
    else
        return "Auto";
}