#ifndef INTERFACE_TYPE_INCLUDED
#define INTERFACE_TYPE_INCLUDED
#include <string>
#include <iostream>
#include <vector>
#include "Property.h"

class InterfaceType{
    bool exported; 
    std::string name;
    std::vector<Property> properties;
    
    public:
    InterfaceType(bool exported, std::string name, std::vector<Property> properties){
        this->exported = exported; 
        this->name = name; 
        this->properties = properties; 
    }

    void display(){
        std::cout << "Type Name: " << this->name << "\n"; 
    }
};

#endif