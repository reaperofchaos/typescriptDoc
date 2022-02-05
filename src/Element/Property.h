#ifndef PROPERTY_TYPE_INCLUDED
#define PROPERTY_TYPE_INCLUDED
#include <string>
#include <vector> 
struct Property{
    std::vector<std::string> propertyTypes; 
    std::string propertyName;
    std::string propertyValue;

    Property(std::string propertyName, std::vector<std::string> propertyTypes){
        this->propertyName = propertyName;
        this->propertyTypes = propertyTypes; 
    }
};
#endif