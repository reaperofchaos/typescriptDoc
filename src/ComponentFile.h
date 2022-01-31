#ifndef COMPONENT_FILE_INCLUDED
#define COMPONENT_FILE_INCLUDED
#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>  
#include <vector>
#include <algorithm>
#include "Directory.h"

namespace fs = std::filesystem;

class ComponentFile{
    std::string componentName;
    std::vector<fs::path> componentFiles;
    std::vector<fs::path> reducerFiles;
    std::vector<fs::path> sagaFiles;
    std::vector<fs::path> selectorFiles;
    std::vector<fs::path> typeFiles;

    public: 
        ComponentFile(){}
        ComponentFile(fs::path component){
            componentName = component.stem();

            std::vector<fs::path> foldersInComponent = Directory::findFoldersInDir(component, false);
            for(fs::path folderInComponent: foldersInComponent){

                //5. get file names of components
                if(folderInComponent.stem() == "components"){
                    this->componentFiles = Directory::findFilesOfTypeInDir(folderInComponent, false,  ".tsx");
                }

                //6. get file names of type files
                if(folderInComponent.stem() == "types"){
                    this->typeFiles = Directory::findFilesOfTypeInDir(folderInComponent, false,  ".ts");
                }
                //7. get file names of reducers
                if(folderInComponent.stem() == "reducers"){
                    this->reducerFiles = Directory::findFilesOfTypeInDir(folderInComponent, false,  ".ts");
                }
                //8. get file names of sagas
                if(folderInComponent.stem() == "sagas"){
                    this->sagaFiles = Directory::findFilesOfTypeInDir(folderInComponent, false,  ".ts");
                }
                //8. get file names of selectors
                if(folderInComponent.stem() == "selectors"){
                    this->selectorFiles = Directory::findFilesOfTypeInDir(folderInComponent, false,  ".ts");
                }
            }
        }

        void DisplayComponent(){
            std::cout << "Component: " << this->componentName << "\n"; 
            Directory::displayPathList("\tComponent Files", this->componentFiles);
            Directory::displayPathList("\tType Files", this->typeFiles);
            Directory::displayPathList("\tReducers Files", this->reducerFiles);
            Directory::displayPathList("\tSelectors Files", this->selectorFiles);
            Directory::displayPathList("\tSagas Files", this->sagaFiles);
        }
    };
#endif