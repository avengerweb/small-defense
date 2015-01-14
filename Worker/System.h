#ifndef AP_SYSTEM_H
#define AP_SYSTEM_H

#include <string>
#include <iostream>
#include <boost/log/trivial.hpp>

using namespace std;

class System {
public:
    static string excuteCommand(string cmd);
};

#endif