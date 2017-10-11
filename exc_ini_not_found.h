//
// Created by DNS on 18.09.2017.
//

#ifndef LABA1_EXC_CFG_NOT_FOUND_H
#define LABA1_EXC_CFG_NOT_FOUND_H
#include "allExceptions.h"
using namespace std;

class exc_ini_not_found: public allExceptions {
public:
    explicit exc_ini_not_found(const char *message) : allExceptions(message) {}

};


#endif //LABA1_EXC_CFG_NOT_FOUND_H
