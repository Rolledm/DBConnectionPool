#ifndef CONNECTION_H
#define CONNECTION_H

#include <ctime>
#include <memory>
#include <mysql.h>
#include <atomic>

#include "Settings.h"
#include "../../libLogger/src/Logger.h"

class Connection {

public:
    Connection();
    ~Connection();

    void init();


    MYSQL mysql;
    MYSQL* connection;
    std::atomic<bool> isBusy;
    std::time_t time;

};

#endif