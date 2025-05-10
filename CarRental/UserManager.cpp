//
// Created by MacBook Air on 24/01/24.
//
#include "UserManager.h"
void UserManager::Register(SQLiteDBUser UserDB) {
    string firstname,lastname, username, password;
    int userType;
    int Iscustomer;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Register"<<endl;
    cout<<"*******************************"<<endl;
    cout << "Please enter the first name: ";
    cin >> firstname;
    cout << "Please enter the second name: ";
    cin >> lastname;
    cout << "Please enter the username: ";
    cin >> username;
    cout << "Please enter the password: ";
    cin >> password;
    cout<<"*******************************"<<endl;

    cout << "Register as customer or admin (1 for customer, 0 for admin): ";
    cin >> userType;
    if (userType == 1) {
        Iscustomer = 1;
    } else {
        Iscustomer = 0;
    }
    User user(firstname, lastname, username, password, Iscustomer);
    UserDB.addUser(user);
}
int UserManager::Userlogin(SQLiteDBUser UserDB){

    string username, password;
    cout<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Login"<<endl;
    cout<<"*******************************"<<endl;
    cout<<"Please enter you username: ";
    cin >> username;
    cout<<"Please enter your password: ";
    cin >> password;
    cout<<"*******************************"<<endl;
    return UserDB.UserLogin(username, password);

}
