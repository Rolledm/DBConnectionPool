#ifndef SETTINGS_H
#define SETTINGS_H

#include <utility>
#include <string>

typedef struct {
    std::string username;
    std::string password;
    std::string host;
    std::string data_base;
    int port;
    int cli_flag;

    std::pair<int, int> numOfConnections; // first - min, second - max
    int timeout; // in seconds

} Settings;

#endif