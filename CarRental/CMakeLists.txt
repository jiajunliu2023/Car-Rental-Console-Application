cmake_minimum_required(VERSION 3.27)
project(CarRental)

set(CMAKE_CXX_STANDARD 17)

add_executable(CarRental main.cpp
sqlite3.c
sqlite3.h
sqlite3ext.h
        User.cpp
        User.h
        Webpage.h
        Car.h
        Car.cpp
        UserManager.h
        UserManager.cpp
        SQLiteDBUser.h
        SQLiteDBUser.cpp
        CarManager.h
        CarManager.cpp
        SQLiteDBCar.h
        SQLiteDBCar.cpp
        SQLiteDBCarRental.cpp
        SQLiteDBCarRental.h
        Car.cpp
)
