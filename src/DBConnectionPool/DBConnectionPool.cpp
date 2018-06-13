#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool(int argc, char** argv) {
    sev_lvl = "debug";
    outFile = "/home/rolledm/file1";
    handleArguments(argc, argv);
    init->initSettings(&queueManager.connectionManager.settings);
    queueManager.connectionManager.outFile = outFile;

    Logger::getInstance().init(sev_lvl);    
    
    for (int i = 0; i < queueManager.connectionManager.settings.numOfConnections.first; i++) {
        //queueManager.connectionManager.connections.emplace_back(new MySQLConnector(queueManager.connectionManager.settings));  // throws Exception if can't connect to db
        queueManager.connectionManager.newConnection();
    }

    std::cout << "Successful connection to MySQL." << std::endl;
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Successful connection to MySQL.";


    std::ofstream file(outFile);
    if (!file) {
        throw "Error w/ out file.";
    }
    file.close();

    /*file.open("sample.log");
    if (!file) {
        throw "Error w/ log file.";
    }
    file.close();*/
}


DBConnectionPool::~DBConnectionPool() {
    delete(init);
    //for (auto& it : queueManager.connectionManager.connections) {
       // mysql_close(it->connection);
   // }
    queueManager.connectionManager._lock.unlock();
    queueManager.connectionManager._lock.lock();    
    for (auto& it : queueManager.connectionManager.connections) {
        mysql_close(it->connection);
        BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Connection closed.";
        delete(it);
    }
    queueManager.connectionManager.connections.clear();
    queueManager.connectionManager._lock.unlock();    
    queueManager._lock.unlock();
    //std::cout << "deleted." << std::endl;
    
}

void DBConnectionPool::handleArguments(int argc, char** argv) {
    if (argc == 1) {
        showHelp();
        exit(0);
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-x") == 0) {
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    init = new InitByXML(argv[i+1]);
                    i++;
                } else {
                    throw "Incorrect argument.";
                }
                
            } 
            else if (strcmp(argv[i], "-o") == 0) {
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    outFile = argv[i+1];
                    i++;
                } else {
                    throw "Incorrect argument.";
                }
                
            }
            else if (strcmp(argv[i], "-l") == 0) {
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    sev_lvl = argv[i+1];
                    i++;
                } else {
                    throw "Incorrect argument.";
                }
                
            }
        }
    }
}


void DBConnectionPool::startWork() {
    std::string promt;
    std::thread thread(&QueueManager::startWork, &queueManager);//queueManager.startWork();
    thread.detach();
    while (true) {
        std::cout << "Enter your command: ";
        std::getline(std::cin, promt);
        if (promt == "exit") {endWork();}
        if (promt == "script") {
            std::cout << "Path: ";
            std::getline(std::cin, promt);
            std::ifstream file(promt);
            if (!file) {
                std::cout << "File error!" << std::endl;
                continue;
            }
            while (getline(file, promt)) {
                //std::thread thread(&DBConnectionPool::start, this, promt);
                //thread.detach();  
                queueManager.push(promt);      
            }
            continue;
        }
        //std::thread thread(&DBConnectionPool::start, this, promt);
        //thread.detach();
        queueManager.push(promt);              
    }
}

void DBConnectionPool::endWork() {
    delete(init);
    //for (auto& it : queueManager.connectionManager.connections) {
       // mysql_close(it->connection);
    // }
    queueManager.connectionManager._lock.unlock();
    queueManager.connectionManager._lock.lock();    
    for (auto& it : queueManager.connectionManager.connections) {
        mysql_close(it->connection);
        //BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Connection closed.";
        delete(it);
    }
    queueManager.connectionManager.connections.clear();
    queueManager.connectionManager._lock.unlock();    
    queueManager._lock.unlock();

    
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Work ended successfully.";
    exit(0);
}

void DBConnectionPool::showHelp() {
    std::cout << "DBConnectionPool - utility for multi-thread work w/ database." << std::endl;
    std::cout << "Usage: ./main [OPTIONS]" << std::endl << std::endl;
    std::cout << "Available options:" << std::endl;
    std::cout << "-x PATH_TO_FILE - use .xml file to initialise connections to database." << std::endl;
    std::cout << "-o PATH_TO_FILE - specify output file." << std::endl;
    std::cout << "-l SEVERITY_LEVEL - change logger severity level. Default: debug." << std::endl << std::endl;
    std::cout << "Available severity levels:" << std::endl;
    std::cout << "debug, info, warning, error, fatal." << std::endl << std::endl;
    std::cout << "Example of usage" << std::endl;
    std::cout << "./main -x ../../test.xml -o ~/file1 -l info" << std::endl;
}