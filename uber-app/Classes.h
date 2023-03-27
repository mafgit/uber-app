#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// TODO: admin class

class User
{
protected:
    int id = -1, day = 0, month = 0, year = 0;
    string firstName = "", lastName = "", phoneNum = "", password = "";

public:
    User() {}

    User(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password) : id(id), day(day), month(month), year(year), firstName(firstName), lastName(lastName), phoneNum(phoneNum), password(password) {}

    void viewProfile()
    {
        // TODO: view profile
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
    int model = 0, noOfSeats = 0;
    string name = "", plateNum = "", color = "", type = "";
    // TODO: name doesn't accept space so think about attributes such as brand, make, etc

public:
    Vehicle() {}

    Vehicle(string type, int model, string name, string plateNum, string color)
    {
        this->type = type;
        this->model = model;
        this->name = name;
        this->plateNum = plateNum;
        this->color = color;
    }

    // getters
    int getModel() { return model; }
    string getName() { return name; }
    string getPlateNum() { return plateNum; }
    string getColor() { return color; }
    string getType() { return type; }
};

class Driver : public User
{
    int sumOfRatings = 0, ratedBy = 0;
    Vehicle vehicle;
    string nic = "";

public:
    Driver() {}

    Driver(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password, string nic, Vehicle vehicle)
        : User(id, day, month, year, firstName, lastName, phoneNum, password), sumOfRatings(0), ratedBy(0), nic(nic), vehicle(vehicle) {}

    void appendToFile()
    {
        // FIXME: phone number not getting saved in file, neither is its value correct in uber-app.cpp over driver.appendToFile()
        ofstream file("drivers.txt", ios::app);
        file << id << "," << day << "," << month << "," << year << "," << firstName << "," << lastName << ","
             << phoneNum << "," << password << "," << nic << "," << vehicle.getType() << "," << vehicle.getModel() << "," << vehicle.getName() << "," << vehicle.getPlateNum()
             << "," << vehicle.getColor() << "," << sumOfRatings << "," << ratedBy << "\n";

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