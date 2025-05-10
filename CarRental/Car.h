//
// Created by MacBook Air on 27/12/23.
//
#ifndef CARRENTAL_CAR_H
#define CARRENTAL_CAR_H
#include <iostream>
using namespace std;
class Car{
private:
    string CarMake;
    string CarModel;
    int Mileage;
    int Year;
    int Availability;
    int MinimumPeriod;
    int MaximumPeriod;
    double Price;
public:
    Car(string carMake, string carModel, int mileage, int year, int availability, int minimumPeriod, int maximumPeriod, double price) {
        CarMake = carMake;
        CarModel = carModel;
        Mileage = mileage;
        Year = year;
        Availability = availability;
        MinimumPeriod = minimumPeriod;
        MaximumPeriod = maximumPeriod;
        Price = price;

    }
    string getCarMake() const;
    string getCarModel() const ;
    int getMileage() const;
    int getYear() const;
    int getAvailability() const;
    int getMinimumPeriod() const;
    int getMaximumPeriod() const;
    double getPrice() const;


};


#endif //CARRENTAL_CAR_H
