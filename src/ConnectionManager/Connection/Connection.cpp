#include "Connection.h"

Connection::Connection(Settings settings) {
    init(settings);
    isBusy = false;
    time = std::time(nullptr);
}

Connection::~Connection() {
    mysql_close(connection);
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "Connection closed.";    
}

void Connection::init(Settings settings) {
    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql, settings.host.c_str(),
                                    settings.username.c_str(), settings.password.c_str(), settings.data_base.c_str(),
                                    settings.port, 0, settings.cli_flag);

    if (connection == nullptr) {
        throw mysql_error(&mysql);
    }
}