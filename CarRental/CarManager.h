//
// Created by MacBook Air on 24/01/24.
//

#ifndef CARRENTAL_CARMANAGER_H
#define CARRENTAL_CARMANAGER_H
#include "SQLiteDBCar.h"
#include "SQLiteDBCarRental.h"
class CarManager{
public:
    void SearchCar(SQLiteDBCar CarDB);
    void AddCar(SQLiteDBCar CarDB);
    void DeleteCar(SQLiteDBCar CarDB);
    void UpdateCar(SQLiteDBCar CarDB);
    void CarRental(SQLiteDBCarRental CarRentalDB, SQLiteDBCar CarDB, int id);
    void ManageBook(SQLiteDBCarRental CarRentalDB, SQLiteDBCar CarDB);
    void DeleteBook(SQLiteDBCarRental CarRentalDB);

};
#endif //CARRENTAL_CARMANAGER_H
