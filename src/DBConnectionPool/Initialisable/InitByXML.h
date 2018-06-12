#ifndef INITBYXML_H
#define INITBYXML_H

#include "Initialisable.h"

class InitByXML : public Initialisable {
public:
    InitByXML(std::string path) : Initialisable(path) {}
    virtual void initSettings(Settings* settings);
};

#endif