#ifndef FILE_TYPE_INCLUDED
#define FILE_TYPE_INCLUDED
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include "../Element/ImportType.h"
#include "../Element/Property.h"
#include "../Element/InterfaceType.h"

namespace fs = std::filesystem;

class FileType{
    public:
    fs::path file; 
    std::string filename; 
    std::ifstream in; 
    std::vector<std::string> lines; 
    std::string fileType;
    std::vector<ImportType> imports;
    std::vector<InterfaceType> interfaces;
    InterfaceType reduxStoreTypes; 

    public: 
        FileType(fs::path file){
            this->file = file;
            this->filename = fs::canonical(this->file);
            this->in.open(this->filename, std::ios::in);
            int i = 0; 
            for(std::string line; std::getline(this->in, line); )
            {
                this->lines.push_back(line);
                i++; 
            }
        }
    
    void readFile(){
        for(std::string line : lines){
            std::cout << line << "\n";
        }
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
    void displayImports(){
        for(ImportType import : this->imports){
            import.display(); 
        }
    }
    virtual void displayType(){};

    void findInterfaces(){
            std::regex startInterface("(export)?\\W?interface\\W+(\\w+)\\W?\\{");
		    std::smatch interfaceStart;
            std::regex endInterface("\\}");
            std::smatch interfaceEnd;
            std::regex interfaceProperty("(\\w+)\\??\\:((?:\\W(?:(?:['\"]\\w?['\"])|(?:\\w+\\[?\\]?))\\W?\\|?)+);?,?");
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
    virtual void findEnum(){};
    void displayInterfaces(){
        std::cout << "Interface count: " << interfaces.size() << "\n"; 
        for(InterfaceType interface : this->interfaces){
            interface.display();
        }
    }
    virtual void setReduxStore(){};
    virtual void displayEnums(){}
    virtual void displayReduxStore(){}; 
};
#endif