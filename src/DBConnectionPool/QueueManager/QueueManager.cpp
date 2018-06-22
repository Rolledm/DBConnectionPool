#include "QueueManager.h"

#include <thread>
#include <chrono>

#include <ctime>

#include "../../Logger/Logger.h"

void QueueManager::startWork() {
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


void QueueManager::push(std::string task) {
    std::lock_guard<std::mutex> locker(_lock);
    queue.emplace_back(task);
}

std::string QueueManager::pop() {
    std::lock_guard<std::mutex> locker(_lock);

    std::string str = queue.front();
    queue.pop_front();
    return str;
}

void QueueManager::initOutFile(std::string outfile) {
    connectionManager.initOutFile(outfile);
}

void QueueManager::endWork() {
    connectionManager.endWork();
}