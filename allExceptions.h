//
// Created by DNS on 18.09.2017.
//
#ifndef LABA1_ALLEXCEPTIONS_H
#define LABA1_ALLEXCEPTIONS_H

#include <exception>
#include <iostream>

class allExceptions: public std::exception {
public:
    explicit allExceptions(const char *message){
        std::cout << message << std::endl;
    }
};


#endif //LABA1_ALLEXCEPTIONS_H
