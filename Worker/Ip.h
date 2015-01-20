#include <string>

class Ip {
public:
    bool isBanned;
    time_t unbanTime;
    time_t banTime;
    bool isInWaitList;
    // Type 0 - program 1 - user
    int8_t type;
};