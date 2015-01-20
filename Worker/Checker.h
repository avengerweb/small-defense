#ifndef AP_CHECKER_H
#define AP_CHECKER_H

#include <string>
#include <iostream>
#include <map>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/algorithm/string.hpp>
#include "System.h"
#include "Ip.h"

using namespace std;

// netstat -ntu | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -n
class Checker {

public:
    void checkIpList();
    void flushList();
    bool IsIp(string ip);
    bool BanIp(string ip, int8_t type);
    bool UnbanIp(string ip, int8_t type);
    bool _inProcess;

private:
    const char* command = "netstat -ntu | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -n";
    map<string, Ip> ip_list;
    int _banTime = 10; // minutes
    int _maxPacketCount = 0; // max packet count for not give a ban

};

#endif