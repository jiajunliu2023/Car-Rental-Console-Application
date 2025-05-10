//
// Created by MacBook Air on 24/01/24.
//

#ifndef CARRENTAL_SQLITEDBCAR_H
#define CARRENTAL_SQLITEDBCAR_H
#include <iostream>
#include <sqlite3.h>
#include "Car.h"
class SQLiteDBCar {
public:
    static SQLiteDBCar& getInstance(const char* dbName);

    //Filter the car data with car make or model through key word
    void searchCar(const int response, const string keyword);

    //Display all available car to the customer
    void displayCar();
    //Display all car records to the Admin
    void AdmindisplayCar();
    //Add the car for rental into the car database
    void addCar(const Car& car);
    //Delete the car record
    void deleteCar(int id);
    //Update the car record
    void updateCar(const Car& car, const int id);
    //When the car is rented, the availability becomes unavailability (0).
    void carNotAvailability(const int carid);
    //Change the availability back to 1, when the admin reject the request
    void carAvailability(const int carid);

    //Check whether the car id exists and its minimum and maximum rental period
    bool checkCardetail(int carid, int& minperiod, int& maxPeriod);
    //Check the car price with car id
    double checkCarPrice(const int carid);

    //Update the book status

    ~SQLiteDBCar();





private:
    sqlite3 *db;

    SQLiteDBCar(const char *dbName);

    void createTable();

    static int callbackPrintData(void *, int argc, char** argv, char** ColNames);



};
#endif //CARRENTAL_SQLITEDBCAR_H
