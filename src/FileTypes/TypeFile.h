#ifndef TYPE_FILE_INCLUDED
#define TYPE_FILE_INCLUDED
#include <iostream>
#include <vector>
#include <filesystem>
#include "FileType.h"
#include "../Element/EnumType.h"
#include "../Element/InterfaceType.h"

namespace fs = std::filesystem;

class TypeFile: public FileType{
    fs::path path;
    std::vector<InterfaceType> interfaces;
    std::vector<EnumType> enums; 

    public: 
        TypeFile(fs::path path) : FileType(path){
            this->path = path; 
        }

        void displayType(){
            std::cout << path.stem() <<  " is a type file \n" << std::endl;
        }
};
#endif