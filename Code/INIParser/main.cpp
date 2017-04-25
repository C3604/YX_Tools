#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>
#include "INIParser.h"
using namespace std;


int main()
{
    INIParser ini_parser;
    ini_parser.ReadINI("conf.ini");
    cout << ini_parser.GetValue("default", "server_port") << endl;
    ini_parser.Clear();
    cout << ini_parser.GetSize() << endl;

    ini_parser.SetValue("class1","name1","Tom");
    ini_parser.SetValue("class2","name2","Lucy");
    ini_parser.WriteINI("test.ini");
    return 0;
}
