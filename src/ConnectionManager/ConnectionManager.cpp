#include "ConnectionManager.h"

#include <fstream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "../Logger/Logger.h"

//#define DBG

void ConnectionManager::initOutFile(std::string outFile) {
    numOfOpenedConnections = 0;
    this->outFile = outFile;
    for (int i = 0; i < Settings::getInstance().getNumOfConnections().first; i++) {
        newConnection();
    }
}

void ConnectionManager::newConnection() {
    std::lock_guard<std::mutex> locker(_lock);
    if (numOfOpenedConnections < Settings::getInstance().getNumOfConnections().second) {
        connections.emplace_back(std::shared_ptr<Connection>(new Connection()));
        numOfOpenedConnections++;
    }
    else
        BOOST_LOG_SEV(Logger::getInstance().lg, error) << "Can't create new connection. Number of connections is max already.";
}

void ConnectionManager::removeConnection(std::shared_ptr<Connection> connection) {
    std::lock_guard<std::mutex> locker(_lock);
    connections.erase(std::remove(connections.begin(), connections.end(), connection), connections.end());
    numOfOpenedConnections--;
}

std::shared_ptr<Connection> ConnectionManager::findConnection() {
    std::lock_guard<std::mutex> locker(_lock);
    std::shared_ptr<Connection> temp = nullptr;
    for (auto& it : connections) {
        if (!it->isBusy) {
            it->isBusy = true;
            temp = it;
            break;
        }
    }
    return temp;
}

void ConnectionManager::start(std::string command, std::shared_ptr<Connection> connection) {
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

    std::lock_guard<std::mutex> locker(_lock);
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

    mysql_free_result(result);
    file.close();
    connection->time = std::time(nullptr);
    connection->isBusy = false;
}

size_t ConnectionManager::numOfFreeConnections() {
    size_t num = 0;
    std::lock_guard<std::mutex> locker(_lock);    
    
    for (auto& it : connections) {
        if (!(it->isBusy)) num++;
    }
    return num;
}

void ConnectionManager::watchForUnusedConnections() {
    while (true) {
        if (numOfOpenedConnections > Settings::getInstance().getNumOfConnections().first && numOfFreeConnections() > 0) {
            std::time_t time = std::time(nullptr);
            std::shared_ptr<Connection> temp = nullptr;
            for (auto& it : connections) {
                if (time - it->time >= Settings::getInstance().getTimeout() && !it->isBusy) {
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

void ConnectionManager::endWork() {
    std::lock_guard<std::mutex> locker(_lock);
    connections.clear();
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "All connections closed.";
}

int ConnectionManager::getNumOfOpenedConnections() {
    return numOfOpenedConnections;
}