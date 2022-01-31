#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>  
#include <vector>
#include "Directory.h"
#include "ComponentFile.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	//1. find the source folder
	fs::path pathToShow = fs::current_path();
	const string folderToSearch = "src"; 
	fs::path sourceFolder = Directory::foundFolderResults(folderToSearch, pathToShow);
	
	//2. get a list of folders in source folder
	std::vector<fs::path> sourceTopFolders = Directory::findFoldersInDir(sourceFolder, false);
	Directory::displayPathList("Folders directly under source", sourceTopFolders);

	//3. Check if folder is actually a component
	std::vector<fs::path> components = Directory::getComponents(sourceFolder);
	Directory::displayPathList("Components directly under source", components);
	std::vector<ComponentFile> componentFiles; 

	//4. Create a Component File with the list of files
	for(fs::path component: components){
		ComponentFile componentFile = ComponentFile(component);
		componentFile.DisplayComponent();
		componentFiles.push_back(componentFile); 
	}
	


	return 0;
}