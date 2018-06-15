#ifndef CONNECTION_H
#define CONNECTION_H

#include <ctime>
#include <mysql.h>

#include "../Settings/Settings.h"
#include "../../Logger/Logger.h"

class Connection {

public:
    Connection(Settings settings);
    ~Connection();

    void init(Settings settings);


    MYSQL mysql;
    MYSQL* connection;
    bool isBusy;
    std::time_t time;

};

#endif