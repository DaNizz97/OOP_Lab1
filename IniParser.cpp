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
    int equalPosition, splittingPosition;

    while (!file.eof() && getline(file, lineOfIniFile)) {
        lineOfIniFile = eraseComments(lineOfIniFile);
        if (lineOfIniFile.empty()) {
            continue;
        }
        if (lineOfIniFile[0] == '[') {
            sectionName = lineOfIniFile;
            getline(file, lineOfIniFile);
            lineOfIniFile = eraseComments(lineOfIniFile);
        }
        while (lineOfIniFile[0] != '[' && !file.eof() && getline(file, lineOfIniFile)) {
            lineOfIniFile = eraseComments(lineOfIniFile);
            if (lineOfIniFile[0] == '[') {
                sectionName = lineOfIniFile;
                break;
            }
            if (lineOfIniFile.empty()) {
                continue;
            }
            lineOfIniFile.erase(remove(lineOfIniFile.begin(), lineOfIniFile.end(), ' '), lineOfIniFile.end());
            equalPosition = (int) lineOfIniFile.find('=');
            parameterName = lineOfIniFile.substr(0, (unsigned long long int) equalPosition);
            parameterValue = lineOfIniFile.substr((unsigned long long int) equalPosition + 1);
            dataStore[sectionName][parameterName] = parameterValue;
        }
    }

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

std::string IniParser::eraseComments(std::string &lineOfIniFile) const {
    size_t position = lineOfIniFile.find(';');
    if (position != -1) {
        return lineOfIniFile.substr(0, position);
    }
    return lineOfIniFile;
}

IniParser::~IniParser() = default;

