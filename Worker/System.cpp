#include "System.h"

string System::excuteCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }

    return data;
}

vector<string> System::splitString(string std, string delimiter) {
    std::vector<std::string> strs;
    boost::split(strs, std, boost::is_any_of(delimiter));

    return strs;
}