#include "IniParser.h"

using namespace std;
int main()
{
    char file_name[90], section[90], parameter[90];
    cout << "Name of INI file: ";
    cin >> file_name;
    cout << endl << "Name of section: ";
    cin >> section;
    cout << endl << "Name of parameter: ";
    cin >> parameter;
    int k;
    IniParser iniParser;

    try {
        iniParser.Initialize(file_name);
        if(iniParser.IsHaveSection(section)){
            cout << section <<" is here" << endl;
        }
        if(iniParser.IsHaveParam(section, parameter)) {
            k = iniParser.GetValue<int>(section, parameter);
            cout << k << endl;
        }
    }
    catch (exception &e){
        e.what();
    }

    return 0;
}