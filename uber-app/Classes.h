#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Functions.h"
using namespace std;

// LATER: admin class

const int MAX_TRIES = 12; // LATER: change value
// const int MAX_BOOKINGS_TO_DISPLAY = 10;

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

    virtual void updateProfile()
    {
        cout << "Enter a hyphen (-) in any field that you do not want to modify" << endl;
        // TODO: enter hyphen check
        askFirstAndLastNames(&firstName, &lastName);
        askPassword(&password, true);
    }

    int getId() { return id; }
};

class Passenger;
class Driver;

class Booking
{
    int id = -1;
    string status = "available"; // available, not accepted, arriving, arrived, in progress, completed, cancelled
    char pickupLocation = '-', dropoffLocation = '-';
    string type = "";
    int fare = 0; // LATER: check if fare should be taken in float
    Passenger *passenger;
    int passengerId;
    Driver *driver;
    int driverId;
    string bookedAt = "-";
    string completedAt = "-";

    const int fare_per_km = 25;

public:
    Booking() {}

    Booking(int id, char pickupLocation, char dropoffLocation, string type, Passenger *passenger);

    // constructor for loading an already stored booking
    void loadBooking(int id, string status, char pickupLocation, char dropoffLocation, string type, int fare, int passengerId, string bookedAtStr, int driverId, string completedAt)
    {
        this->id = id;
        this->status = status;
        this->pickupLocation = pickupLocation;
        this->dropoffLocation = dropoffLocation;
        this->type = type;
        this->fare = fare;
        this->passengerId = passengerId;
        this->bookedAt = bookedAt;
        this->driverId = driverId;
        this->completedAt = completedAt;
    }

    void updateStatus(string newStatus)
    {
        // TODO: update booking status
    }

    void appendToFile();

    void completeRide()
    {
        completedAt = getCurrentTime();
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
            // LATER: 6) Delete account
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
    }

    void updateProfile() override
    {
        this->User::updateProfile();
        askDOB(&day, &month, &year, 1);
        askPhoneNum(&phoneNum, 1);

        // TODO: edit file
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

        int newId = getLastId("bookings.txt") + 1;
        Booking booking(newId, pickup, dropoff, type, this);
        booking.appendToFile();

        // wait for X seconds OR until a driver accepts a ride
        int tries = 0;
        bool found = false;

        cout << endl
             << "Checking every five seconds if any driver accepted the ride...";

        // TODO: check if user cancels the search; in that case update status to unavailable
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
            // TODO: code if ride found
        }
        else
        {
            booking.updateStatus("not accepted");
            cout << endl
                 << endl
                 << "Your ride was not accepted by any driver" << endl
                 << "Please try again later" << endl;
        }
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
        // LATER: check if friend function can be implemented
        file.close();
    }

    int displayMenu()
    {
        int opt = 0;

        do
        {
            cout << endl
                 << "1) View available rides" << endl;
            cout << "2) View history" << endl;
            cout << "3) View profile" << endl;
            cout << "4) Update profile" << endl;
            cout << "5) Logout" << endl;
            // LATER: 6) Delete account
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
        // LATER: more data?
    }

    void updateProfile() override
    {
        this->User::updateProfile();
        askDOB(&day, &month, &year, 2);
        askPhoneNum(&phoneNum, 2);

        // TODO: edit file
    }

    int viewAvailableRides()
    {
        system("cls");

        ifstream file("bookings.txt");
        string line;

        string idStr, statusStr, pickupStr, dropoffStr, typeStr, fareStr, passengerIdStr, driverIdStr, bookedAtStr, completedAtStr;
        Booking booking;
        int acceptedId;

        if (file)
        {
            while (getline(file, line))
            {
                string *fields[10] = {&idStr, &statusStr, &pickupStr, &dropoffStr, &typeStr, &fareStr, &passengerIdStr, &bookedAtStr, &driverIdStr, &completedAtStr};
                getFields(line, fields, 10);

                if (statusStr == "available" && (this->vehicle).getType() == typeStr)
                {
                    booking.loadBooking(stoi(idStr), statusStr, pickupStr[0], dropoffStr[0], typeStr, stoi(fareStr), stoi(passengerIdStr), bookedAtStr, stoi(driverIdStr), completedAtStr);

                    cout << endl
                         << "Booking ID: " << idStr;
                    cout << endl
                         << "Pickup Location: " << pickupStr;
                    cout << endl
                         << "Dropoff Location: " << dropoffStr;
                    cout << endl
                         << "Average Distance: " << abs(dropoffStr[0] - pickupStr[0]);
                    cout << endl
                         << "Vehicle Type: " << typeStr;
                    cout << endl
                         << "Booked at: " << bookedAtStr;
                }
            }

            cout << endl
                 << "Enter a booking ID to accept it: ";
            cin >> acceptedId;

            // TODO: check if acceptedId is available
        }

        return acceptedId;
    }
};

Booking::Booking(int id, char pickupLocation, char dropoffLocation, string type, Passenger *passenger)
{
    this->id = id;
    this->pickupLocation = pickupLocation;
    this->dropoffLocation = dropoffLocation;
    this->type = type;
    this->passenger = passenger;
    this->passengerId = passenger->getId();
    this->fare = fare_per_km * abs(dropoffLocation - pickupLocation); // TODO: also use type of vehicle to calculate cost
    bookedAt = getCurrentTime();

    // TODO: set driver
}

void Booking::appendToFile()
{
    ofstream file("bookings.txt", ios::app);
    file << id << "," << status << "," << pickupLocation << "," << dropoffLocation << "," << type << ","
         << fare << "," << passengerId << "," << bookedAt << "," << driverId << "," << completedAt << "\n";
    file.close();
}