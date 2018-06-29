#include "DBConnectionPool_interface.h"

DBConnectionPool_interface::DBConnectionPool_interface() {
}

void DBConnectionPool_interface::initFields() {
    if (Settings::getInstance().getIsInitialised() == false) {
        throw "Initialiser not specified.";
    }

    std::ofstream file(Settings::getInstance().getOutFile());    //checking output file
    if (!file) {
        throw "Error w/ out file.";
    }
    file.close();
}

void DBConnectionPool_interface::startWork() {
    initFields();
    

    std::string promt;
    std::thread thread(&DBConnectionPool::startWork, &pool);
    thread.detach();
    while (true) {
        std::cout << "Enter your command: ";
        std::getline(std::cin, promt);
        if (promt == "exit") {break;}
        if (promt == "script") {
            std::cout << "Path: ";
            std::getline(std::cin, promt);
            std::ifstream file(promt);
            if (!file) {
                std::cout << "Script file error!" << std::endl;
                continue;
            }
            while (getline(file, promt)) {
                pool.push(promt);      
            }
            continue;
        }
        pool.push(promt);              
    }
    pool.temp = true;
}

void DBConnectionPool_interface::showHelp() {
    std::cout << "DBConnectionPool - utility for multi-thread work w/ database." << std::endl;
    std::cout << "Usage: ./main [OPTIONS]" << std::endl << std::endl;
    std::cout << "Available options:" << std::endl;
    std::cout << "-x PATH_TO_FILE - use .xml file to initialise connections to database." << std::endl;
    std::cout << "-l SEVERITY_LEVEL - change logger severity level. Default: debug." << std::endl << std::endl;
    std::cout << "Available severity levels:" << std::endl;
    std::cout << "debug, info, warning, error, fatal." << std::endl << std::endl;
    std::cout << "Example of usage" << std::endl;
    std::cout << "./main -x ../../test.xml -l info" << std::endl;
}