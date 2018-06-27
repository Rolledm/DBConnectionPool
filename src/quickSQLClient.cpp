#include <iostream>

#include "DBConnectionPool_interface.h"

void handleArguments(int argc, char** argv, DBConnectionPool_interface* dbPool);

int main(int argc, char** argv) {

    try {
        DBConnectionPool_interface pool;
        handleArguments(argc, argv, &pool);
        pool.startWork();
    } catch (const char* e) {
        std::cout << "Fatal error. Open log file to see error. " << std::endl;
        BOOST_LOG_SEV(Logger::getInstance().lg, fatal) << "Fatal: " << e;
        return 1;
    } catch (...) {
        std::cout << "Other exception." << std::endl;
        BOOST_LOG_SEV(Logger::getInstance().lg, fatal) << "Other exception.";        
        return 3;
    }
    return 0;
}

void handleArguments(int argc, char** argv, DBConnectionPool_interface* dbPool) {
    if (argc == 1) {
        DBConnectionPool_interface::showHelp();
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
                    i++;
                } else {
                    throw "There is no .xml file specified.";
                }
                
            } 
            else if (strcmp(argv[i], "-o") == 0) {              //output file
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    dbPool->setOutFile(argv[i+1]);
                    i++;
                } else {
                    throw "There is no output file specified.";
                }
                
            }
            else if (strcmp(argv[i], "-l") == 0) {              //logger severity level
                if (i < argc - 1 && argv[i+1][0]!='-') {
                    Logger::getInstance().changeSeverity(argv[i+1]);
                    i++;
                } else {
                    throw "There is no severity level specified.";
                }
                
            }
        }
    }
}