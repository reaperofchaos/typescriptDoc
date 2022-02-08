#ifndef IMPORT_TYPE_INCLUDED
#define IMPORT_TYPE_INCLUDED
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

class ImportType{
    std::string defaultImport;
    std::vector<std::string> imports;
    std::string nodePath;
    fs::path importPath;
    public: 
    ImportType(){};
    ImportType(std::string defaultImport, std::vector<std::string> imports, std::string nodePath){
        this->defaultImport = defaultImport; 
        this->imports = imports; 
        this->nodePath = nodePath; 
        this->importPath = fs::current_path(); 
    } 
    
    void display(){
            std::cout << "Default Import: " << this->defaultImport << "\n";
            std::cout << "imports: ";
                for(std::string import : this->imports){
                        std::cout << import << ", "; 
                    }
            std::cout << "\n"; 
            std::cout << "Node Path: " << this->nodePath << "\n"; 
        }
};
#endif