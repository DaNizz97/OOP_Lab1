//
// Created by DNS on 17.09.2017.
//
#include "IniParser.h"

using namespace std;

void IniParser::Initialize(const char *filename_cstr)  throw(exc_io) {
    ifstream file(filename_cstr);
    if (!file.good()) {
        throw exc_io("EXCEPTION: \"File not found!\"");
    }
    string lineOfIniFile, sectionName, parameterName, parameterValue;
    getline(file, lineOfIniFile);
    int equalPosition, splittingPosition;
    while (!file.eof()) {
        if (isLineComment(lineOfIniFile) || lineOfIniFile.empty()) {
            getline(file, lineOfIniFile);
            continue;
        }
        if (lineOfIniFile[0] == '[') {
            sectionName = lineOfIniFile;
            getline(file, lineOfIniFile);
            while (lineOfIniFile[0] != '[' && !file.eof()) {
                if (isLineComment(lineOfIniFile) || lineOfIniFile.empty()) {
                    getline(file, lineOfIniFile);
                    continue;
                }
                if (lineOfIniFile[0] != ';') {
                    lineOfIniFile.erase(remove(lineOfIniFile.begin(), lineOfIniFile.end(), ' '), lineOfIniFile.end());
                    equalPosition = (int) lineOfIniFile.find('=');
                    parameterName = lineOfIniFile.substr(0, (unsigned long long int) equalPosition);
                    parameterValue = lineOfIniFile.substr((unsigned long long int) equalPosition + 1);
                    splittingPosition = (int) parameterValue.find(';');
                    if (splittingPosition != -1) {
                        parameterValue = parameterValue.substr(0, (unsigned long long int) (splittingPosition));
                    }

                    dataStore[sectionName][parameterName] = parameterValue;
                }
                getline(file, lineOfIniFile);
            }
        }
    }
    equalPosition = (int) lineOfIniFile.find('=');
    parameterName = lineOfIniFile.substr(0, (unsigned long long int) equalPosition - 1);
    parameterValue = lineOfIniFile.substr((unsigned long long int) equalPosition + 2);
    dataStore[sectionName][parameterName] = parameterValue;
}

bool IniParser::IsHaveSection(const char *section_name) const throw(exc_ini_not_initied) {
    if (dataStore.empty()) {
        throw exc_ini_not_initied("EXCEPTION: \"File is not initialized\"");
    }
    map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>>::const_iterator it;
    bool check = false;
    for (it = dataStore.begin(); it != dataStore.end(); ++it) {
        if (section_name == it->first) {
            check = true;
        }
    }
    return check;
}

bool IniParser::IsHaveParam(const char *section_name,
                            const char *param_name) const throw(exc_ini_not_initied, exc_ini_not_found) {
    if (dataStore.empty()) {
        throw exc_ini_not_initied("EXCEPTION: \"File is not initialized\"");
    }
    bool checkParamExc = false;
    map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>>::const_iterator it;
    for (it = dataStore.at(section_name).begin(); it != dataStore.at(section_name).end(); ++it) {
        if (param_name == it->first) {
            checkParamExc = true;
        }
    }
    if (!checkParamExc) {
        throw exc_ini_not_found("EXCEPTION: \"Parameter not found!\"");
    }
    return checkParamExc;
}


bool IniParser::isLineComment(std::string &lineOfIniFile) const{
    return lineOfIniFile[0] == ';';
}


IniParser::~IniParser() = default;

