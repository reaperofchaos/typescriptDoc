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
#include "../Element/FunctionType.h"

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
    std::vector<FunctionType> functions;

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
            std::regex interfaceProperty("(\\w+)(\\?{0,})\\W?:((?:\\W(?:(?:['\"]\\w?['\"])|(?:\\w+\\[?\\]?))\\W?\\|?)+)[;,]+");
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
                        std::string propertyOptional = interfacePropertyMatches[2];
                        std::string propertyValue = interfacePropertyMatches[3];
                        size_t pos = 0;
                        std::vector<std::string> propertyValues = {};
                        std::string delimiter = "|";
                        while ((pos = propertyValue.find(delimiter)) != std::string::npos) {
                            std::string prop = propertyValue.substr(0, pos);
                            propertyValues.push_back(prop);
                            propertyValue.erase(0, pos + delimiter.length());
                        }

                        propertyValues.push_back(propertyValue);
                        bool isOptional = propertyOptional == "?";
                        properties.push_back(Property(propertyName, isOptional, propertyValues));
                    }
                }
            }
        }

    virtual void findEnum(){};

    bool findEndOfFunction(std::vector<std::string> lines, int index){
        std::regex closeBracket("\\}\\W?$");
        std::smatch bracketClose;
        bool bracketCloseFound = std::regex_search(lines.at(index), bracketClose, closeBracket);
        std::regex startVariable("(const|let|var|function)");
        std::smatch variableStart; 
        int i = index; 
        if(bracketCloseFound){

            //is this the end of file
            //check if new lines are only things after
            while(i < lines.size()){
                if(lines.at(i) != "\n" || lines.at(i) != "\r\n"){
                    break; 
                }
                if(index ==lines.size() - 1 || i == lines.size() - 1){
                    return true; 
                }
                i++; 
            }

            //is there a const/let/var or start of new function
            bool variableFound = std::regex_search(lines.at(i), variableStart, startVariable);
            if(variableFound){
                return true; 
            }
            return false; 
        }
    }

    // checks if a return JSX statement exists (ie a component)
    bool findReturn(std::string line){
        std::regex startReturn("return\\W?\\(");
        std::smatch returnStart;
        return std::regex_search(line, returnStart, startReturn);
    }

    bool findEndOfReturn(std::vector<std::string> lines, int index){
        std::regex endParenthesis("\\)\\W?\\}?"); 
        std::smatch parenthesisEnd;
        std::regex endBracket("\\}"); 
        std::smatch bracketEnd;
        bool endParenthesisFound =  std::regex_search(lines.at(index), parenthesisEnd, endParenthesis);
        if(endParenthesisFound){
            int i = index; 
            bool endBracketFound =  std::regex_search(lines.at(i+1), bracketEnd, endBracket);
            if(endBracketFound){
                return true; 
            } 
            if(findEndOfFunction(lines, i)){
                    return true;
                }
        }
        return false; 
    }
    //looks for functions in file
    void parseFunction(){
        std::regex startFunction("(export)?const\\W?(\\w+)\\W?=\\W?\\((.*)\\)\\W?:?\\W?(.*)?\\W?=>\\W?\\{");
		std::smatch functionStart;
        std::string functionName = ""; 
        std::string functionArguments = ""; 
        std::string functionReturnType = "";
        bool exported = false; 
        bool inFunction = false; 
        std::string nestedFunctionBody = ""; 
        std::string functionBody = "";
        std::vector<FunctionType> nestedFunctions;
        std::vector<FunctionType> nestedFunctionFunctions;
        std::string nestedFunctionName;
        std::string nestedFunctionArguments;
        std::string nestedFunctionReturnType;
        FunctionType nestedFunction;
        std::string returnBody = ""; 
        bool isComponent = false; 
        bool inReturn = false; 
        int i = 0; 
        for(std::string line: this->lines){
            bool functionStartFound = std::regex_search(line, functionStart, startFunction);
            bool functionEndFound = findEndOfFunction(this->lines, i); 
            if(!inFunction){
                if(functionStartFound ){
                    exported = functionStart[1] == "export" ? true : false;
                    functionName = functionStart[2]; 
                    functionArguments = functionStart[3]; 
                    functionReturnType = functionStart[4]; 
                    std::cout << "Found a function " << functionName << "\n"; 
                    inFunction = true; 
                }
            }else{
                //append lines to function body
                functionBody += line;

                //append line to any nested functions
                if(nestedFunctionBody != ""){
                    nestedFunctionBody += line + "\n"; 
                }
                //if the start of a function is found, we have a nested function
                if(functionStartFound ){
                    //This is a nested function
                    nestedFunctionBody = line + "\n"; 
                    nestedFunctionName = functionStart[2]; 
                    nestedFunctionArguments = functionStart[3]; 
                    nestedFunctionReturnType = functionStart[4]; 
                    std::cout << "Found a nested function " << nestedFunctionName << " \n"; 

                }
                //check for a return function
                if(findReturn(line)){
                    std::cout << "Found a JSX return " << "\n"; 
                    isComponent = true; 
                    inReturn = true;
                }

                //check if in return function
                if(inReturn){
                    returnBody += line + "\n"; 
                    //check if end of return
                    // std::cout << "Found end of return " << (findEndOfReturn(lines, i) ? "True" : "false") << "\n"; 
                    if(findEndOfReturn(lines, i)){
                        std::cout << returnBody << "\n"; 
                        inReturn = false; 
                    }
                }
                
                //check if the end of a function is found
                if(functionEndFound){
                    //if this is the end of a function create the function type and add to functions property
                    if(nestedFunctionBody == "")
                    {
                        inFunction = false; 
                        //store function
                        this->functions.push_back(FunctionType(functionName, functionArguments, 
                        functionReturnType, functionBody, nestedFunctions));
                        //clear the variables
                        exported = false; 
                        functionName = ""; 
                        functionArguments = ""; 
                        functionBody = ""; 
                        nestedFunctionBody = ""; 
                        nestedFunctions.clear(); 
                        inFunction = false; 
                    }else{
                        //if this is the end of a nested function add to a nested function  vector
                        std::cout << nestedFunctionBody << "\n\n"; 
                        std::cout << "Found the end of nested function " << nestedFunctionName << "\n\n"; 
                        FunctionType nestedFunction = FunctionType(nestedFunctionName, nestedFunctionArguments, 
                        nestedFunctionReturnType, nestedFunctionBody, nestedFunctionFunctions);
                        nestedFunctionName = ""; 
                        nestedFunctionArguments = ""; 
                        nestedFunctionReturnType = ""; 
                        nestedFunctionBody = "";
                        nestedFunctionFunctions.clear();  
                        isComponent = false; 
                    }
                }
            }
            i++;
        }
    }

    void displayInterfaces(){
        for(InterfaceType interface : this->interfaces){
            interface.display();
        }
    }
    virtual void setReduxStore(){};
    virtual void displayEnums(){}
    virtual void displayReduxStore(){}; 
};
#endif