//
// Created by MacBook Air on 24/01/24.
//
#include "CarManager.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void CarManager::SearchCar(SQLiteDBCar CarDB){
    int response;
    string keyword;
    cout<<"*******************************"<<endl;
    cout << "Please enter search response (1 for searching for Car Make (brand), 2 for searching for the Car Model): ";
    cin >> response;
    cout <<"Please enter the key word: ";
    cin >> keyword;
    cout<<"*******************************"<<endl;
    CarDB.searchCar(response, keyword);

}
void CarManager::AddCar(SQLiteDBCar CarDB){
    string carmodel, carmake;
    int year, mileage, availability, minimumperiod, maximumperiod;
    double price;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Add Car"<<endl;
    cout<<"*******************************"<<endl;
    cout << "Please enter the Car Make (brand): ";
    cin >> carmake;
    cout << "Please enter the Car Model: ";
    cin >> carmodel;
    cout << "Please enter the year when the car was made: ";
    cin >> year;
    cout<<"Please enter the mileage (km): ";
    cin >> mileage;
    cout << "Please enter the availability (1 for available or 0 for not available): ";
    cin >> availability;
    cout<<"Please enter the Minimum period for rental (day): ";
    cin >> minimumperiod;
    cout<<"Please enter the Maximum period for rental (day): ";
    cin >> maximumperiod;
    cout<<"Please enter the price for this rented car per day in NZ dollar: ";
    cin>>price;
    cout<<"*******************************"<<endl;
    Car car(carmake, carmodel, mileage, year, availability, minimumperiod, maximumperiod, price);
    CarDB.addCar(car);
}
void CarManager::DeleteCar(SQLiteDBCar CarDB){
    int carid;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Delete Car"<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Please enter the Car ID of the car that you want to delete: ";
    cin >>carid;
    cout<<"*******************************"<<endl;
    cout<<endl;
    CarDB.deleteCar(carid);
}
void CarManager::UpdateCar(SQLiteDBCar CarDB){
    string carmodel, carmake;
    int year, mileage, availability, minimumperiod, maximumperiod;
    double price;
    int num;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Update Car"<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Please enter the the car id for updating car: ";
    cin >>num;
    cout << "Please enter the updated value for Car Make (brand): ";
    cin >> carmake;
    cout << "Please enter the update value for Car model: ";
    cin >> carmodel;
    cout << "Please enter the update value for year when the car was made: ";
    cin >> year;
    cout<<"Please enter the update value for mileage (km): ";
    cin >> mileage;
    cout << "Please enter the update value for availability (1 for available or 0 for not available): ";
    cin >> availability;
    cout<<"Please enter the update value for Minimum period for rental (day): ";
    cin >> minimumperiod;
    cout<<"Please enter the update value for Maximum period for rental (day): ";
    cin >> maximumperiod;
    cout<<"Please enter the update value for price for this rented car per day in NZ dollar: ";
    cin>>price;
    cout<<"*******************************"<<endl;
    Car car(carmake, carmodel, mileage, year, availability, minimumperiod, maximumperiod, price);
    CarDB.updateCar(car, num);
}
void CarManager::CarRental(SQLiteDBCarRental CarRentalDB, SQLiteDBCar CarDB, int id){
    int carid, minperiod, maxperiod;
    string startDate, endDate;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Please enter the Car Id of car that you want to book: ";
    cin>>carid;
    cout <<"Please enter the startDate in the format of YYYY-MM-DD: ";
    cin>>startDate;
    cout <<"Please enter the endDate in the format of YYYY-MM-DD: ";
    cin>>endDate;
    cout<<"*******************************"<<endl;
    if (CarDB.checkCardetail(carid, minperiod, maxperiod)) {
        tm startingDate = {0};
        startingDate.tm_year = stoi(startDate.substr(0, 4)) -1900;
        startingDate.tm_mon = stoi(startDate.substr(5,2)) -1;
        startingDate.tm_mday = stoi(startDate.substr(8, 2));

        tm EndingDate = {0};
        EndingDate.tm_year = stoi(endDate.substr(0, 4)) -1900;
        EndingDate.tm_mon = stoi(endDate.substr(5,2)) -1;
        EndingDate.tm_mday = stoi(endDate.substr(8, 2));

        time_t startingTime = mktime(&startingDate);
        time_t EndingTime  = mktime(&EndingDate);
        time_t difference = EndingTime - startingTime;
        int DayDifference =  difference/(60 * 60 * 24);
        if (DayDifference < minperiod){
            cout<<"The rental period is less than minimum period"<<endl;
        }
        else if (DayDifference > maxperiod){
            cout<<"The rental period is more than maximum period"<<endl;
        }
        else {
            CarRentalDB.AddCarRental(startDate, endDate, carid, id);
            CarDB.carNotAvailability(carid);
            double CarPrice = CarDB.checkCarPrice(carid);
            double rentalFee = DayDifference * CarPrice;
            cout<<"The Rental fee is "<<rentalFee<<endl;
            cout<<endl;


        }


    }
}
void CarManager::ManageBook(SQLiteDBCarRental CarRentalDB, SQLiteDBCar CarDB){
    int  response, RentalID;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Please enter the rental id of that you want to process: ";
    cin>>RentalID;
    cout<<"Please enter the number for booking requests, 1 for accept and 0 for reject: ";
    cin>>response;
    cout<<"*******************************"<<endl;
    CarRentalDB.ProcessRental(RentalID, response, CarDB);
}
void CarManager::DeleteBook(SQLiteDBCarRental CarRentalDB){
    int id;
    cout<<"*******************************"<<endl;
    cout<<"Please enter the rental id of that you want to delete: ";
    cin>>id;
    cout<<"*******************************"<<endl;
    CarRentalDB.deletebook(id);
}
