//
// Created by DNS on 18.09.2017.
//

#ifndef LABA1_EXC_CFG_NOT_INITIED_H
#define LABA1_EXC_CFG_NOT_INITIED_H
#include "allExceptions.h"

class exc_ini_not_initied: public allExceptions {
public:
    explicit exc_ini_not_initied(const char *message) : allExceptions(message) {}
};



#endif //LABA1_EXC_CFG_NOT_INITIED_H
