#ifndef PROPERTY_TYPE_INCLUDED
#define PROPERTY_TYPE_INCLUDED
#include <string>
#include <iostream>
#include <vector> 
struct Property{
    std::vector<std::string> propertyTypes; 
    std::string propertyName;
    std::string propertyValue;
    bool propertyOptional;

    public: 
    Property(std::string propertyName, bool propertyOptional, std::string propertyValue){
        this->propertyName = propertyName;
        this->propertyValue = propertyValue; 
        this->propertyOptional = propertyOptional;
    }

    Property(std::string propertyName, std::string propertyValue){
        this->propertyName = propertyName;
        this->propertyValue = propertyValue; 
    }

    Property(std::string propertyName, std::vector<std::string> propertyTypes){
        this->propertyName = propertyName;
        this->propertyTypes = propertyTypes; 
    }
     Property(std::string propertyName, bool propertyOptional,  std::vector<std::string> propertyTypes){
        this->propertyName = propertyName;
        this->propertyTypes = propertyTypes; 
        this->propertyOptional = propertyOptional;
    }
    void display(){
        std::cout << "Property: " << this->propertyName << " " << "\n";
        if(this->propertyOptional){
            std:: cout << "Optional Type" << "\n"; 
        }
        if(this->propertyTypes.size() > 0){
            std::cout << "Property Types: ";
            int i = 0; 
            for(std::string propertyType : this->propertyTypes){
                std::cout << propertyType;
                if(i != this->propertyTypes.size() - 1){
                    std::cout << ", ";
                }
                i++; 
            }
            std::cout << "\n"; 
        }

        if(this->propertyValue != ""){
            std::cout << "Value: " << this->propertyValue << "\n";
        };
    }
};
#endif