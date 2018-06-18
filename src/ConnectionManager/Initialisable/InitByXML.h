#ifndef INITBYXML_H
#define INITBYXML_H

#include "Initialisable.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class InitByXML : public Initialisable {
public:
    InitByXML(std::string path) : Initialisable(path) {read_xml(path, pt);}
    virtual std::string get(std::string, std::string);
    virtual int get(std::string, int);  
private:
    boost::property_tree::ptree pt;    
};

#endif