//
// Created by MacBook Air on 24/01/24.
//
#include "SQLiteDBCar.h"
SQLiteDBCar& SQLiteDBCar::getInstance(const char* dbName) {

    static SQLiteDBCar instance(dbName);

    return instance;
}

SQLiteDBCar::SQLiteDBCar(const char *dbName) {
    int rc = sqlite3_open(dbName, &db);

    if (rc != SQLITE_OK) {
        cerr << "Cannot Open or Create the Database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    createTable();
}


SQLiteDBCar::~SQLiteDBCar() {
    sqlite3_close(db);
}
void SQLiteDBCar::createTable(){
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS Car (CarID INTEGER PRIMARY KEY AUTOINCREMENT, CarMake TEXT NOT NULL, CarModel TEXT NOT NULL, Mileage INTEGER NOT NULL, Year INTEGER NOT NULL, Availability INTEGER NOT NULL, MinimumPeriod INTEGER NOT NULL, MaximumPeriod INTEGER NOT NULL, Price REAL NOT NULL);";
    char *errMsg = nullptr;

    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Cannot create table: " << errMsg << endl;
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}
void SQLiteDBCar::searchCar(const int response, const string keyword){
    if (response == 1) {
        const char *selectDataSQL = "SELECT * FROM Car WHERE CarMake COLLATE SQL_Latin1_General_CP1_CI_AS LIKE ? AND Availability = 1;";
        sqlite3_stmt *stmt;

        if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
            cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
            exit(EXIT_FAILURE);
        }
        string KeyWord = "%" + keyword + "%";
        if (sqlite3_prepare_v2(db, selectDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, KeyWord.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_ROW) {
                cout << "There are not related results." << endl;
            } else {
                do {
                    int carid = sqlite3_column_int(stmt, 0);
                    const char *Carmake = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
                    const char *Carmodel = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
                    int Mileage = sqlite3_column_int(stmt, 3);
                    int year = sqlite3_column_int(stmt, 4);
                    int availability = sqlite3_column_int(stmt, 5);
                    int minperiod = sqlite3_column_int(stmt, 6);
                    int maxperiod = sqlite3_column_int(stmt, 7);
                    double price = sqlite3_column_double(stmt, 8);
                    cout << "CardID: " << carid << " Car Make: " << Carmake << " Car model: " << Carmodel
                         << " Mileage: " << Mileage << " Year: " << year << " Availability: " << availability
                         << " Minperiod: " << minperiod << " Maxperiod: " << maxperiod << " Price: " << price
                         << endl;
                } while (sqlite3_step(stmt) == SQLITE_ROW);


            }

            sqlite3_finalize(stmt);
        }
        else{
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;

        }
    }
    else{
        const char* SearchDataSQL = "SELECT * FROM Car WHERE CarModel COLLATE SQL_Latin1_General_CP1_CI_AS LIKE ? AND Availability = 1;";
        sqlite3_stmt *stmt;

        if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
            cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
            exit(EXIT_FAILURE);
        }
        string KeyWord = "%" + keyword + "%";
        if (sqlite3_prepare_v2(db, SearchDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, KeyWord.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_ROW) {
                cout << "There are not related results." << endl;
            } else {
                do {
                    int carid = sqlite3_column_int(stmt, 0);
                    const char *Carmake = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
                    const char *Carmodel = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
                    int Mileage = sqlite3_column_int(stmt, 3);
                    int year = sqlite3_column_int(stmt, 4);
                    int availability = sqlite3_column_int(stmt, 5);
                    int minperiod = sqlite3_column_int(stmt, 6);
                    int maxperiod = sqlite3_column_int(stmt, 7);
                    double price = sqlite3_column_double(stmt, 8);
                    cout << "CardID: " << carid << " Car Make: " << Carmake << " Car model: " << Carmodel
                         << " Mileage: " << Mileage << " Year: " << year << " Availability: " << availability
                         << " Minperiod: " << minperiod << " Maxperiod: " << maxperiod << " Price: " << price
                         << endl;
                } while (sqlite3_step(stmt) == SQLITE_ROW);


            }
            sqlite3_finalize(stmt);

        }
        else{
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;

        }
    }
}

//Display all available car to the customer
void SQLiteDBCar::displayCar() {
    const char *selectDataSQL = "SELECT * FROM Car WHERE Availability = 1;";
    sqlite3_stmt *stmt;

    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, selectDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout<<"There are not available car currently"<<endl;
        } else {
            sqlite3_exec(db, selectDataSQL, callbackPrintData, nullptr, nullptr);
        }
        sqlite3_finalize(stmt);

    }

}
//Display all car records to the Admin
void SQLiteDBCar::AdmindisplayCar() {
    const char *selectDataSQL = "SELECT * FROM Car;";
    sqlite3_stmt *stmt;
    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, selectDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << "There are not cars currently" << endl;
        } else {
            sqlite3_exec(db, selectDataSQL, callbackPrintData, nullptr, nullptr);
        }
        sqlite3_finalize(stmt);
    }
}
//Add the car for rental into the car database
void SQLiteDBCar::addCar(const Car& car){
    const char* insertDataSQL = "INSERT INTO Car (CarMake, CarModel, Mileage, Year, Availability, MinimumPeriod, MaximumPeriod, Price) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }

    if (sqlite3_prepare_v2(db, insertDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, car.getCarMake().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, car.getCarModel().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, car.getMileage());
        sqlite3_bind_int(stmt, 4, car.getYear());
        sqlite3_bind_int(stmt, 5, car.getAvailability());
        sqlite3_bind_int(stmt, 6, car.getMinimumPeriod());
        sqlite3_bind_int(stmt, 7, car.getMaximumPeriod());
        sqlite3_bind_double(stmt, 8, car.getPrice());



        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
        }

        cout<<"The car has been successfully added."<<endl;

        sqlite3_finalize(stmt);
    }else {

cerr << "Error preparing statement from adding car: " << sqlite3_errmsg(db) << endl;
}


}
//Delete the car record
void SQLiteDBCar::deleteCar(int id) {
    const char* caridcheck = "SELECT * FROM Car WHERE CarID = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }

    if (sqlite3_prepare_v2(db, caridcheck, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << "The Car ID is not identified" << endl;
        } else {
            const char *deleteDataSQL = "DELETE FROM Car WHERE CarID = ?;";
            sqlite3_finalize(stmt);
            if (sqlite3_prepare_v2(db, deleteDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmt, 1, id);

                if (sqlite3_step(stmt) != SQLITE_DONE) {
                    std::cerr << "Error deleting data: " << sqlite3_errmsg(db) << endl;
                }
                sqlite3_finalize(stmt);
                cout << "The Car record is successfully deleted" << endl;
            }
        }
    }
}
//Update the car record
void SQLiteDBCar::updateCar(const Car& car, const int id){
    const char* caridcheck = "SELECT * FROM Car WHERE CarID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, caridcheck, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_DONE){
            cout<<"The Car ID is not identified"<<endl;
        }
        else{
            const char* updateDataSQL = "UPDATE Car SET CarMake = ?, CarModel = ?, Mileage = ?, Year = ?, Availability = ?, MinimumPeriod = ?, MaximumPeriod = ?, Price = ? WHERE CarID = ?;";
            sqlite3_finalize(stmt);

            if (sqlite3_prepare_v2(db, updateDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, car.getCarMake().c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, car.getCarModel().c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 3, car.getMileage());
                sqlite3_bind_int(stmt, 4, car.getYear());
                sqlite3_bind_int(stmt, 5, car.getAvailability());
                sqlite3_bind_int(stmt, 6, car.getMinimumPeriod());
                sqlite3_bind_int(stmt, 7, car.getMaximumPeriod());
                sqlite3_bind_double(stmt, 8, car.getPrice());
                sqlite3_bind_int(stmt, 9, id);


                if (sqlite3_step(stmt) != SQLITE_DONE) {
                    cerr << "Error updating data: " << sqlite3_errmsg(db) << endl;
                }
                cout<<"The car detail has been updated"<<endl;

                sqlite3_finalize(stmt);
            }
        }
    }



}
//When the car is rented, the availability becomes unavailability (0).
void SQLiteDBCar::carNotAvailability(const int carid){
    const char* updateSQLDB = "UPDATE Car SET Availability = 0 WHERE CarID = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, updateSQLDB, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, carid);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error updating data: " << sqlite3_errmsg(db) << endl;
        }

        sqlite3_finalize(stmt);
    }
}
//Change the availability back to 1, when the admin reject the request
void SQLiteDBCar::carAvailability(const int carid) {
    const char* updateCarSQLDB = "UPDATE Car SET Availability = 1 WHERE CarID = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, updateCarSQLDB, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, carid);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error updating data: " << sqlite3_errmsg(db) << endl;
        }

        sqlite3_finalize(stmt);
    }

}

//Check whether the car id exists and its minimum and maximum rental period
bool SQLiteDBCar::checkCardetail(int carid, int& minperiod,  int& maxPeriod) {
    const char* selectOperation = "SELECT * FROM Car WHERE CarID = ? AND Availability = 1;";
    sqlite3_stmt* selectstmt;
    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }


    if (sqlite3_prepare_v2(db, selectOperation, -1, &selectstmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(selectstmt, 1, carid);

        //Check whether there are result for MinimumPeriod and MaximumPeriod
        if (sqlite3_step(selectstmt) == SQLITE_ROW) {
            const char* checkPeriod = "SELECT MinimumPeriod, MaximumPeriod FROM Car WHERE CarID = ?;";
            sqlite3_stmt* Checkstmt;


            if (sqlite3_prepare_v2(db, checkPeriod, -1, &Checkstmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(Checkstmt, 1, carid);

                // Check if there is a row for the given carid and retrieve values
                if (sqlite3_step(Checkstmt) == SQLITE_ROW) {
                    minperiod = sqlite3_column_int(Checkstmt, 0);
                    maxPeriod = sqlite3_column_int(Checkstmt, 1);

                    // Finalize the second statement
                    sqlite3_finalize(Checkstmt);

                    // Finalize the first statement
                    sqlite3_finalize(selectstmt);

                    return true;
                } else {
                    // Handle the case when no row is found for the second statement
                   cout << "The minimum and maximum period are not found for CarID: " << carid << endl;
                }

                // Finalize the second statement
                sqlite3_finalize(Checkstmt);
            } else {
                // Handle the case when the second statement preparation fails
                cerr << "Error preparing statement for checkPeriod: " << sqlite3_errmsg(db) << endl;
            }
        } else {
            // Handle the case when no row is found for the first statement
            cout << "The Car id is not identified" << endl;
        }

        // Finalize the first statement
        sqlite3_finalize(selectstmt);
    } else {
        // Handle the case when the first statement preparation fails
        cerr << "Error preparing statement from selectOperation: " << sqlite3_errmsg(db) << endl;
    }

    return false;
}

//Check the car price with car id
double SQLiteDBCar::checkCarPrice(const int carid){
    const char* checkPrice = "SELECT Price FROM Car WHERE CarID = ?;";
    double price = -1.0;
    sqlite3_stmt* stmt;
    if (sqlite3_open("Car.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, checkPrice, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, carid);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            price = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    else{
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;

    }
    return price;
}







int SQLiteDBCar::callbackPrintData(void *, int argc, char** argv, char** ColNames) {
    for (int i = 0; i < argc; ++i) {
        cout <<ColNames[i]<<": "<<argv[i] << " ";
    }
    cout << endl;

    return 0;
}



