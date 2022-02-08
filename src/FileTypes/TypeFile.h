#ifndef TYPE_FILE_INCLUDED
#define TYPE_FILE_INCLUDED
#include <iostream>
#include <string.h>
#include <vector>
#include <regex>
#include <filesystem>
#include <sstream>
#include "FileType.h"
#include "../Element/EnumType.h"
#include "../Element/InterfaceType.h"
#include "../Element/ImportType.h"

namespace fs = std::filesystem;

class TypeFile: public FileType{
    fs::path path;
    std::vector<InterfaceType> interfaces;
    std::vector<EnumType> enums; 

    public: 
        TypeFile(fs::path path) : FileType(path){
            this->path = path; 
            findImports(); 
            findInterfaces();
            findEnum();
        }

        void findEnum(){
            std::regex startEnumPattern("(export)\\W+enum\\W+(\\w+)\\W?\\{");
		    std::smatch foundEnumStart;
            std::regex endEnumPattern("\\}");
            std::smatch foundEnumEnd;
            std::regex enumValuePattern("(\\w+)\\W?=\\W?([\"'].*[\"']),?");
            std::smatch foundEnumValues;
            std::string enumCode = ""; 
            std::string exported;
            std::string enumName;
            std::vector<Property> enumValues;
            for(std::string line: this->lines){
                if(enumCode == ""){
                    bool enumStartFound = std::regex_search(line, foundEnumStart, startEnumPattern);
                    if(enumStartFound){
                        enumCode = line; 
                        exported = foundEnumStart[1];
                        enumName = foundEnumStart[2];
                    }
                }
                if(enumCode != ""){
                    bool enumEndFound = std::regex_search(line, foundEnumEnd, endEnumPattern);
                    bool enumValueFound = std::regex_search(line, foundEnumValues, enumValuePattern);
                    enumCode += line;

                    if(enumValueFound){
                        std::string propertyName = foundEnumValues[1];
                        std::string propertyValue = foundEnumValues[2];
                        enumValues.push_back(Property(propertyName, propertyValue));
                    }

                    if(enumEndFound){
                        this->enums.push_back(EnumType(exported == "export", enumName, enumValues));
                        enumValues.clear();
                        enumCode = ""; 
                    }
                }
            }
        }

        void displayType(){
            std::cout << path.stem() <<  " is a type file \n" << std::endl;
        }

        void displayEnums(){
            for(EnumType enumType : this->enums){
                enumType.display();
            }
        }
        
};  
#endif