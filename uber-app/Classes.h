#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Functions.h"
#include "Questions.h"
using namespace std;

// LATER: admin class

const int MAX_TRIES = 3; // LATER: change value
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

    virtual void updateProfile(bool isPassenger)
    {
        cout << endl
             << "If you do not want to update a field then enter a hyphen (-) in it if it is a text field and -1 if it is a number field" << endl;

        string firstName2, lastName2, password2;
        int day2, month2, year2;
        string phoneNum2;
        int age;

        askName(firstName2, true, true);
        askName(lastName2, false, true);
        askPassword(password2, password, true);

        do
        {
            askDate(1, day2, 1, 31, true);
            askDate(2, month2, 1, 12, true);
            askDate(3, year2, current_year - 120, current_year, true);

            if (day2 == -1)
                day2 = day;
            if (month2 == -1)
                month2 = month;
            if (year2 == -1)
                year2 = year;

            if (!isPassenger)
            {
                age = getAge(day2, month2, year2);
                if (age < 18)
                    cerr << endl
                         << "Error: driver must be at least 18 years old" << endl;
            }
        } while (!isPassenger && age < 18);

        askPhoneNum(phoneNum2, isPassenger, true);

        if (firstName2 != "-")
            firstName = firstName2;
        if (lastName2 != "-")
            lastName = lastName2;
        if (password2 != "-")
            password = password2;
        if (phoneNum2 != "-" && phoneNum2 != "0")
            phoneNum = phoneNum2;
        if (day2 != -1)
            day = day2;
        if (month2 != -1)
            month = month2;
        if (year2 != -1)
            year = year2;

        // TODO: update the member variables and file
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
    int passengerId = -1;
    Driver *driver;
    int driverId = -1;
    string bookedAt = "-";
    string completedAt = "-";

    const int fare_per_km = 25;

public:
    Booking() {}
    Booking(int id) : id(id) {}
    Booking(int id, char pickupLocation, char dropoffLocation, string type, Passenger *passenger);

    // constructor for loading an already stored booking
    void load(int id, string status, char pickupLocation, char dropoffLocation, string type, int fare, int passengerId, string bookedAtStr, int driverId, string completedAt)
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

    friend void updateBooking(Booking &booking, string newStatus, int newDriverId, string newCompletedAt);

    bool checkFound()
    {
        ifstream file("bookings.txt");
        string idStr, statusStr, driverIdStr;

        string line;
        bool found = false;

        while (getline(file, line))
        {
            ss.clear();
            ss.str(line);
            getline(ss, idStr, ',');

            if (stoi(idStr) == id)
            {
                getline(ss, statusStr, ',');
                if (statusStr == "accepted")
                {
                    for (int i = 0; i < 7; i++)
                        getline(ss, driverIdStr, ',');

                    driverId = stoi(driverIdStr);
                    // TODO: ride starting time
                    found = true;
                }
            }
        }

        file.close();
        return found;
    }

    void appendToFile();

    void completeRide()
    {
        completedAt = getCurrentTime();
    }

    void getFromFile()
    {
        ifstream file("bookings.txt");
        string idStr, statusStr, pickupLocationStr, dropoffLocationStr, typeStr,
            fareStr, passengerIdStr, bookedAtStr, driverIdStr, completedAtStr;
        string line;
        bool found = false;

        string *fields[10] = {&idStr, &statusStr, &pickupLocationStr, &dropoffLocationStr, &typeStr, &fareStr, &passengerIdStr, &bookedAtStr, &driverIdStr, &completedAtStr};
        while (getline(file, line))
        {
            ss.clear();
            ss.str(line);
            getFields(line, fields, 10);
            // getline(ss, idStr, ',');

            if (stoi(idStr) == id)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            status = statusStr;
            pickupLocation = pickupLocationStr[0];
            dropoffLocation = dropoffLocationStr[0];
            type = typeStr;
            // fare = stoi(fareStr);
            // passengerId = stoi(passengerIdStr);
            // bookedAt = bookedAtStr;
            // driverId = stoi(driverIdStr);
            // completedAt = completedAtStr;
        }

        file.close();
    }

    void display()
    {
        cout << endl
             << "Booking ID: " << id;
        if (driverId != -1)
        {
            cout << endl
                 << "Driver ID: " << driverId;
            // TODO:
            // driver->setId(driverId);
            // driver->getFromFile();
            // cout ...
        }
        cout << endl
             << "Pickup Location: " << pickupLocation;
        cout << endl
             << "Dropoff Location: " << dropoffLocation;
        cout << endl
             << "Average Distance: " << abs(dropoffLocation - pickupLocation) << " km";
        cout << endl
             << "Vehicle Type: " << type;
        cout << endl
             << "Booked at: " << bookedAt << endl;
    }
};

void updateBooking(Booking &booking, string newStatus, int newDriverId, string newCompletedAt)
{
    ifstream file("bookings.txt");

    ofstream file2("bookings2.txt");
    file2.close();
    file2.open("bookings2.txt", ios::app);
    // string idStr, statusStr, pickupLocationStr, dropoffLocationStr, typeStr,
    // fareStr, passengerIdStr, bookedAtStr, driverIdStr, completedAtStr;

    // string *fields[10] = {&idStr, &statusStr, &pickupLocationStr, &dropoffLocationStr, &typeStr, &fareStr, &passengerIdStr, &bookedAtStr, &driverIdStr, &completedAtStr};

    string line, idStr;
    while (getline(file, line))
    {
        ss.clear();
        ss.str(line);
        getline(ss, idStr, ',');

        if (stoi(idStr) == booking.id)
            line = to_string(booking.id) + "," + newStatus + "," + booking.pickupLocation + "," + booking.dropoffLocation + "," + booking.type + "," + to_string(booking.fare) + "," + to_string(booking.passengerId) + "," + booking.bookedAt + "," + to_string(newDriverId) + "," + newCompletedAt;

        file2 << line << "\n";
    }

    file.close();
    file2.close();

    remove("bookings.txt");
    rename("bookings2.txt", "bookings.txt");
}

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

    // void updateProfile() override
    // {
    //     this->User::updateProfile();
    //     // TODO: edit file
    // }

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

            pickup = toupper(pickup);
            dropoff = toupper(dropoff);
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

            found = booking.checkFound();

            if (!found)
                tries++;
            else
                found = true;
        }

        if (found)
        {
            cout << endl
                 << "Ride found!" << endl;

            booking.getFromFile();
            booking.display();
        }
        else
        {
            updateBooking(booking, "unavailable", -1, "-");
            // TODO: check that if ctrl+c is pressed then the line above can be made to run or not
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

    // void updateProfile() override
    // {
    //     this->User::updateProfile();

    //     // TODO: edit file
    // }

    void viewAvailableRides(int &acceptedId, Booking &booking, bool &found)
    {
        system("cls");

        ifstream file("bookings.txt");
        string line;

        string idStr, statusStr, pickupStr, dropoffStr, typeStr, fareStr, passengerIdStr, driverIdStr, bookedAtStr, completedAtStr;

        acceptedId = -1;
        found = false;

        if (file)
        {
            while (getline(file, line))
            {
                string *fields[10] = {&idStr, &statusStr, &pickupStr, &dropoffStr, &typeStr, &fareStr, &passengerIdStr, &bookedAtStr, &driverIdStr, &completedAtStr};
                getFields(line, fields, 10);

                if (statusStr == "available" && (this->vehicle).getType() == typeStr)
                {
                    booking.load(stoi(idStr), statusStr, pickupStr[0], dropoffStr[0], typeStr, stoi(fareStr), stoi(passengerIdStr), bookedAtStr, stoi(driverIdStr), completedAtStr);
                    booking.display();
                }

                cout << endl
                     << "Enter a booking ID to accept it (enter -2 to cancel): ";
                cin >> acceptedId;

                if (acceptedId < -1)
                    acceptedId = -2;

                if (acceptedId > -1)
                {
                    ifstream file("bookings.txt");
                    string line, idStr, statusStr;

                    while (getline(file, line))
                    {
                        ss.clear();
                        ss.str(line);
                        getline(ss, idStr, ',');
                        getline(ss, statusStr, ',');

                        if (stoi(idStr) == acceptedId && statusStr == "available")
                            found = true;
                    }
                }
            }

            file.close();
        }
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