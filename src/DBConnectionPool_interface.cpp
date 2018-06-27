#include "DBConnectionPool_interface.h"

DBConnectionPool_interface::DBConnectionPool_interface() {
    sev_lvl = "debug";          //setting
    outFile = "file1";          //default
    Logger::getInstance().init(sev_lvl);        
}

void DBConnectionPool_interface::initFields() {
    if (Settings::getInstance().getIsInitialised() == false) {
        throw "Initialiser not specified.";
    }
    
    
    //Logger::getInstance().changeSeverity(sev_lvl);  //handle args and init components
    pool.initOutFile(outFile);

    std::cout << "Hello." << std::endl;


    std::ofstream file(outFile);    //checking output file
    if (!file) {
        throw "Error w/ out file.";
    }
    file.close();
}


/*void DBConnectionPool::handleArguments(int argc, char** argv) {
    if (argc == 1) {
        showHelp();
        exit(0);
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-x") == 0) {                   //xml
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    std::ifstream file(argv[i+1]);
                    if (!file) {
                        throw "Error w/ .xml file.";
                    }
                    file.close();

                    Settings::getInstance().initFields(new InitByXML(argv[i+1]));
                    isInitialised = true;
                    i++;
                } else {
                    throw "There is no .xml file specified.";
                }
                
            } 
            else if (strcmp(argv[i], "-o") == 0) {              //output file
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    outFile = argv[i+1];
                    i++;
                } else {
                    throw "There is no output file specified.";
                }
                
            }
            else if (strcmp(argv[i], "-l") == 0) {              //logger severity level
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    sev_lvl = argv[i+1];
                    i++;
                } else {
                    throw "There is no severity level specified.";
                }
                
            }
        }
    }
}*/


void DBConnectionPool_interface::startWork() {
    initFields();

    std::string promt;
    std::thread thread(&DBConnectionPool::startWork, &pool);
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
}

void DBConnectionPool_interface::endWork() {
    pool.endWork();
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Work ended successfully.";
    exit(0);
}

void DBConnectionPool_interface::showHelp() {
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

void DBConnectionPool_interface::setOutFile(std::string outFile) {
    this->outFile = outFile;
}