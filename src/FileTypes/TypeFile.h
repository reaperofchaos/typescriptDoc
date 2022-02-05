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
    std::vector<ImportType> imports;
    std::vector<InterfaceType> interfaces;
    std::vector<EnumType> enums; 

    public: 
        TypeFile(fs::path path) : FileType(path){
            this->path = path; 
            findImports(); 
            findInterface();
            findEnum();
        }

        //find imports
        void findImports(){
            std::regex r("import\\W(\\w{0,}),?\\W?(\\{\\W?[\\w{1,},?\\W?]{0,}\\}){0,1} from [\"|\']+(.*)[\"|\']+");
		    std::smatch importMatch;
            for(std::string line: this->lines){
                bool found = std::regex_search(line, importMatch, r);
                if(found){
                    std::string importDefault = importMatch[1]; 
                    std::string foundImports = importMatch[2];
                    std::vector<std::string> imports;

                    if(foundImports.length() > 0){
                        foundImports.erase(0, 1); 
                        foundImports.pop_back();
                        std::stringstream sstr(foundImports);
                        while(sstr.good())
                        {
                            std::string substr;
                            getline(sstr, substr, ',');
                            if(substr[substr.length() -1] == ' '){
                                substr.pop_back(); 
                            }
                            imports.push_back(substr);
                        }
                    }
                    std::string importPath = importMatch[3];
                    this->imports.push_back(ImportType(importDefault, imports, importPath ));
                }
            }
        }

        void findInterface(){
            std::regex startInterface("(export)?\\W?interface\\W+(\\w+)\\{");
		    std::smatch interfaceStart;
            std::regex endInterface("\\}");
            std::smatch interfaceEnd;
            std::regex interfaceProperty("(\\w+)\\:((?:\\W(?:(?:['\"]\\w?['\"])|(?:\\w+\\[?\\]?))\\W?\\|?)+);");
            std::smatch interfacePropertyMatches; 
            std::string interfaceCode = ""; 
            std::vector<Property> properties = {};
            std::string exported = ""; 
            std::string interfaceName = "";
            for(std::string line: this->lines){
                if(interfaceCode == ""){
                    properties = {};
                    bool interfaceStartFound = std::regex_search(line, interfaceStart, startInterface);
                    if(interfaceStartFound){
                        interfaceCode = line; 
                        exported = interfaceStart[1];
                        interfaceName = interfaceStart[2];
                    }  
                }else{
                    bool interfaceEndFound = std::regex_search(line, interfaceEnd, endInterface);
                    bool interfacePropertyFound = std::regex_search(line, interfacePropertyMatches, interfaceProperty);
                    interfaceCode += line; 
                    if(interfaceEndFound){
                        interfaceCode = ""; 
                        this->interfaces.push_back(InterfaceType(exported == "export", interfaceName, properties)); 
                        properties.clear(); 
                    }
                    if(interfacePropertyFound){
                        std::string propertyName = interfacePropertyMatches[1];
                        std::string propertyValue = interfacePropertyMatches[2];
                        size_t pos = 0;
                        // std::cout << "Property name: " << propertyName << " value: " << propertyValue << "\n";
                        std::vector<std::string> propertyValues = {};
                        std::string delimiter = "|";
                        while ((pos = propertyValue.find(delimiter)) != std::string::npos) {
                            std::string prop = propertyValue.substr(0, pos);
                            propertyValues.push_back(prop);
                            propertyValue.erase(0, pos + delimiter.length());
                        }
                        propertyValues.push_back(propertyValue);
                        properties.push_back(Property(propertyName, propertyValues));
                    }
                }
            }
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

        void displayImports(){
            for(ImportType import : this->imports){
                import.display(); 
            }
        }
        void displayInterfaces(){
            for(InterfaceType interface : this->interfaces){
                interface.display();
            }
        }

        void displayEnums(){
            for(EnumType enumType : this->enums){
                enumType.display();
            }
        }
        
};  
#endif