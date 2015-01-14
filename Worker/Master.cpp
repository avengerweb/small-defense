#include "Master.h"

using namespace std;

void daemonThread() {
    Master* m = Master::instance();
    while (m->IsWork())
    {
        try
        {
            m->getChecker()->checkIpList();
            // Update diff(We need that when have to small count of ip address not need to spam command)
            boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
        }
        catch(boost::thread_interrupted&)
        {
            BOOST_LOG_TRIVIAL(info) << "Stop daemon thread";
            break;
        }
    }
}

void commandThread() {
    string command;
    bool t = true;
    while (t)
    {
        getline(cin, command);
        if (command != "")
            cout << "Command: " << command << endl;
        try
        {
            if (command == "stop") {
                // Stop daemon thread
                Master::instance()->Stop();

                // Stop command thread
                t = false;
            }
        }
        catch(boost::thread_interrupted&)
        {
            cout << "Thread is stopped" << endl;
            break;
        }
    }
}

void Master::Stop() {
    this->_status = false;
    this->_daemonThread.interrupt();
    this->_daemonThread.join();
}

void Master::start() {
    //Initialization checker
    this->_checker = new Checker();
    //Run command thread firslty
    this->_commandThread = boost::thread(&commandThread);
    //Then start daemon
    // Set true for run loop
    this->_status = true;
    // Open thread
    this->_daemonThread = boost::thread(&daemonThread);
    // Join to command thread and work with that
    this->_commandThread.join();
//    commandThread();
}

Checker * Master::getChecker() {
    return this->_checker;
}

boost::mutex Master::instantiation_mutex;
boost::atomic<Master *> Master::instance_(0);

Master* Master::instance() {
    Master * tmp = instance_.load(boost::memory_order_consume);
    if (!tmp) {
        boost::mutex::scoped_lock guard(instantiation_mutex);
        tmp = instance_.load(boost::memory_order_consume);
        if (!tmp) {
            tmp = new Master;
            instance_.store(tmp, boost::memory_order_release);
        }
    }
    return tmp;
}
