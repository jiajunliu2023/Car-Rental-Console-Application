//
// Created by MacBook Air on 24/01/24.
//

#ifndef CARRENTAL_SQLITEDBUSER_H
#define CARRENTAL_SQLITEDBUSER_H
#include <iostream>
#include <sqlite3.h>
#include "User.h"
//Manipulate the User Database
class SQLiteDBUser {
public:
    static SQLiteDBUser& getInstance(const char* dbName);
    // User Register
    void addUser(const User& user);
    // Check whether the username exists or not
    bool CheckUserName(const string username);
    //User login
    int UserLogin(const string username, const string password);

    ~SQLiteDBUser();


private:

   sqlite3 *db;


    SQLiteDBUser(const char *dbName);

    void createTable();
};
#endif //CARRENTAL_SQLITEDBUSER_H
