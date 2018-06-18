#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include "../../ConnectionManager/ConnectionManager.h"
#include <list>

class QueueManager {
public:
    void startWork();
    void push(std::string task);
    std::string pop();
    
    void initSettings(Initialisable* init);
    void initOutFile(std::string);
    void endWork();

private:
    std::list<std::string> queue; 
    std::mutex _lock;
    ConnectionManager connectionManager;
};


#endif