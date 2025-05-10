
//The first time to create the database, the error message occurs (may solve the problem, since the createtable function has been deleted to INSERT SQL operation.
//The Admin can accept and reject the booking request (When the book is rejected, the car availability is stll 0
//When the data is added, it can show in the database, but the program running can not identify it.
//Try to use the try to identify the potential invalid input
//When insert the new car book record, sometimes "Error preparing statement: bad parameter or other API misuse" happens

#include <iostream>
#include "UserManager.h"
#include "Webpage.h"
#include "SQLiteDBUser.h"
#include "SQLiteDBCar.h"
#include "SQLiteDBCarRental.h"
#include "CarManager.h"




int main() {
    UserManager um;
    CarManager cm;
    SQLiteDBUser& UserDB = SQLiteDBUser::getInstance("User.db");
    SQLiteDBCar& CarDB = SQLiteDBCar::getInstance("Car.db");
    SQLiteDBCarRental& CarRentalDB = SQLiteDBCarRental::getInstance("CarRental.db");
    int number;
    while (true) {
        number = Homepage();
        if (number == 1) {
            um.Register(UserDB);
        } else if (number == 2) {
            int n = um.Userlogin(UserDB);
                if (n == -1) {
                    cout<<"The Username does not match the password";
                }
                else if (n == 0) {
                     cout << "Successfully login as Admin" << endl;
                     while (true) {
                         number = AdminMenu();
                         if (number == 1) {
                             CarDB.AdmindisplayCar();
                         } else if (number == 2) {
                             cm.AddCar(CarDB);
                         } else if (number == 3) {
                             cm.UpdateCar(CarDB);
                         } else if (number == 4) {
                             cm.DeleteCar(CarDB);
                         } else if (number == 5) {
                             CarRentalDB.ShowPendingBook();
                         } else if (number == 6){
                             cm.ManageBook(CarRentalDB, CarDB);
                         } else if (number == 7){
                             cm.DeleteBook(CarRentalDB);
                         }
                         else if (number == 8) {
                             break;
                         } else {
                             cout << "Please enter the valid number" << endl;
                         }
                     }
                }

                else{
                     cout << "Successfully login as Customer" << endl;
                     while (true) {
                         int userID = n;
                         number = CustomerMenu();
                         if (number == 1) {
                             CarDB.displayCar();
                         } else if (number == 2){
                             cm.SearchCar(CarDB);
                         }else if (number == 3) {
                             cm.CarRental(CarRentalDB, CarDB, userID);
                         } else if (number == 4){
                             break;
                         } else {
                             cout << "Please enter the valid number" << endl;
                         }
                     }
                 }


        } else if (number == 3) {
            break;
        }
        else{
            cout<<"Please enter a valid number"<<endl;
        }
    }


    return 0;
}