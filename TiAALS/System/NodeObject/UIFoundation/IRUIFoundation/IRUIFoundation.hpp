//
//  IRUIFoundation.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 04/03/2019.
//

#ifndef IRUIFoundation_hpp
#define IRUIFoundation_hpp

#include "JuceHeader.h"
#include "IRNodeObject.hpp"
#include "IRFileManager.hpp"
#include "IRIconBank.hpp"
#include "UserSettingStr.h"
#include "IRPath.h"



class IRUIFoundation : public Component,
public IRStrComponent,
public KeyListener,
private IRNodeObject::Listener
{
public:
    IRUIFoundation(IRNodeObject* nodeObject, IRStr* str);
    ~IRUIFoundation();
    
    // --------------------------------------------------
    // ==================================================
    // key events

    virtual void IRKeyPressed(int keyCode, String keyText);
    virtual void IRKeyReleased(int keyCode, String keyText);
    
    // ==================================================
    // status change
    
    virtual void setEditMode(bool newEditMode) {};
    // --------------------------------------------------

    // --------------------------------------------------
    // ==================================================
    // when file manager of this Object is updated, then all objects of IRUIFoundation
    // will share the file manger automatically.
    virtual void updateFileManager(IRFileManager& fileManager) {}
    // callback informing fileManager changes
    //std::function<void(IRFileManager*)> fileManagerUpdated;
    
    void setFileManagerUpdateCallback(std::function<void(IRFileManager&)> callback);
    
    IRFileManager& getFileManager() { return getStr()->FILEMANAGER; }
    // ==================================================
    // object
    IRNodeObject* nodeObject;
    // --------------------------------------------------
    
private:
    bool keyStateChanged(bool isKeyDown, Component* originatingComponent) override;
    bool keyPressed(const KeyPress &key,
                    Component* originatingComponent) override;
    // ==================================================
    // get signal from IRNodeComponent when IRNodeObject status changed.
    void NodeObjectStatusChanged(IRNodeComponentStatus status);

    // --------------------------------------------------
    

    // --------------------------------------------------
    // for this class
    void setEditModeBase(bool newEditMode);
    
    // ==================================================

private:
    
    //key event
    int pressedKeyCode;
    String pressedKeyText;
    
    // status
    bool editModeFlag = true;

    
};

#endif /* IRUIFoundation_hpp */
