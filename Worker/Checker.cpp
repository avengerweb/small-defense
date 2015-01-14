#include "Checker.h"

void Checker::checkIpList() {
    string result = System::excuteCommand(string(this->command));
    BOOST_LOG_TRIVIAL(info) << result;
}