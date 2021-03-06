#include "FileType.h"

class ReactComponentFile: public FileType{
    fs::path path;
    std::vector<ImportType> imports;
    
    public: 
    ReactComponentFile(fs::path path) : FileType(path){
            this->path = path; 
            this->findImports(); 
        }

};