#ifndef FUNCTION_TYPE_INCLUDED
#define FUNCTION_TYPE_INCLUDED
#include <string>
#include <vector>
#include "Property.h"

class FunctionType{
    std::string name;
    std::string returnType;
    std::vector<Property> parameters;
    std::vector<std::string> comments;
};
#endif