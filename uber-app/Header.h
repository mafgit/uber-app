#pragma once
#include <iostream>
using namespace std;

// todo: inheritance (User -> Driver, Passenger, and if there's time and energy, then Admin);
// basic variables will become protected in User class
class Passenger {
	int id, age;
	string firstName, lastName, phoneNum, password;
	// todo: nic?
};

class Vehicle {
	int model, noOfSeats;
	string brand, plateNum, color;
	// todo: add name/type of vehicle like uber mini, etc
	// types: bike, ride_ac, ride, ride_mini, auto
};

class Driver {
	int id, age;
	string firstName, lastName, phoneNum, password;
	// todo: nic?
	int sumOfRatings, userCountOfRating;
	Vehicle vehicle;
};

class Booking {
	char pickupLocation, dropoffLocation;
	int fare; // in rupees, so I guess I do not need float
	Passenger passenger;
	Driver driver;
	// todo: bookedAt (time of booking)
	string status; // coming, ready, going, completed, cancelled
	// todo: maybe I shouldn't add this many values for status
};