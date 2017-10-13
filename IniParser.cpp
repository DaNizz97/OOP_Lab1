//
// Created by DNS on 17.09.2017.
//
#include <algorithm>
#include "IniParser.h"

using namespace std;
typedef unsigned long long int ulli;

void IniParser::initialize(const char *filename_cstr)  throw(exc_io) {
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
    file.close();
    init = true;
}

void IniParser::assignmentValue(string &lineOfIniFile, const string &sectionName, string &parameterName, string &parameterValue) {
    lineOfIniFile.erase(remove(lineOfIniFile.begin(), lineOfIniFile.end(), ' '), lineOfIniFile.end());
    ulli equalPosition = lineOfIniFile.find('=');
    parameterName = lineOfIniFile.substr(0, equalPosition);
    parameterValue = lineOfIniFile.substr(equalPosition + 1);
    dataStore[sectionName][parameterName] = parameterValue;
}

bool IniParser::isHaveSection(const std::string &section_name) const throw(exc_ini_not_found, exc_ini_not_initialized) {
    if (!init) {
        throw exc_ini_not_initialized("EXCEPTION: \"File is not initialized!\"");
    }
    bool check = false;
    for (auto it : dataStore) {
        if (section_name == it.first) {
            check = true;
        }
    }
    if(!check){
        throw exc_ini_not_found("EXCEPTION: \"Section \"" + section_name + "\" not found!\"");
    }
    return check;
}

bool IniParser::isHaveParam(const std::string &section_name,
                            const std::string &param_name) const throw(exc_ini_not_initialized, exc_ini_not_found) {
    if (!init) {
        throw exc_ini_not_initialized("EXCEPTION: \"File is not initialized!\"");
    }
    bool checkParamExc = false;
    for (auto it : dataStore.at(section_name)) {
        if (param_name == it.first) {
            checkParamExc = true;
        }
    }
    if (!checkParamExc) {
        throw exc_ini_not_found("EXCEPTION: \"Parameter \"" + param_name + "\" not found!\"");
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

template<>
int IniParser::getValue<int>(const std::string &section_name, const std::string &param_name) const throw(allExceptions){
    if(isHaveParam(section_name, param_name) && isHaveSection(section_name)){
        return stoi(dataStore.at(section_name).at(param_name));
    }
}

template<>
double IniParser::getValue<double>(const std::string &section_name, const std::string &param_name) const throw(allExceptions){
    if(isHaveParam(section_name, param_name) && isHaveSection(section_name)){
        return stod(dataStore.at(section_name).at(param_name));
    }
}

template<>
string IniParser::getValue<string>(const std::string &section_name, const std::string &param_name) const throw(allExceptions){
    if(isHaveParam(section_name, param_name) && isHaveSection(section_name)){
        return dataStore.at(section_name).at(param_name);
    }
}
IniParser::~IniParser() = default;

