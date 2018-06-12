#ifndef INITIALISABLE_H
#define INITIALISABLE_H

#include "../../ConnectionManager/Settings/Settings.h"

class Initialisable {
public:
    Initialisable (std::string path) {this->path = path;}
    virtual void initSettings(Settings* settings) = 0;
//private:
    std::string path;
};

#endif