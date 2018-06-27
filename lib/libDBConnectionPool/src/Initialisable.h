#ifndef INITIALISABLE_H
#define INITIALISABLE_H

#include <string>

class Initialisable {
public:
    Initialisable (std::string path) {this->path = path;}
    virtual std::string get(std::string, std::string) = 0;
    virtual int get(std::string, int) = 0;    
protected:
    std::string path;
};

#endif