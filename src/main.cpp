#include <iostream>

#include "DBConnectionPool/DBConnectionPool.h"

int main(int argc, char** argv) {

    try {
        DBConnectionPool pool(argc, argv);
        pool.startWork();
    } catch (const char* e) {
        std::cout << "Error: " << e << std::endl;
        BOOST_LOG_SEV(Logger::getInstance().lg, fatal) << "Error: " << e;
        return 1;
    } catch (...) {
        std::cout << "Other exception." << std::endl;
        BOOST_LOG_SEV(Logger::getInstance().lg, fatal) << "Other exception.";        
        return 3;
    }
    return 0;
}