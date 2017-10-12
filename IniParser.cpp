//
// Created by DNS on 17.09.2017.
//
#include "IniParser.h"

using namespace std;
typedef unsigned long long int ulli;

void IniParser::Initialize(const char *filename_cstr)  throw(exc_io) {
    ifstream file(filename_cstr);
    if (!file.good()) {
        throw exc_io("EXCEPTION: \"File not found!\"");
    }
    string lineOfIniFile, sectionName, parameterName, parameterValue;
    while ( !file.eof() && getline(file, lineOfIniFile) ) {
        eraseComments(lineOfIniFile);
        if (lineOfIniFile.empty()) {
            continue;
        }
        if ( isLineSection(lineOfIniFile) ) {
            eraseBracketsFromSection(lineOfIniFile);
            sectionName = lineOfIniFile;
        }
        assignmentValue(lineOfIniFile, sectionName, parameterName, parameterValue);
        while ( !isLineSection(lineOfIniFile) && !file.eof() && getline(file, lineOfIniFile) ) {
            eraseComments(lineOfIniFile);
            if (isLineSection(lineOfIniFile)) {
                eraseBracketsFromSection(lineOfIniFile);
                sectionName = lineOfIniFile;
                break;
            }
            if (lineOfIniFile.empty()) {
                continue;
            }
            assignmentValue(lineOfIniFile, sectionName, parameterName, parameterValue);
        }
    }

}

void IniParser::assignmentValue(string &lineOfIniFile, const string &sectionName, string &parameterName, string &parameterValue) {
    lineOfIniFile.erase(remove(lineOfIniFile.begin(), lineOfIniFile.end(), ' '), lineOfIniFile.end());
    ulli equalPosition = lineOfIniFile.find('=');
    parameterName = lineOfIniFile.substr(0, equalPosition);
    parameterValue = lineOfIniFile.substr(equalPosition + 1);
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

void IniParser::eraseComments(std::string &lineOfIniFile) const {
    size_t position = lineOfIniFile.find(';');
    if (position != -1) {
        lineOfIniFile = lineOfIniFile.substr(0, position);
    }
}

bool IniParser::isLineSection(const std::string &lineOfIniFile) const {
    return lineOfIniFile[0] == '[';
}

void IniParser::eraseBracketsFromSection(std::string &lineOfIniFile) const {
    ulli firstBracket = lineOfIniFile.find('[');
    ulli secondBracket = lineOfIniFile.find(']');
    lineOfIniFile = lineOfIniFile.substr(firstBracket + 1, secondBracket - 1);
}


IniParser::~IniParser() = default;

