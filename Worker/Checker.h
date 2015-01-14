#ifndef AP_CHECKER_H
#define AP_CHECKER_H

#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <boost/process/process.hpp>
#include <boost/process/operations.hpp>
#include "System.h"

// netstat -ntu | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -n
class Checker {

public:
    void checkIpList();

private:
    const char* command = "netstat -ntu | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -n";
};

#endif