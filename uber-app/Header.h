#pragma once
#include <iostream>
using namespace std;

// todo: inheritance (User -> Driver, Passenger, and if there's time and energy, then Admin);

class User {
protected:
	int id, day, month, year;
	string firstName, lastName, phoneNum, nic, password;
public:
	User() {
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
		return phoneNum;
	}
};

class Passenger : public User {
public:
	Passenger() {}

	Passenger(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password)
		: User(id, day,  month,  year, firstName, lastName, phoneNum, password) {}

	void appendToFile() {

	}

};

class Vehicle {
	int model, noOfSeats;
	string brand, plateNum, color, type;
	// types: bike, ride_ac, ride, ride_mini, auto
};

class Driver : public User {
	int sumOfRatings, userCountOfRating;
	Vehicle vehicle;
	string nic;

public:
	Driver() {
		sumOfRatings=0;
		userCountOfRating=0;
		nic = "";
		// todo: vehicle initialization
	}

	Driver(int id, int day, int month, int year, string firstName, string lastName, string phoneNum, string password, Vehicle vehicle, string nic)
		: User(id, day,  month,  year, firstName, lastName, phoneNum, password), sumOfRatings(0), userCountOfRating(0), vehicle(vehicle), nic(nic) {}
	
	void appendToFile() {}
};

class Booking {
	char pickupLocation, dropoffLocation;
	int fare; // todo: check if fare should be taken in float
	Passenger passenger;
	Driver driver;
	// todo: bookedAt (time of booking)
	// todo: completedAt
	string status; // arriving, arrived, in_progress, completed, cancelled
};