#pragma once
#include <iostream>
#include <fstream>

using namespace std;

// todo: inheritance (User -> Driver, Passenger, and if there's time and energy, then Admin);

class User
{
protected:
    int id, day, month, year;
    string firstName, lastName, phoneNum, nic, password;

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
        nic = "";
        password = "";
    }

    User(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password) : id(id), day(day), month(month), year(year), firstName(firstName), lastName(lastName), phoneNum(phoneNum), password(password) {}

    string getPhoneNum()
    {
    	cout << phoneNum;
        return phoneNum;
    }

    string getPassword()
    {
    	cout << password;
        return password;
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
        ofstream passengers_cout("passengers.txt", ios::app);
        passengers_cout.write((char *)this, sizeof(*this));
        passengers_cout.close();
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
        // variable initialization
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
        // todo: vehicle initialization
    }

    Driver(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password, Vehicle vehicle, string nic)
        : User(id, day, month, year, firstName, lastName, phoneNum, password), sumOfRatings(0), userCountOfRating(0), vehicle(vehicle), nic(nic) {}

    void appendToFile()
    {
        ofstream drivers_cout("drivers.txt", ios::app);
        drivers_cout.write((char *)this, sizeof(*this));
        drivers_cout.close();
    }
};

class Booking
{
    char pickupLocation, dropoffLocation;
    int fare; // todo: check if fare should be taken in float
    Passenger passenger;
    Driver driver;
    // todo: bookedAt (time of booking)
    // todo: completedAt
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