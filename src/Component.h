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

class Component{
    std::string componentName;
    std::vector<fs::path> componentFiles;
    std::vector<fs::path> reducerFiles;
    std::vector<fs::path> sagaFiles;
    std::vector<fs::path> selectorFiles;
    std::vector<fs::path> typeFiles;

    public: 
        /**
         * @brief Construct a new Component object
         * 
         */
        Component(){}

        /**
         * @brief Construct a new Component object
         * 
         * @param component a path
         */
        Component(fs::path component){
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

        /**
         * @brief Get the Components object
         * 
         * @return std::vector<fs::path> 
         */
        std::vector<fs::path> getComponents(){return this->componentFiles;}
        /**
         * @brief Get the Types object
         * 
         * @return std::vector<fs::path> 
         */
        std::vector<fs::path> getTypes(){return this->typeFiles;}
        /**
         * @brief Get the Reducers object
         * 
         * @return std::vector<fs::path> 
         */
        std::vector<fs::path> getReducers(){return this->reducerFiles;}
        /**
         * @brief Get the Selectors object
         * 
         * @return std::vector<fs::path> 
         */
        std::vector<fs::path> getSelectors(){return this->selectorFiles;}
        /**
         * @brief Get the Sagas object
         * 
         * @return std::vector<fs::path> 
         */
        std::vector<fs::path> getSagas(){return this->sagaFiles;}

        /**
         * @brief Prints console output for the contents of the component
         * 
         */
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