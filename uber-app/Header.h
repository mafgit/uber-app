#pragma once
#include <iostream>
using namespace std;

class Passenger {
	int id, age;
	string firstName, lastName, phoneNum, password;
};


class Driver {
	int id, age, sumOfRatings, userCountOfRating;
	string firstName, lastName, phoneNum;
};

class Vehicle {
	int model, noOfSeats;
	string brand, plateNum, color;
};

class Car {

};

class Bike {

};

class Rickshaw {

};

class Booking {
	string type;
	char pickup, dropoff;

};