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
#include "exc_ini_not_initialized.h"
#include "exc_ini_not_found.h"
#include "exc_wrong_type.h"
class IniParser {
private:
    std::map<std::string,std::map<std::string, std::string>> dataStore;

public:

    IniParser() = default;

    ~IniParser();

    void Initialize(const char *fileName) throw(exc_io);

    bool IsHaveSection(const std::string &section_name) const throw(exc_ini_not_found, exc_ini_not_initialized);

    bool
    IsHaveParam(const std::string &section_name, const std::string &param_name) const throw(exc_ini_not_found, exc_ini_not_initialized);

    template<class T>
    T GetValue(const std::string &section_name,
               const std::string &param_name) const throw(exc_ini_not_found, exc_ini_not_initialized, exc_wrong_type) {
        if (dataStore.empty()) {
            throw exc_ini_not_found("EXCEPTION: \"Parameter \"" + param_name + "\" not found!\"");
        }
        bool check = false;
        for (auto it : dataStore.at(section_name)) {
            if (param_name == it.first) {
                check = true;
            }
        }
        if (!check) {
            throw exc_ini_not_found("EXCEPTION: \"Parameter not found!\"");
        }
        std::string str = dataStore.at(section_name).at(param_name);
        std::istringstream parse(str);
        T paramValue;
        parse >> paramValue;
        /*
        if(parse.bad())
            throw exc_wrong_type("EXCEPTION: \"Error variable type\"");
        */
        return paramValue;
    }
private:

    bool init = false;
    void eraseComments(std::string &lineOfIniFile) const;

    bool isLineSection(const std::string &lineOfIniFile) const;

    void eraseBracketsFromSection(std::string &lineOfIniFile) const;

    void assignmentValue(std::string &lineOfIniFile, const std::string &sectionName, std::string &parametrName, std::string &parametrValue);
};

#endif //LABA1_INIPARSER_H
