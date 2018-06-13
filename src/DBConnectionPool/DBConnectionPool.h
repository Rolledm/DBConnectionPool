#ifndef DBCONNECTIONPOOL_H
#define DBCONNECTIONPOOL_H

#include "../ConnectionManager/Connection/Connection.h"
#include "../Logger/Logger.h"
#include "Initialisable/Initialisable.h"
#include "Initialisable/InitByXML.h"
#include "QueueManager/QueueManager.h"
#include "../ConnectionManager/Settings/Settings.h"

#include <vector>
#include <mutex>
#include <thread>
#include <fstream>

class DBConnectionPool {
public:
    DBConnectionPool(int argc, char** argv);
    ~DBConnectionPool();
    void handleArguments(int argc, char** argv);
    void startWork();
    void endWork();
//private:
    Initialisable* init;
    QueueManager queueManager;
    std::string outFile;
    std::string sev_lvl;
};

#endif