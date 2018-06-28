#ifndef DBCONNECTIONPOOL_H
#define DBCONNECTIONPOOL_H

#include "ConnectionManager.h"
#include <list>

class DBConnectionPool {
public:
    ~DBConnectionPool();

    void startWork();
    void push(std::string task);
    std::string pop();
    void initConnections();
    
    void endWork();

private:
    std::list<std::string> queue; 
    std::mutex _lock;
    ConnectionManager connectionManager;
};


#endif