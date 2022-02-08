#include "FileType.h"
#include "../Element/ImportType.h"
#include "../Element/InterfaceType.h"

class ReducerFile: public FileType{
    fs::path path;
    std::vector<ImportType> imports;
    std::vector<InterfaceType> interfaces; 
    InterfaceType reduxStoreTypes;
    
    public: 
    ReducerFile(fs::path path) : FileType(path){
            this->path = path; 
            this->findImports(); 
            this->findInterfaces(); 
            std::cout << "Interface count: " << interfaces.size() << "\n"; 
            this->setReduxStore();
        }
    void setReduxStore(){
        std::cout << "interface count " << this->interfaces.size() << "\n"; 
        if(this->interfaces.size() > 0){
            this->reduxStoreTypes = this->interfaces.at(0); 
        }
    }
    void displayReduxStore(){
                this->reduxStoreTypes.display(); 

    }
};