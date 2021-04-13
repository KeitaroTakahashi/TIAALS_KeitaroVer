//
//  IRSaveLoadSystem.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 06/11/2018.
//

#include "IRSaveLoadSystem.hpp"

void IRSaveLoadSystem::createHeader()
{
    this->header = json11::Json::object({
        {"Project", json11::Json::object({
            {"projectName",     "IRiMaS_project1"},
            {"author",          "Keitaro Takahashi"},
            {"date",            "20.04.1986"},
            {"osType",          "macOS"},
            {"osVersion",       "10.13.6"},
            {"IRVersion",       "0.0.1"},
            {"bounds",          "10,10,1200,600"},
        })},
    });
    
    

    
}
// ----------------------------------------
void IRSaveLoadSystem::loadHeader()
{
    
    std::cout << "========== loadHeader ==========" << std::endl;
    
    json11::Json data = this->saveData["Header"]["Project"].object_items();
    
    std::cout << "author = " << data["author"].string_value() << std::endl;
    this->saveDataStr.header.author = data["author"].string_value();
    // split string by ,
    
    auto bounds = data["bounds"].array_items();

    int x = bounds[0].int_value();
    int y = bounds[1].int_value();
    int w = bounds[2].int_value();
    int h = bounds[3].int_value();
    this->saveDataStr.header.bounds = Rectangle<int>(x,y,w,h);
    
    std::cout << "bounds = " << x << "," << y << "," << w << "," << h << std::endl;


    std::cout << "date = " << data["date"].string_value() << std::endl;
    this->saveDataStr.header.date = data["date"].string_value();
    std::cout << "osType = " << data["osType"].string_value() << std::endl;
    this->saveDataStr.header.osType = data["osType"].string_value();

    std::cout << "osVersion = " << data["osVersion"].string_value() << std::endl;
    this->saveDataStr.header.osVersion = data["osVersion"].string_value();

    std::cout << "IRVersion = " << data["IRVersion"].string_value() << std::endl;
    this->saveDataStr.header.IRVersion = data["IRVersion"].string_value();

    std::cout << "projectName = " << data["projectName"].string_value() << std::endl;
    this->saveDataStr.header.projectName = data["projectName"].string_value();
    std::cout << "========== end ==========" << std::endl;

}
// ----------------------------------------
void IRSaveLoadSystem::createWorkspaces(json11::Json workspaceSaveData)
{
    
    this->saveData = json11::Json::object({
        
        {"Header", this->header},
        {"Workspaces", workspaceSaveData},
        
    });
    
}
// ----------------------------------------
void IRSaveLoadSystem::loadWorkspaces()
{
    std::cout << "========== loadWorkspaces ==========" << std::endl;

    
    for(auto it = this->saveData["Workspaces"].object_items().cbegin(); it != this->saveData["Workspaces"].object_items().cend(); ++it)
    {
        
        
        
        std::string id = static_cast<std::string>(it->first);
        
        std::cout << id << std::endl;

        json11::Json data = this->saveData["Workspaces"][id].object_items();
        
        json11::Json appearance = data["Appearance"];
        std::cout << "Appearance : backgroundColour = " << appearance["backgroundColour"].string_value() << std::endl;

        
        json11::Json Objects = data["Objects"];
        json11::Json::array objectArray = Objects.array_items();
        
        std::cout << "array count = " << objectArray.size() << std::endl;
        
        for(int i =0; i< objectArray.size(); i++)
        {
            for(auto it = objectArray[i].object_items().cbegin(); it != objectArray[i].object_items().cend(); ++it)
            {
                std::cout << " - "<< it->first << std::endl;
                
            }

        }
 
    }
    std::cout << "========== end ==========" << std::endl;
}
// ----------------------------------------
void IRSaveLoadSystem::callCreateNewProjectFromSaveData()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.createNewProjectFromSaveData(); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->createNewProjectFromSaveDataComplete != nullptr) this->createNewProjectFromSaveDataComplete();
}
// ----------------------------------------
void IRSaveLoadSystem::callCreateNewWorkspaceFromSaveData()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.createNewWorkspaceFromSaveData(); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->createNewWorkspaceFromSaveDataComplete != nullptr) this->createNewWorkspaceFromSaveDataComplete();
}
// ----------------------------------------

bool IRSaveLoadSystem::createProjectDirectory(std::string projectPath)
{
    this->projectDirectory = projectPath;
    std::string p = projectPath;
    std::string r = projectPath+this->resourceDirectory;

    // create a project directory
    createDirectoryWithPath(projectPath, "Project Directory");
    
    // create a resource directory
    createDirectoryWithPath(r, "Resources Directory");

    // create a image directory
    createDirectoryWithPath(r+this->imageDirectory, "Image Directory");
    
    // create a movie directory
    createDirectoryWithPath(r+this->movieDirectory, "Movie Directory");

    // create a document directory
    createDirectoryWithPath(r+this->documentDirectory, "Document Directory");

    // create an audio directory
    createDirectoryWithPath(r+this->audioDirectory, "Audio Directory");



    return true;
}
// ----------------------------------------
bool IRSaveLoadSystem::createDirectoryWithPath(std::string path, std::string text)
{
    File d(path);

    // check if the projectPath already exists and if so, return false.
    if(d.isDirectory()) { std::cout << text+" already exists " << path << std::endl; return false;}
    auto result = d.createDirectory();
    if(!result.wasOk()) { return false; }
    return true;
}
// ----------------------------------------

void IRSaveLoadSystem::writeSaveData(std::string filePath)
{
    std::ofstream myFile;
    // trunc mode : discard previous data and write new save data
    myFile.open(filePath, std::ofstream::trunc);
    myFile << this->saveData.dump();
    myFile.close();
    
    //std::cout << "========== save data ========== \n" << std::endl;
    //std::cout << this->saveData.dump() << std::endl;
    //std::cout << "========== end ========== \n" << std::endl;
}

// read save data from a file
void IRSaveLoadSystem::readSaveData(std::string filePath)
{
    
    //init
    this->readData.clear();
    
    std::ifstream myFile(filePath);
    
    if(!myFile){
        std::cout << "Error : Could not open file " << filePath << std::endl;
        return;
    }
    
    std::string buf;
    while (!myFile.eof())
    {
        std::getline(myFile, buf);
        this->readData += buf;
    }
    
    myFile.close();
    
    std::string err;
    this->saveData = json11::Json::parse(this->readData,err);

    std::cout << "Header" << "\n";
    
    loadHeader();

    std::cout << "Worksapce" << "\n";
  
    loadWorkspaces();
 
    for(auto it = this->saveData["Workspaces"].object_items().cbegin(); it != this->saveData["Workspaces"].object_items().cend(); ++it)
    {
        std::cout << " - " << it->first << "\n";
        
        for (auto item2 : this->saveData["Workspaces"][it->first].object_items())
        {
            std::cout << " - - " << item2.first << std::endl;
            
        }
    }
    
    for (auto item : this->saveData["Workspaces"].object_items())
    {
        std::cout << item.first << std::endl;

    }
    
    std::cout << "workspace size = " << this->saveData["Workspaces"].object_items().size() << std::endl;

}
// ----------------------------------------
