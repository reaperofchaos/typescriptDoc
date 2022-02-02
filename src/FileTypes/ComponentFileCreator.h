#ifndef FILETYPE_CREATOR_INCLUDED
#define FILETYPE_CREATOR_INCLUDED
#include "FileType.h"
#include "TypeFile.h"

namespace fs = std::filesystem;

class ComponentFileCreator{
    public:
       static FileType *fileFactoryMethod(std::string type, fs::path file){
           if(type == "type"){
               return new TypeFile(file); 
           }
           return new FileType(file);
       }
};
#endif