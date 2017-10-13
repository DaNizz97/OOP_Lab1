//
// Created by DNS on 19.09.2017.
//

#ifndef LABA1_EXC_WRONG_TYPE_H
#define LABA1_EXC_WRONG_TYPE_H

#include "allExceptions.h"

class exc_wrong_type: public allExceptions {
public:
    explicit exc_wrong_type(const std::string &message) : allExceptions(message) {}
};


#endif //LABA1_EXC_WRONG_TYPE_H
