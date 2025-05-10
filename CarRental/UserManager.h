//
// Created by MacBook Air on 24/01/24.
//

#ifndef CARRENTAL_USERMANAGER_H
#define CARRENTAL_USERMANAGER_H
#include "SQLiteDBUser.h"
class UserManager{
public :
    void Register(SQLiteDBUser UserDB);
    int Userlogin(SQLiteDBUser UserDB);
};

#endif //CARRENTAL_USERMANAGER_H
