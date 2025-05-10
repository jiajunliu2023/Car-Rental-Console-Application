//
// Created by MacBook Air on 25/12/23.
//

#ifndef CARRENTAL_USER_H
#define CARRENTAL_USER_H
#include <iostream>
#include <string>
using namespace std;

class User {

    private:
        string FirstName;
        string LastName;
        string UserName;
        string Password;
        int IsCustomer;
    public:
        User(string firstName, string lastName, string userName, string password, int iscustomer) {
            FirstName = firstName;
            LastName = lastName;
            UserName = userName;
            Password = password;
            IsCustomer = iscustomer;
        }
        string getFirstName() const;
        string getLastName() const ;
        string getUserName() const;
        string getPassword() const;
        int getIsCustomer() const;

    };



#endif //CARRENTAL_USER_H
