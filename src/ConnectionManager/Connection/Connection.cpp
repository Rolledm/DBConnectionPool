#include "Connection.h"

Connection::Connection() {
    init();
    isBusy = false;
    time = std::time(nullptr);
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Connection opened.";        
}

Connection::~Connection() {
    mysql_close(connection);
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Connection closed.";    
}

void Connection::init() {
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, Settings::getInstance().getHost().c_str(),
                                    Settings::getInstance().getUsername().c_str(), Settings::getInstance().getPassword().c_str(), 
                                    Settings::getInstance().getDataBase().c_str(), Settings::getInstance().getPort(), 0, Settings::getInstance().getCliFlag());

    if (connection == nullptr) {
        throw mysql_error(&mysql);
    }
}