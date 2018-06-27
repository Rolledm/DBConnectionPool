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

    void initOutFile(std::string outFile);
    void newConnection();
    void removeConnection(std::shared_ptr<Connection> connection);
    std::shared_ptr<Connection> findConnection();
    void start(std::string command, std::shared_ptr<Connection> connection);
    int numOfFreeConnections();
    void endWork();

    int getNumOfOpenedConnections();

    void watchForUnusedConnections();

private:
    std::string outFile;
    std::atomic<int> numOfOpenedConnections;
    std::mutex _lock;
    std::vector <std::shared_ptr<Connection>> connections;
};

#endif