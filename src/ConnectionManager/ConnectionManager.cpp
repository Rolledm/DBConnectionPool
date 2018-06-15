#include "ConnectionManager.h"

#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "../Logger/Logger.h"

//#define DBG

void ConnectionManager::init() {
    for (int i = 0; i < settings.numOfConnections.first; i++) {
        newConnection();
    }
}

void ConnectionManager::newConnection() {
    _lock.lock();
    if (connections.size() < settings.numOfConnections.second)
        connections.emplace_back(new Connection(settings));
    else
        BOOST_LOG_SEV(Logger::getInstance().lg, error) << "Can't create new connection. Number of connections is max already.";
    _lock.unlock();
}

void ConnectionManager::removeConnection(Connection* connection) {
    _lock.lock();
    connections.erase(std::remove(connections.begin(), connections.end(), connection), connections.end());
    delete(connection);
    _lock.unlock();
}

Connection* ConnectionManager::findConnection() {
    _lock.lock();
    for (auto& it : connections) {
        if (!it->isBusy) {
            it->isBusy = true;
            _lock.unlock();
            return it;
        }
    }
    _lock.unlock();
    return nullptr;
}

void ConnectionManager::start(std::string command, Connection* connection) {
    #ifdef DBG
        std::this_thread::sleep_for(std::chrono::seconds(3));
    #endif
    std::ofstream file(outFile, std::ios::app);
    MYSQL_RES *result;
    MYSQL_ROW row;
    int query_state;

    query_state = mysql_query(connection->connection, command.c_str());
    if (query_state != 0) {
        BOOST_LOG_SEV(Logger::getInstance().lg, warning) << mysql_error(connection->connection);
        file.close();
        connection->time = std::time(nullptr);
        connection->isBusy = false;
        return;
    }
    result = mysql_store_result(connection->connection);

    _lock.lock();
    if (result != nullptr) {
        file << "\n=========================\n\n";    
        while (( row = mysql_fetch_row(result)) != nullptr) {
            unsigned int num_fields;

            num_fields = mysql_num_fields(result);
            for(unsigned int i = 0; i < num_fields; i++)
            {
                file << row[i] << "\t";
            }

            file << std::endl;
        }
    }    
    
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Query " << command.c_str() << " finished successfully.";            
    _lock.unlock();

    mysql_free_result(result);
    file.close();
    connection->time = std::time(nullptr);
    connection->isBusy = false;
}

size_t ConnectionManager::numOfFreeConnections() {
    size_t num = 0;
    _lock.lock();
    
    for (auto& it : connections) {
        if (!(it->isBusy)) num++;
    }
    _lock.unlock();
    return num;
}

void ConnectionManager::watchForUnusedConnections() {
    while (true) {
        if (connections.size() > settings.numOfConnections.first && numOfFreeConnections() > 0) {
            std::time_t time = std::time(nullptr);
            Connection* temp = nullptr;
            for (auto& it : connections) {
                if (time - it->time >= settings.timeout && !it->isBusy) {
                    temp = it;
                    break;
                }
            }
            if (temp != nullptr) {
                removeConnection(temp);
                continue;
            }
        }
    }
}