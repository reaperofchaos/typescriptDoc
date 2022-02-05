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
            std::vector<std::string> interfaceCodes; 
            std::vector<Property> properties = {};
            std::string exported = ""; 
            std::string interfaceName = "";
            for(std::string line: this->lines){
                if(interfaceCode == ""){
                    properties = {};
                    bool interfaceStartFound = std::regex_search(line, interfaceStart, startInterface);
                    if(interfaceStartFound){
                        interfaceCode = line; 
                        // std::cout << "Results from InterfaceStart match" << "\n\n"; 
                        exported = interfaceStart[1];
                        interfaceName = interfaceStart[2];
                        // std::cout << "Exported:" << ((exported == "export") ? "true" : "false") << "\n";
                        // std::cout << "Interface Name:" << interfaceName << "\n";
                    }  
                }else{
                    bool interfaceEndFound = std::regex_search(line, interfaceEnd, endInterface);
                    bool interfacePropertyFound = std::regex_search(line, interfacePropertyMatches, interfaceProperty);
                    interfaceCode += line; 
                    if(interfaceEndFound){
                        interfaceCodes.push_back(interfaceCode);
                        interfaceCode = ""; 
                        this->interfaces.push_back(InterfaceType(exported == "export", interfaceName, properties)); 
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
                        // for(std::string p: propertyValues){
                        //     std::cout << "Value: " << p << "\n"; 
                        // }
                        properties.push_back(Property(propertyName, propertyValues));
                    }
                }
            }

            // std::cout << "Displaying interfaces" << "\n"; 
            // for(std::string interface : interfaceCodes){
            //     std::cout << interface << "\n";
            // }
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

        
};  
#endif