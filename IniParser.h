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

class IniParser {
private:
    std::map<std::string, std::map<std::string, std::string>> dataStore;

    bool init = false;

    void eraseComments(std::string &lineOfIniFile) const;

    bool isLineSection(const std::string &lineOfIniFile) const;

    void eraseBracketsFromSection(std::string &lineOfIniFile) const;

    void assignmentValue(std::string &lineOfIniFile, const std::string &sectionName, std::string &parameterName,
                         std::string &parameterValue);

public:

    IniParser() = default;

    ~IniParser();

    void initialize(const char *fileName) throw(exc_io);

    bool isHaveSection(const std::string &section_name) const throw(exc_ini_not_found, exc_ini_not_initialized);

    bool
    isHaveParam(const std::string &section_name,
                const std::string &param_name) const throw(exc_ini_not_found, exc_ini_not_initialized);

    template<typename T>
    T getValue(const std::string &section_name,
               const std::string &param_name) const throw(allExceptions);
};

#endif //LABA1_INIPARSER_H
