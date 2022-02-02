#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>  
#include <vector>
#include "Directory.h"
#include "Component.h"
#include "FileTypes/ComponentFileCreator.h"
#include "FileTypes/FileType.h"
#include "FileTypes/TypeFile.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	//1. find the source folder
	fs::path workingDirectory = fs::current_path();
	const string folderToSearch = "src"; 
	fs::path sourceFolder = Directory::findFolderResults(folderToSearch, workingDirectory);
	fs::path emptyPath; 
	if(sourceFolder == emptyPath){
		std::cout << "Source folder was not found in " << fs::canonical(workingDirectory) << "\n"
				  << "Navigate to the project folder with the source folder and try again" << "\n"
		 		  << "Exiting....";
		return 1;
	}
	//2. get a list of folders in source folder
	std::vector<fs::path> sourceTopFolders = Directory::findFoldersInDir(sourceFolder, false);
	Directory::displayPathList("Folders directly under source", sourceTopFolders);

	//3. Check if folder is actually a component
	std::vector<fs::path> componentNames = Directory::getComponents(sourceFolder);
	Directory::displayPathList("Components directly under source", componentNames);
	std::vector<Component> componentList; 

	//4. Create a Component File with the list of files
	for(fs::path componentName: componentNames){
		Component component = Component(componentName);
		component.DisplayComponent();
		componentList.push_back(component); 
	}
	//5. parse some files
	for(Component component: componentList){
		std::vector<fs::path> typeFiles = component.getTypes(); 
		for(fs::path typeFile : typeFiles){
			FileType* typeFileFile = ComponentFileCreator::fileFactoryMethod("type", typeFile);
			typeFileFile->readFile();
			
		}
	}
	


	return 0;
}