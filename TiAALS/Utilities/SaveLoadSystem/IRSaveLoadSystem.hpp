//
//  IRSaveLoadSystem.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 06/11/2018.
//

#ifndef IRSaveLoadSystem_hpp
#define IRSaveLoadSystem_hpp

#include <stdio.h>
#include <fstream>
#include "JuceHeader.h"
#include "KLib.h"
#include "json11.hpp"

typedef json11::Json t_json;

class IRSaveLoadSystem: public Component
{
public:
    
    struct headerStr
    {
        std::string author;
        Rectangle<int> bounds;
        std::string date;
        std::string osType;
        std::string osVersion;
        std::string IRVersion;

        std::string projectName;
    };

    struct dataStr
    {
        headerStr header;
    };
    
    
    IRSaveLoadSystem()
    {
        
    }
    
    ~IRSaveLoadSystem()
    {
        
    }
    // ========================================
    
    // create header of the save data including project information
    void createHeader();
    // load header
    void loadHeader();
    
    // create workspaces save data
    void createWorkspaces(json11::Json workspaceSaveData);
    // load workspaces
    void loadWorkspaces();
    
    // create all necessary project directories
    bool createProjectDirectory(std::string projectPath);
    bool createDirectoryWithPath(std::string path, std::string text);
    // ========================================
    // export save data into a file
    void writeSaveData(std::string filePath);
    
    
    // read save data from a file
    void readSaveData(std::string filePath);
    
    // ========================================
    json11::Json getSaveData() const
    {
        return this->saveData;
    }
    
    dataStr getSaveDataStr() const
    {
        return this->saveDataStr;
    }
    
    void setHeader(json11::Json newHeader)
    {
        this->header = newHeader;
    }
    // ========================================
    // Listener
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void createNewProjectFromSaveData();
        virtual void createNewWorkspaceFromSaveData();
    };
    
    virtual void addListener(Listener* newListener) { this->listeners.add(newListener); }
    virtual void removeListener(Listener* listener) { this->listeners.remove(listener);}
    
    ListenerList<Listener> listeners;
    
    std::function<void()> createNewProjectFromSaveDataComplete;
    std::function<void()> createNewWorkspaceFromSaveDataComplete;

    // fire createNewProjectFromSaveData() method in the listener
    void callCreateNewProjectFromSaveData();
    // fire
    void callCreateNewWorkspaceFromSaveData();
    
    
private:
    
    std::string fileName;
    
    json11::Json header;
    
    json11::Json saveData;
    std::string readData;
    
    dataStr saveDataStr;
    
    // --------------------------------------------------
    
    std::string projectDirectory;
    std::string imageDirectory = "/images";
    std::string movieDirectory = "/movies";
    std::string documentDirectory = "/documents";
    std::string audioDirectory = "/audio";
    std::string resourceDirectory = "/Resources";

};


#endif /* IRSaveLoadSystem_hpp */




