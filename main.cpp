#include <iostream>
#include "Master.h"

using namespace std;

int main() {
  //  Master master;// = new Master();
    cout << "Version: 0.0.1 (A)" << endl;
    cout << "AvengerSystem: http://avenger-web.ru" << endl;
    cout << "Going start main thread" << endl;

    // Start master control
    Master* m = Master::instance();
    m->start();

    return 0;
}