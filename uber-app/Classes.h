#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Menus.h"
#include <windows.h>
using namespace std;

// TODO: admin class

const int MAX_TRIES = 2; // TODO: change value
class User
{
protected:
    int id = -1, day = 0, month = 0, year = 0;
    string firstName = "", lastName = "", phoneNum = "", password = "";

public:
    User() {}

    User(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password) : id(id), day(day), month(month), year(year), firstName(firstName), lastName(lastName), phoneNum(phoneNum), password(password) {}

    virtual void viewProfile()
    {
        system("cls");
        cout << endl
             << "ID: " << id << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Date of Birth (D/M/Y): " << day << "/" << month << "/" << year << endl;
        cout << "Phone Number: " << phoneNum << endl;
    }
};

class Passenger;
class Driver;

class Booking
{
    char pickupLocation = '-', dropoffLocation = '-';
    int fare = 0; // TODO: check if fare should be taken in float
    Passenger *passenger;
    Driver *driver;
    // TODO: bookedAt (time of booking)
    // TODO: completedAt
    string status = "searching"; // searching, arriving, arrived, in progress, completed, cancelled

public:
    Booking(char pickupLocation, char dropoffLocation, Passenger *passenger)
    {
        this->pickupLocation = pickupLocation;
        this->dropoffLocation = dropoffLocation;
        this->passenger = passenger;
        // TODO: set time, fare and driver;
    }

    void appendToFile()
    {
        // TODO: make appendToFile
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

        // if (opt == 1)
        //     bookARide();
        // if (opt == 3)
        //     viewProfile();

        return opt;
    }

    void viewProfile() override
    {
        this->User::viewProfile();
        // TODO: more data?
        // TODO: show menu again
    }

    void bookARide()
    {
        system("cls");
        char pickup, dropoff;

        do
        {
            cout << endl
                 << "Enter pickup location (enter any location from A to Z): ";
            cin >> pickup;

            cout << "Enter dropoff location (make sure not to use the same location as pickup): ";
            cin >> dropoff;
        } while (pickup < 'A' || pickup > 'Z' || dropoff < 'A' || dropoff > 'Z' || pickup == dropoff);

        cout << endl
             << "Enter a number to select the type of vehicle that you want to book: " << endl;
        string type = typesMenu();

        // TODO: appendToFile for booking
        Booking booking(pickup, dropoff, this);
        booking.appendToFile();

        // wait for X seconds OR until a driver accepts a ride
        int tries = 0;
        bool found = false;

        cout << endl
             << "Checking every five seconds if any driver accepted the ride...";

        while (tries < MAX_TRIES && !found)
        {
            cout << endl
                 << "Wait... ";
            for (int i = 1; i <= 5; i++)
            {
                cout << i << " ";
                Sleep(1000);
            }

            // TODO: found = checkRideFound(booking);

            if (!found)
                tries++;
            else
                found = true;
        }

        if (found)
        {
            // TODO:
        }
        else
        {
            cout << endl
                 << "Your ride was not accepted by any driver" << endl;
        }

        // TODO: show menu again
    }
};

class Vehicle
{
    string type = "", make = "", model = "", trimLevel = "", plateNum = "", color = "";
    int yearOfManufacture = 0;

public:
    Vehicle() {}

    Vehicle(string type, int yearOfManufacture, string make, string model, string trimLevel, string plateNum, string color)
    {
        this->type = type;
        this->yearOfManufacture = yearOfManufacture;
        this->make = make;
        this->model = model;
        this->trimLevel = trimLevel;
        this->plateNum = plateNum;
        this->color = color;
    }

    // getters
    string getMake() { return make; }
    string getModel() { return model; }
    string getTrimLevel() { return trimLevel; }
    string getPlateNum() { return plateNum; }
    string getColor() { return color; }
    string getType() { return type; }
    int getYearOfManufacturer() { return yearOfManufacture; }

    void viewData()
    {
        cout << endl
             << "Vehicle Data: " << endl;
        cout << "Name: " << yearOfManufacture << " " << make << " " << model << " " << trimLevel << endl;
        cout << "Type: " << type << endl;
        cout << "Color: " << color << endl;
        cout << "Plate Number: " << plateNum << endl;
    }
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
        ofstream file("drivers.txt", ios::app);
        file << id << "," << day << "," << month << "," << year << "," << firstName << "," << lastName << ","
             << phoneNum << "," << password << "," << nic << "," << vehicle.getType() << "," << vehicle.getYearOfManufacturer() << "," << vehicle.getMake() << "," << vehicle.getModel() << "," << vehicle.getTrimLevel() << "," << vehicle.getPlateNum() << "," << vehicle.getColor() << "," << sumOfRatings << "," << ratedBy << "\n";
        // TODO: check if friend function can be implemented
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

        // if (opt == 3)
        //     viewProfile();

        return opt;
    }

    void viewProfile() override
    {
        this->User::viewProfile();
        cout << "NIC: " << nic << endl;
        cout << "Average Rating: " << (ratedBy == 0 ? 0 : sumOfRatings / ratedBy) << endl;
        cout << "Rated by: " << ratedBy << " passengers" << endl;
        vehicle.viewData();
        // TODO: more data?
        // TODO: show menu again
    }
};
