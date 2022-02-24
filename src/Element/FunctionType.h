#ifndef FUNCTION_TYPE_INCLUDED
#define FUNCTION_TYPE_INCLUDED
#include <string>
#include <vector>
#include "Property.h"

class FunctionType{
    std::string name;
    std::string returnType;
    std::string arguments; 
    std::vector<Property> parameters;
    std::vector<std::string> comments;
    std::string functionBody; 
    std::vector<FunctionType> nestedFunctions; 

    public:
        FunctionType(){}
        FunctionType(std::string name, std::string returnType, std::string arguments, std::string functionBody, std::vector<FunctionType> nestedFunctions){
            this->name = name; 
            this->returnType = returnType;
            this->arguments = arguments; 
            this->functionBody = functionBody;
            this->nestedFunctions = nestedFunctions;
        }
        FunctionType(std::string name, std::string returnType, std::string arguments, std::string functionBody){
            this->name = name; 
            this->returnType = returnType;
            this->arguments = arguments; 
            this->functionBody = functionBody;
        }
        FunctionType(std::string name, std::string returnType, std::string arguments, std::vector<Property> parameters, std::vector<std::string> comments){
            this->name = name; 
            this->returnType = returnType;
            this->arguments = arguments; 
            this->parameters = parameters;
            this->comments = comments; 
        }

        void display(){
            std::cout << "Function Name: " << this->name << "\n";
            std::cout << "Parameters: " << this->arguments << "\n";  
            std::cout << "Returns: " << this->returnType << "\n"; 
        }
};
#endif