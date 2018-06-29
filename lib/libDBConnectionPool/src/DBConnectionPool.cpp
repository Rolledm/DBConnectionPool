#include "DBConnectionPool.h"

#include <thread>
#include <chrono>

#include <ctime>

#include "../../libLogger/src/Logger.h"

void DBConnectionPool::startWork() {
    connectionManager.startWork();
    temp = false;

    BOOST_LOG_SEV(Logger::getInstance().lg, debug) << "startWork.";
    while (true) {
        if (temp == true) break;
        
        if (queue.size() == 0) continue;

        connectionManager.handleQuery(pop());
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

DBConnectionPool::~DBConnectionPool() {
    BOOST_LOG_SEV(Logger::getInstance().lg, debug) << "DBConnectionPool killed.";
}