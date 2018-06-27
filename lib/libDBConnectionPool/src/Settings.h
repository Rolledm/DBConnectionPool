#ifndef SETTINGS_H
#define SETTINGS_H

#include <utility>
#include <string>
#include "Initialisable.h"
#include "InitByXML.h"

class Settings {
public:
    static Settings& getInstance();
    void initFields(Initialisable* settingsInitialiser);

    std::string getUsername();
    std::string getPassword();
    std::string getHost();
    std::string getDataBase();
    int getPort();
    int getCliFlag();
    std::pair<int, int> getNumOfConnections();
    int getTimeout();
    bool getIsInitialised();

private:
    std::string username;
    std::string password;
    std::string host;
    std::string data_base;
    int port;
    int cli_flag;

    bool isInitialised;

    std::pair<int, int> numOfConnections; // first - min, second - max
    int timeout; // in seconds

private:
    Settings() {isInitialised = false;}
    Settings(const Settings&) = delete;
    Settings& operator=(Settings&) = delete;

};

#endif