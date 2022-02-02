#ifndef INTERFACE_TYPE_INCLUDED
#define INTERFACE_TYPE_INCLUDED
#include <string>
#include <vector>
#include "Property.h"

class InterfaceType{
    std::string name;
    std::vector<Property> properties;
};

#endif