#include "InitByXML.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

void InitByXML::initSettings(Settings* settings) {
    boost::property_tree::ptree pt;
    read_xml(path, pt);

    settings->username = pt.get<std::string>("settings.username", "");
    settings->password = pt.get<std::string>("settings.password", "");
    settings->host = pt.get<std::string>("settings.host", "localhost");
    settings->data_base = pt.get<std::string>("settings.data_base", "");    
    settings->port = pt.get<int>("settings.port", 3306);
    settings->cli_flag = pt.get<int>("settings.cli_flag", 0);
    settings->numOfConnections.first = pt.get<int>("settings.numOfConnections.min", 3);
    settings->numOfConnections.second = pt.get<int>("settings.numOfConnections.max", 5);    
    settings->timeout = pt.get<int>("settings.timeout", 10);
}