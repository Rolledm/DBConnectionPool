#include "InitByXML.h"


std::string InitByXML::get(std::string key, std::string def_val) {
    return pt.get<std::string>(key, def_val);
}

int InitByXML::get(std::string key, int def_val) {
    return pt.get<int>(key, def_val);    
}