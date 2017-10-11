//
// Created by DNS on 18.09.2017.
//
#ifndef LABA1_ALLEXCEPTIONS_H
#define LABA1_ALLEXCEPTIONS_H

#include <exception>
#include <iostream>

using namespace std;

class allExceptions: public exception {
public:
    explicit allExceptions(const char *message){
        cout << message << endl;
    }
};


#endif //LABA1_ALLEXCEPTIONS_H
