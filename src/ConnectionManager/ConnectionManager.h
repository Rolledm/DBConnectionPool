#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <vector>
#include <mutex>

#include "Settings/Settings.h"
#include "Connection/Connection.h"

class ConnectionManager {
public:
    void init(std::string outFile);
    void newConnection();
    void removeConnection(std::shared_ptr<Connection> connection);
    std::shared_ptr<Connection> findConnection();
    void start(std::string command, std::shared_ptr<Connection> connection);
    size_t numOfFreeConnections();
    void endWork();

    int getNumOfOpenedConnections();
    Settings& getSettings();

    void watchForUnusedConnections();

private:
    Settings settings;
    std::string outFile;
    std::atomic<int> numOfOpenedConnections;
    std::mutex _lock;
    std::vector <std::shared_ptr<Connection>> connections;
};

#endif