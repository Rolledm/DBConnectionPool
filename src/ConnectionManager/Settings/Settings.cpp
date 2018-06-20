#include "Settings.h"

void Settings::init(Initialisable* init) {

   username = init->get("settings.username", "");
   password = init->get("settings.password", "");
   host = init->get("settings.host", "");
   data_base = init->get("settings.data_base", "");

   port = init->get("settings.port", 0);
   cli_flag = init->get("settings.cli_flag", 0);
   numOfConnections.first = init->get("settings.numOfConnections.min", 1);
   numOfConnections.second = init->get("settings.numOfConnections.max", 1);
   timeout = init->get("settings.timeout", 0);
   

    delete init;
}