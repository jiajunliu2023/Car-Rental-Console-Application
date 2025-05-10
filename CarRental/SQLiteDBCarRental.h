//
// Created by MacBook Air on 24/01/24.
//

#ifndef CARRENTAL_SQLITEDBCARRENTAL_H
#define CARRENTAL_SQLITEDBCARRENTAL_H
#include <iostream>
#include <sqlite3.h>
#include "Car.h"
#include "SQLiteDBCar.h"
class SQLiteDBCarRental{
public:
    static SQLiteDBCarRental& getInstance(const char* dbName);
    ~SQLiteDBCarRental();
//Add the car rental record with the rental status as pending
    void AddCarRental(const string startDate, const string endDate, const int carid, const int id);
//Show the Admin the pending car rental booking request
    void ShowPendingBook();
//First check the rental id with pending book status is inputted is identified  then accept or reject the book status
    void ProcessRental(const int RentalID, const int response, SQLiteDBCar CarDB);
//Delete the car rental record with rental id
    void deletebook(const int id);
    //Update the book status
    void UpdateQuery(const int RentalID, const char* status, const char* Query);

    //Get the Car id by rental id
    int ReceiveCarID(const int rentalid);

private:
    sqlite3 *db;
    SQLiteDBCarRental(const char *dbName);
    void createTable();
    static int callbackPrintData(void *, int argc, char** argv, char** ColNames);
};
#endif //CARRENTAL_SQLITEDBCARRENTAL_H
