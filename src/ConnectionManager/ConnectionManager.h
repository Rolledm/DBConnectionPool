#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <vector>
#include <mutex>

#include "Settings/Settings.h"
#include "Connection/Connection.h"

class ConnectionManager {
public:
    void init();
    void newConnection();
    void removeConnection(Connection* connection);
    Connection* findConnection();
    void start(std::string command, Connection* connection);
    size_t numOfFreeConnections();

    void watchForUnusedConnections();


public://private:
    std::mutex _lock;
    Settings settings;
    std::vector <Connection*> connections;
    std::string outFile;
};

#endif