#include "Checker.h"
#include "Master.h"

void Checker::checkIpList() {
    _inProcess = true;
    string result = System::excuteCommand(string(this->command));
    vector<string> ip_addresses = System::splitString(result, "\n"); // Get rows
    vector<string> packet_load;
    if (!ip_addresses.empty())
        for (auto ip = begin(ip_addresses); ip != end(ip_addresses); ++ip)
        {
            boost::algorithm::trim(*ip);
            packet_load = System::splitString(*ip, " ");
            if (IsIp(packet_load[1]))
                // Right IP, then ban or do nothing
                if (atoi(packet_load[0].c_str()) > this->_maxPacketCount)
                    BanIp(packet_load[1], 0);
        }

    _inProcess = false;
}

bool Checker::BanIp(string ip, int8_t type) {
    map<string, Ip>::iterator it = ip_list.find(ip);
    if (it == ip_list.end() || (!it->second.isBanned && !it->second.isInWaitList)) {
        ip_list[ip].isBanned = true;
        ip_list[ip].banTime = time(0);
        ip_list[ip].unbanTime = time(0) + this->_banTime * 60;
        ip_list[ip].type = type;

        cout << ip_list[ip].banTime << " " << ip_list[ip].unbanTime << " " << endl;
        System::excuteCommand("ipset -A ipban " +ip);
        cout << "BAN IP: " << ip;
        cout << endl;
        return true;
    }

    if (type == 1) {
        cout << "IP: " << ip << " already banned";
        cout << endl;
    }
    return false;
}

bool Checker::UnbanIp(string ip, int8_t type) {
    map<string, Ip>::iterator it = ip_list.find(ip);
    if (it != ip_list.end()) {
        it->second.isInWaitList = true;
        System::excuteCommand("ipset -D ipban " + ip);

        if (type == 1)
            cout << "IP: " << ip << " unbanned!";

        return true;
    }
    else {
        cout << "IP: " << ip << " not yet banned";
        cout << endl;
        return false;
    }
}

bool Checker::IsIp(string ip) {
    boost::system::error_code ec;
    boost::asio::ip::address::from_string( ip, ec );
//    if ( ec )
//        cerr << "Not valid ip: " << ip << " Code: " << ec.message() << endl;

    return !ec;
}

void Checker::flushList() {
    cout << "";
    if (ip_list.empty())
        return;

    cout << ip_list.size() << " rows be clean!";
    cout << endl;

    ip_list.clear();
    System::excuteCommand("ipset -F ipban");

//    for (auto ip : ip_list)
//    {
//        if (ip.second.isBanned)
//            UnbanIp(ip.first, 0);
//    }
}