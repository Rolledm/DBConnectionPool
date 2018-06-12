#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include "../../ConnectionManager/ConnectionManager.h"
#include <list>

class QueueManager {
public:
    void startWork();
    void push(std::string task);
    std::string pop();

//private:
    std::list<std::string> queue;   //std::string -> Task
    std::mutex _lock;

public:
    ConnectionManager connectionManager;
};


#endif