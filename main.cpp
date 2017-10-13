#include "IniParser.h"

using namespace std;
int main()
{
    int k;
    IniParser iniParser;
    char file_name[90], section[90], parameter[90];
    cout << "Name of INI file: ";
    cin >> file_name;
    try {
        iniParser.initialize(file_name);
    }
    catch (exception &e){
        e.what();
    }
    cout << endl << "Name of section: ";
    cin >> section;
    try {
        if(iniParser.isHaveSection(section)){
            cout << section <<" is here" << endl;
        }
    }
    catch (exception &e){
        e.what();
    }

    cout << endl << "Name of parameter: ";
    cin >> parameter;
    try {
        if(iniParser.isHaveParam(section, parameter)) {
            k = iniParser.getValue<int>(section, parameter);
            cout << k << endl;
        }
    }
    catch (exception &e){
        e.what();
    }

    return 0;
}