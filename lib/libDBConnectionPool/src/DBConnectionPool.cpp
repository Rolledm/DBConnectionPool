#include "DBConnectionPool.h"

#include <thread>
#include <chrono>

#include <ctime>

#include "../../libLogger/src/Logger.h"

void DBConnectionPool::startWork() {

    std::thread thread(&ConnectionManager::watchForUnusedConnections, &connectionManager);  // starting killer of unused connections
    
    while (true) {

        if (queue.size() == 0) continue;

        std::shared_ptr<Connection> tempConnection = connectionManager.findConnection();
        if (tempConnection != nullptr) {
            std::string task = pop();
            std::thread thread(&ConnectionManager::start, &connectionManager, task, tempConnection);
            thread.detach();
        } else {
            if (connectionManager.getNumOfOpenedConnections() < Settings::getInstance().getNumOfConnections().second) {
                connectionManager.newConnection();
            }
        }
        
    }
}


void DBConnectionPool::push(std::string task) {
    std::lock_guard<std::mutex> locker(_lock);
    queue.emplace_back(task);
}

std::string DBConnectionPool::pop() {
    std::lock_guard<std::mutex> locker(_lock);

    std::string str = queue.front();
    queue.pop_front();
    return str;
}

void DBConnectionPool::initOutFile(std::string outfile) {
    connectionManager.initOutFile(outfile);
}

void DBConnectionPool::endWork() {
    connectionManager.endWork();
}

DBConnectionPool::~DBConnectionPool() {
    connectionManager.endWork();
}