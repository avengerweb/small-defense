#ifndef AP_MASTER_H
#define AP_MASTER_H

#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono/chrono.hpp>
#include <memory>
#include <vector>
#include "Checker.h"


class Master {
public:
    bool IsWork() { return _status; }
    bool loadConfig() { return true; }

    static Master* instance();

    void start();
    void Stop();
    Checker* getChecker();
    void doCommand(std::string command);
    boost::chrono::high_resolution_clock::time_point m_lastCheck;
    bool m_checkerLoop;
    bool m_commandLoop;

private:
    static boost::atomic<Master *> instance_;
    static boost::mutex instantiation_mutex;
    bool _status;
    boost::thread _daemonThread;
    boost::thread _commandThread;
    Checker* _checker;
};

#endif