//
// Created by DNS on 17.09.2017.
//

#ifndef LABA1_IOEXCEPTION_H
#define LABA1_IOEXCEPTION_H
#include "allExceptions.h"
using namespace std;

class exc_io: public allExceptions {
public:
    explicit exc_io(const char *message) : allExceptions(message) {}
};


#endif //LABA1_IOEXCEPTION_H
