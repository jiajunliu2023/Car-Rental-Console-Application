//
// Created by MacBook Air on 24/01/24.
//

#include "SQLiteDBCarRental.h"
#include "SQLiteDBCar.h"
SQLiteDBCarRental& SQLiteDBCarRental::getInstance(const char* dbName) {
    static SQLiteDBCarRental instance(dbName);
    return instance;
}
SQLiteDBCarRental::SQLiteDBCarRental(const char *dbName) {
    int rc = sqlite3_open(dbName, &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot Open or Create the Database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    createTable();
}
SQLiteDBCarRental::~SQLiteDBCarRental() {
    sqlite3_close(db);
}

void SQLiteDBCarRental::createTable(){
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS CarRental (RentalID INTEGER PRIMARY KEY AUTOINCREMENT, CarID INTEGER NOT NULL, UserID INTEGER NOT NULL, StartDate TEXT NOT NULL, EndDate TEXT NOT NULL, BookStatus TEXT NOT NULL, FOREIGN KEY (CarID) REFERENCES Car(CarID), FOREIGN KEY (UserID) REFERENCES User(UserID));";
    char *errMsg = nullptr;

    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Cannot create table: " << errMsg << endl;
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}

void SQLiteDBCarRental::AddCarRental(const string startDate, const string endDate, const int carid, const int id) {
    const char *CarRentalDataSQL = "INSERT INTO CarRental (CarID, UserID, StartDate, EndDate, BookStatus) VALUES (?, ?, ?, ?, 'pending');";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_open("CarRental.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, CarRentalDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, carid);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_bind_text(stmt, 3, startDate.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, endDate.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
        }
        else {
            cout << "The car is successfully rented" << endl;
        }
        sqlite3_finalize(stmt);
    }
    else{
        cerr << "Error preparing statement for adding car rental: " << sqlite3_errmsg(db) << endl;
    }

}


void SQLiteDBCarRental::ShowPendingBook() {
    const char *SelectDataSQL = "SELECT * FROM CarRental;";
    sqlite3_stmt *stmt;
    if (sqlite3_open("CarRental.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, SelectDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << "There are not car rental booking to process currently" << endl;
        } else {
            sqlite3_exec(db, SelectDataSQL, callbackPrintData, nullptr, nullptr);
        }


        sqlite3_finalize(stmt);

    }
    else{
        cerr << "Error executing statement for displaying the pending book status: " << sqlite3_errmsg(db) << endl;
    }
}

//First check the rental id is inputted is identified with pending book status, then manipulate the book status
void SQLiteDBCarRental::ProcessRental(const int RentalID, const int response, SQLiteDBCar CarDB) {
    const char* CheckRentaLIDQuery = "SELECT * FROM CarRental WHERE RentalID = ? AND BookStatus = 'pending';";

    const char* BookingAcceptQuery = "UPDATE CarRental SET BookStatus = 'accept' WHERE RentalID = ?;";

    const char* BookingRejectQuery = "UPDATE CarRental SET BookStatus = 'reject' WHERE RentalID = ?;";


    sqlite3_stmt* stmt;
    if (sqlite3_open("CarRental.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }

    // Check if the rental ID is valid and has 'pending' status
    if (sqlite3_prepare_v2(db, CheckRentaLIDQuery, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, RentalID);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            if (response == 0) {
                // Accept booking
                UpdateQuery(RentalID, "reject", BookingRejectQuery);

                int CarID =  ReceiveCarID(RentalID);
                if (CarID > 0) {
                    CarDB.carAvailability(CarID);
                }

            } else {
                // Reject booking
                UpdateQuery(RentalID, "accept", BookingAcceptQuery);
            }

        } else {
            cout << "The Rental ID is not identified" << endl;
        }

        // Finalize the rental check statement
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error preparing rental check statement: " << sqlite3_errmsg(db) << endl;
    }
}

//Update Book Status
void SQLiteDBCarRental::UpdateQuery(const int rentalid, const char* Status, const char* Query) {

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, Query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, rentalid);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            cout << "The booking request has been " << Status << "ed." << endl;
        } else {
            cerr << "Error updating data: " << sqlite3_errmsg(db) << endl;
        }
        sqlite3_finalize(stmt);


    }
    else {
        cerr << "Error preparing statement for updating book status : " << sqlite3_errmsg(db) << endl;
    }
}

int SQLiteDBCarRental::ReceiveCarID(const int rentalid){
    const char* GetCarIDQuery = "SELECT CarID FROM CarRental WHERE RentalID = ?;";

    int CarID = 0;

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, GetCarIDQuery, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, rentalid);
        if (sqlite3_step(stmt) == SQLITE_ROW) {

            CarID = sqlite3_column_int(stmt, 0);

        }
        sqlite3_finalize(stmt);
    }
    else{
        cerr << "Error preparing statement for getting the car id : " << sqlite3_errmsg(db) << endl;
    }
    return CarID;

}
void SQLiteDBCarRental::deletebook(const int id){
    const char* caridcheck = "SELECT * FROM CarRental WHERE RentalID = ?;";
    sqlite3_stmt* stmtCheck;
        if (sqlite3_open("CarRental.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, caridcheck, -1, &stmtCheck, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmtCheck, 1, id);
        if (sqlite3_step(stmtCheck) != SQLITE_ROW){
            cout<<"The Rental ID is not identified"<<endl;
        }
        else{

            sqlite3_stmt* stmtDelete;
            const char* deleteDataSQL = "DELETE FROM CarRental WHERE RentalID = ?;";

            if (sqlite3_prepare_v2(db, deleteDataSQL, -1, &stmtDelete, nullptr) == SQLITE_OK) {
                sqlite3_bind_int(stmtDelete, 1, id);

                if (sqlite3_step(stmtDelete) != SQLITE_DONE) {
                    std::cerr << "Error deleting data: " << sqlite3_errmsg(db) <<endl;
                }
                else {

                    cout << "The Rental record is successfully deleted" << endl;
                }
                sqlite3_finalize(stmtDelete);
            }
        }
        sqlite3_finalize(stmtCheck);
    }
    else{
        cerr << "Error preparing statement for deleting booking: " << sqlite3_errmsg(db) << endl;
    }

}

 int SQLiteDBCarRental::callbackPrintData(void *, int argc, char** argv, char** ColNames) {
    for (int i = 0; i < argc; ++i) {
        cout <<ColNames[i]<<": "<<argv[i] << " ";
    }
    cout << endl;

    return 0;
}
