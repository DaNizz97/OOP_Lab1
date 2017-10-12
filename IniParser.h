//
// Created by DNS on 17.09.2017.
//

#ifndef LABA1_INIPARSER_H
#define LABA1_INIPARSER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "exc_io.h"
#include "exc_ini_not_initied.h"
#include "exc_ini_not_found.h"
#include "exc_wrong_type.h"
class IniParser {
private:
    map<string, map<string, string>> dataStore;

public:

    IniParser() = default;

    ~IniParser();

    void Initialize(const char *fileName) throw(exc_io);

    bool IsHaveSection(const char *section_name) const throw(exc_ini_not_initied);

    bool
    IsHaveParam(const char *section_name, const char *param_name) const throw(exc_ini_not_found, exc_ini_not_initied);

    template<class T>
    T GetValue(const char *section_name,
               const char *param_name) const throw(exc_ini_not_found, exc_ini_not_initied, exc_wrong_type) {
        if (dataStore.empty()) {
            throw exc_ini_not_initied("EXCEPTION: \"File is not initialized\"");
        }
        bool check = false;
        map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>::const_iterator it;
        for (it = dataStore.at(section_name).begin(); it != dataStore.at(section_name).end(); ++it) {
            if (param_name == it->first) {
                check = true;
            }
        }
        if (!check) {
            throw exc_ini_not_found("EXCEPTION: \"Parameter not found!\"");
        }
        string str = dataStore.at(section_name).at(param_name);
        istringstream parse(str);
        T paramValue;
        parse >> paramValue;
        /*
        if(parse.bad())
            throw exc_wrong_type("EXCEPTION: \"Error variable type\"");
        */
        return paramValue;
    }
private:
    std::string eraseComments(std::string &lineOfIniFile) const;
};

#endif //LABA1_INIPARSER_H
