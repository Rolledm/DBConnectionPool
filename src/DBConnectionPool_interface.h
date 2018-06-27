#ifndef DBCONNECTIONPOOL_INTERFACE_H
#define DBCONNECTIONPOOL_INTERFACE_H

#include "../lib/libLogger/src/Logger.h"
#include "../lib/libDBConnectionPool/src/DBConnectionPool.h"

#include <vector>
#include <mutex>
#include <thread>
#include <fstream>

class DBConnectionPool_interface {
public:
    DBConnectionPool_interface();
    ~DBConnectionPool_interface() = default;
    void initFields();
    void startWork();
    void endWork();
    static void showHelp();

    void setOutFile(std::string outFile);
    
protected:
    DBConnectionPool pool;
    std::string outFile;
    std::string sev_lvl;

private:
    DBConnectionPool_interface(const DBConnectionPool_interface&) = delete;
    DBConnectionPool_interface(const DBConnectionPool_interface&&) = delete;
    DBConnectionPool_interface& operator=(DBConnectionPool_interface&) = delete;
};

#endif