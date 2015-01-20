#include "Master.h"

using namespace std;

void daemonThread() {
    Master* m = Master::instance();
    m->pause = false;
    while (m->IsWork())
    {
        try
        {
            if (!m->pause)
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
    Master* m = Master::instance();
    m->_t = true;
    while (m->_t)
    {
        getline(cin, command);
        if (command != "")
            cout << "Command: " << command << endl;
        try
        {
            if (command == "")
                continue;

            m->doCommand(command);
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

void Master::doCommand(std::string command) {
    Master* m = Master::instance();
    std::vector<std::string> parsed_line = System::splitString(command, " ");
    std::vector<std::string> command_args;
    for (auto it : parsed_line) {
        if (it != " " && it != "")
        {
            command_args.push_back(it);
        }
    }

    if (command_args[0] == "ban")
    {
        if (m->getChecker()->IsIp(command_args[1]))
        {
            m->getChecker()->BanIp(command_args[1], 1); // do ban IP
        }
        else
        {
            cout << "not valid ip given";
            cout << endl;
        }
    }

    if (command_args[0] == "unban")
    {
        if (m->getChecker()->IsIp(command_args[1]))
        {
            m->getChecker()->UnbanIp(command_args[1], 1); // do ban IP
        }
        else
        {
            cout << "not valid ip given";
            cout << endl;
        }
    }

    if (command_args[0] == "flush")
    {

            if (m->getChecker()->_inProcess) {
                cout << "wait while main thread done his work 5-10 seconds!";
                cout << endl;
                while (m->getChecker()->_inProcess) {
                    if (!m->getChecker()->_inProcess)
                        break;
                }
            }
            m->pause = true;
            m->getChecker()->flushList(); // do ban IP
            m->pause = false;


    }

    if (command == "stop") {
        m->Stop();
        this->_t = false;
    }
}