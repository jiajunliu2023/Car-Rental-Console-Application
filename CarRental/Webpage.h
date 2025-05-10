//
// Created by MacBook Air on 27/12/23.
//

#ifndef CARRENTAL_WEBPAGE_H
#define CARRENTAL_WEBPAGE_H
#include <iostream>
using namespace std;
int num;
int Homepage(){
    cout<<endl;
    cout<<"**************************"<<endl;
    cout <<"Welcome to the Car Rental"<<endl;
    cout<<"**************************"<<endl;
    cout <<"1. Register"<<endl;
    cout <<"2. Login"<<endl;
    cout <<"3. Leave"<<endl;
    cout<<"**************************"<<endl;
    cout <<"Please enter the specific number: ";
    cin >> num;
    return num;
}

int  CustomerMenu(){
    cout<<endl;
    cout<<"**************************"<<endl;
    cout<<"Customer Menu: "<<endl;
    cout<<"**************************"<<endl;
    cout<<"1. Display Available Cars"<<endl;
    cout<<"2. Search Car"<<endl;
    cout<<"3. Book rental "<<endl;
    cout<<"4. Go Back to home page"<<endl;
    cout<<"**************************"<<endl;
    cout <<"Please enter the specific number: ";
    cin >> num;
    return num;
}

int AdminMenu(){
    cout<<endl;
    cout<<"**************************"<<endl;
    cout<<"Admin Menu: "<<endl;
    cout<<"**************************"<<endl;
    cout<<"1. Display All Cars"<<endl;
    cout<<"2. Add Car"<<endl;
    cout<<"3. Update Car"<<endl;
    cout<<"4. Delete Car"<<endl;
    cout<<"5. Show the booking request"<<endl;
    cout<<"6. Process the booking"<<endl;
    cout<<"7. Delete car booking record"<<endl;
    cout<<"8. Go back to the home page"<<endl;
    cout<<"**************************"<<endl;
    cout <<"Please enter the specific number: ";
    cin >> num;
    return num;
}

#endif //CARRENTAL_WEBPAGE_H
