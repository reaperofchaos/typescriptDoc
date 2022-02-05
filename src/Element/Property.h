#ifndef PROPERTY_TYPE_INCLUDED
#define PROPERTY_TYPE_INCLUDED
#include <string>
#include <iostream>
#include <vector> 
struct Property{
    std::vector<std::string> propertyTypes; 
    std::string propertyName;
    std::string propertyValue;

    public: 
    Property(std::string propertyName, std::string propertyValue){
        this->propertyName = propertyName;
        this->propertyValue = propertyValue; 
    }
    Property(std::string propertyName, std::vector<std::string> propertyTypes){
        this->propertyName = propertyName;
        this->propertyTypes = propertyTypes; 
    }
    void display(){
        std::cout << "Property: " << this->propertyName << " " << "\n";
        if(this->propertyTypes.size() > 0){
            std::cout << "Property Types; ";
            for(std::string propertyType : this->propertyTypes){
                std::cout << propertyType << ", "; 
            }
            std::cout << "\n"; 
        }

        if(this->propertyValue != ""){
            std::cout << "Value: " << this->propertyValue << "\n";
        };
    }
};
#endif