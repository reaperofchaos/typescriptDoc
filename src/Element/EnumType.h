
#ifndef ENUM_TYPE_INCLUDED
#define ENUM_TYPE_INCLUDED
#include <string>
#include <vector>
#include "Property.h"
class EnumType{
    bool exported; 
    std::string name;
    std::vector<Property> values;
    public: 
    EnumType(bool exported, std::string name, std::vector<Property> values){
        this->exported = exported; 
        this->name = name; 
        this->values = values; 
    }


    void display(){
        std::cout << "Enum: " << this->name << "\n"; 
        for(Property property: this->values){
            property.display();
        }
    }
};
#endif