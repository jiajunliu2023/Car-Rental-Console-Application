//
// Created by MacBook Air on 24/01/24.
//
#include "SQLiteDBUser.h"


SQLiteDBUser& SQLiteDBUser::getInstance(const char* dbName) {
    static SQLiteDBUser instance(dbName);

    return instance;
}
SQLiteDBUser::SQLiteDBUser(const char *dbName) {
    int rc = sqlite3_open(dbName, &db);

    if (rc != SQLITE_OK) {
        cerr << "Cannot Open or Create the Database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    createTable();
}


void SQLiteDBUser::addUser(const User& user){
    string username = user.getUserName();
    //Check whether the username is used or not
    if (CheckUserName(username)){
        cout<<"The Username has already existed, please choose another"<<endl;
    }
    else {
        //Add all the detail about the account into the User database table
        const char* insertDataSQL = "INSERT INTO User (FirstName, LastName, UserName, Password, IsCustomer) VALUES (?, ?, ?, ?, ?);";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, insertDataSQL, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, user.getFirstName().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, user.getLastName().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, user.getUserName().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, user.getPassword().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 5, user.getIsCustomer());


            if (sqlite3_step(stmt) != SQLITE_DONE) {
                cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
            }
            cout <<"Successfully Register"<<endl;

           sqlite3_finalize(stmt);
        }
    }
}
bool SQLiteDBUser::CheckUserName(const string username) {

    const char* searchQuery = "SELECT * FROM User WHERE UserName = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_open("User.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }
    if (sqlite3_prepare_v2(db, searchQuery, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);


        if (result == SQLITE_ROW){

            return true;
        } else if (result == SQLITE_DONE) {
            return false;  // Username does not exist
        } else {
            cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
            return false;
        }

    }else{
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }


}
//User login
int SQLiteDBUser::UserLogin(const string username, const string password) {
    const char* loginQuery = "SELECT * FROM User WHERE UserName = ? AND Password = ?;";
    const char* checkRoleQuery = "SELECT UserID FROM User WHERE UserName = ? AND Password = ? AND IsCustomer = 1;";
    sqlite3_stmt* loginstmt = nullptr;
    sqlite3_stmt* rolestmt = nullptr;
    if (sqlite3_open("User.db", &db) != SQLITE_OK) {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        exit(EXIT_FAILURE);
    }


    // Prepare the login statement
    if (sqlite3_prepare_v2(db, loginQuery, -1, &loginstmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(loginstmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(loginstmt, 2, password.c_str(), -1, SQLITE_STATIC);

        // Check if a matching username and password are found
        if (sqlite3_step(loginstmt) == SQLITE_ROW) {
            int userid = -1;


            sqlite3_finalize(loginstmt);

            // Prepare the role check statement
            if (sqlite3_prepare_v2(db, checkRoleQuery, -1, &rolestmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(rolestmt, 1, username.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(rolestmt, 2, password.c_str(), -1, SQLITE_STATIC);


                if (sqlite3_step(rolestmt) == SQLITE_ROW) {
                    userid = sqlite3_column_int(rolestmt, 0);
                }
                else{
                    return 0;
                }
            } else {
                cerr << "Error preparing Role Check statement: " << sqlite3_errmsg(db) << endl;
            }


            sqlite3_finalize(rolestmt);

            return userid;
        } else {
            // Finalize the login statement before returning
            sqlite3_finalize(loginstmt);
            return -1;
        }
    } else {
        cerr << "Error preparing login statement: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
}

SQLiteDBUser::~SQLiteDBUser() {
    sqlite3_close(db);
}

void SQLiteDBUser::createTable(){
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS User (UserID INTEGER PRIMARY KEY AUTOINCREMENT, FirstName TEXT NOT NULL, LastName TEXT NOT NULL, UserName TEXT NOT NULL, Password TEXT NOT NULL, IsCustomer BOOLEAN NOT NULL);";
    char *errMsg = nullptr;

    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Cannot create table: " << errMsg << endl;
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}




