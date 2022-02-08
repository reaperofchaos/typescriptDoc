#include "FileType.h"

class HelperFunction: : public FileType{
    fs::path path;
    std::vector<ImportType> imports;
    
    public: 
        HelperFunction(fs::path path) : FileType(path){
            this->path = path; 
            this->findImports(); 
        }

        

};