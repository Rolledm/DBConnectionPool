#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <vector>
#include <mutex>

#include "Settings.h"
#include "Connection.h"

class ConnectionManager {
public:
    ConnectionManager() {numOfOpenedConnections = 0;}
    ~ConnectionManager();
    void startWork();

    void newConnection();
    void removeConnection(std::shared_ptr<Connection> connection);
    std::shared_ptr<Connection> findConnection();

    void handleQuery(std::string command);
    void startQuery(std::string command, std::shared_ptr<Connection> connection);
    
    int numOfFreeConnections();
    int getNumOfOpenedConnections();

    void watchForUnusedConnections();

private:
    std::atomic<int> numOfOpenedConnections;
    std::mutex _lock;
    std::vector <std::shared_ptr<Connection>> connections;
};

#endif