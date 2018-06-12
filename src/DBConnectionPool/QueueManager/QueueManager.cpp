#include "QueueManager.h"

#include <thread>
#include <chrono>

#include <ctime>

#include "../../Logger/Logger.h"


void QueueManager::startWork() {
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Num of connections: " << connectionManager.connections.size();
    std::thread thread(&ConnectionManager::watchForUnusedConnections, &connectionManager);
    
    while (true) {

        if (queue.size() == 0) continue;

        Connection* tempConnection = connectionManager.findConnection();
        if (tempConnection != nullptr) {
            std::string task = pop();
            std::thread thread(&ConnectionManager::start, &connectionManager, task, tempConnection);
            thread.detach();
        } else {
            if (connectionManager.connections.size() < connectionManager.settings.numOfConnections.second) {
                connectionManager.newConnection();
                BOOST_LOG_SEV(Logger::getInstance().lg, info) << "New connection! Num of connections: " << connectionManager.connections.size();            
            }
        }
        
    }
}


void QueueManager::push(std::string task) {
    _lock.lock();
    //std::lock_guard<std::mutex> locker(_lock);
    queue.emplace_back(task);

    _lock.unlock();
}

std::string QueueManager::pop() {
    _lock.lock();
    //std::lock_guard<std::mutex> locker(_lock);

    std::string str = queue.front();
    queue.pop_front();

    _lock.unlock();

    return str;
}