#ifndef AP_SYSTEM_H
#define AP_SYSTEM_H

#include <string>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

class System {
public:
    static string excuteCommand(string cmd);
    static vector<string> splitString(string std, string delimiter);
};

#endif