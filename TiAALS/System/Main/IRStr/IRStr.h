//
//  IRStr.h
//  IRiMaS
//
//  Created by Keitaro on 29/08/2019.
//

#ifndef IRStr_h
#define IRStr_h

#include "JuceHeader.h"
#include "KLib.h"
#include "ColourLib.h"
#include "IRIconBank.hpp"
#include "IRFileManager.hpp"
#include "UserSettingStr.h"
#include "IRProjectOwnerBase.h"

struct IRStr
{
    
    IRStr()
    {
        
    }
    virtual ~IRStr()
    {
        
    }
    // KeyListener from IRWIndowComponent
    KeyListener* key;
    void setKeyListener(KeyListener* key) { this->key = key; }
    
    MouseListener* mouse;
    void setMouseListener(MouseListener* mouse) { this->mouse = mouse; }
    
    // ==================================================

    String projectName;
    String projectURL;
    
    // this flag is accessible by all objects inheriting IRStrComponent.
    // it is ideal to give FALSE to isProjectSaved when user made any changes
    bool isProjectSaved = true;
    
    // store currently active workspace
    Component* TopWorkspace = nullptr;
    
    // store the project owner
    IRProjectOwnerBase* projectOwner = nullptr;
    
    // in case there is a parent str
    IRStr* parentStr = nullptr;
    // ==================================================
    // callBack
    std::vector<std::function<void(IRFileManager&)>> fileManagerUpdatedCallbackList;
        
    void addFileManagerUpdatedCallbackFunc(std::function<void(IRFileManager&)> callBack)
    {
        this->fileManagerUpdatedCallbackList.push_back(callBack);
    }
    
    void notifyFileManagerUpdate()
    {
        for(int i = 0; i < this->fileManagerUpdatedCallbackList.size(); i ++ )
        {
            this->fileManagerUpdatedCallbackList[i](FILEMANAGER);
        }
    }
    // ==================================================
    
    virtual Component* createNewObject(std::string id, Component* parent, IRStr* str)
    {
        KLib().showErrorMessage("Error : createNewObject can not be called from IRStr object but from IRMasterStr!\n");
        return nullptr;
    }
    
    // ==================================================

    // SIZE
    
    int ControlBarWidth = 270;
    
    
    // ==================================================


    void setIconBank(IRIconBank* bank) { this->ICONBANK = bank; }
    IRIconBank* getIconBank() const { return this->ICONBANK; }
    // ==================================================
    UserSettingStr USERSETTING;
    IR::IRColours SYSTEMCOLOUR;
    
    // IconBank has large size, and we need only one set in a project, so IRStr holds a pointer of it.
    IRIconBank* ICONBANK;

    IRFileManager FILEMANAGER;

    // ==================================================
    // load and store here as it costs time
    StringArray fontFamilyList;

};

#endif /* IRStr_h */
