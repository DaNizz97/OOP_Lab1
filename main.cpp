#include "IniParser.h"

using namespace std;

int main() {
    try {
        IniParser iniParser;
        iniParser.initialize("9.ini");
        cout << iniParser.getValue<string>("DEBUG", "DBAddressIP") << endl;
    }
    catch (exception &e) {
        e.what();
    }

    return 0;
}