#pragma once
#include <iostream>
using namespace std;

// todo: inheritance (User -> Driver, Passenger, and if there's time and energy, then Admin);

class User {
protected:
	int id, age;
	string firstName, lastName, phoneNum, nic, password;
public:
	User(int id, int age, string firstName, string lastName, string phoneNum, string password) : id(id), age(age), firstName(firstName), lastName(lastName), phoneNum(phoneNum), password(password) {}

};

class Passenger : public User {
public:
	Passenger(int id, int age, string firstName, string lastName, string phoneNum, string password)
		: User(id, age, firstName, lastName, phoneNum, password) {}

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
	Driver(int id, int age, string firstName, string lastName, string phoneNum, string password, int sumOfRatings, int userCountOfRating, Vehicle vehicle, string nic)
		: User(id, age, firstName, lastName, phoneNum, password), sumOfRatings(sumOfRatings), userCountOfRating(userCountOfRating), vehicle(vehicle), nic(nic) {}
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