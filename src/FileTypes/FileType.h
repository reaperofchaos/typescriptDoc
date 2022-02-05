#ifndef FILE_TYPE_INCLUDED
#define FILE_TYPE_INCLUDED
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileType{
    public:
    fs::path file; 
    std::string filename; 
    std::ifstream in; 
    std::vector<std::string> lines; 
    std::string fileType;

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
    virtual void displayType(){};
    virtual void findImports(){};
    virtual void findInterface(){};
    virtual void displayInterfaces(){};
};
#endif