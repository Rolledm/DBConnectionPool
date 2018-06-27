#include "Settings.h"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

void Settings::initFields(Initialisable* settingsInitialiser) {

   username = settingsInitialiser->get("settings.username", "user");
   password = settingsInitialiser->get("settings.password", "");
   host = settingsInitialiser->get("settings.host", "");
   data_base = settingsInitialiser->get("settings.data_base", "");

   port = settingsInitialiser->get("settings.port", 0);
   cli_flag = settingsInitialiser->get("settings.cli_flag", 0);
   numOfConnections.first = settingsInitialiser->get("settings.numOfConnections.min", 1);
   numOfConnections.second = settingsInitialiser->get("settings.numOfConnections.max", 1);
   timeout = settingsInitialiser->get("settings.timeout", 0);
   
   isInitialised = true;

    delete settingsInitialiser;
}

std::string Settings::getUsername() {
    return username;
}

std::string Settings::getPassword() {
    return password;
}

std::string Settings::getHost() {
    return host;
}

std::string Settings::getDataBase() {
    return data_base;
}

int Settings::getPort() {
    return port;
}

int Settings::getCliFlag() {
    return cli_flag;
}

std::pair<int, int> Settings::getNumOfConnections() {
    return numOfConnections;
}

int Settings::getTimeout() {
    return timeout;
}

bool Settings::getIsInitialised() {
    return isInitialised;
}