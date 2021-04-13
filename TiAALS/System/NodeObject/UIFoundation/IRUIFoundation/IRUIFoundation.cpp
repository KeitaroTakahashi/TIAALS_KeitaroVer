//
//  IRUIFoundation.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 04/03/2019.
//

#include "IRUIFoundation.hpp"

IRUIFoundation::IRUIFoundation(IRNodeObject* nodeObject, IRStr* str) :
IRStrComponent(str)
{
    setOpaque(false);
    
    this->nodeObject = nodeObject;
    this->nodeObject->statusChangeCompleted = [this](IRNodeComponentStatus status){ NodeObjectStatusChanged(status); };

    // setup callback function for FileManager
    // get to know when fileManager is updated
    std::function<void(IRFileManager& )> callback = [this](IRFileManager& fileManager){ updateFileManager(fileManager); };
    getStr()->addFileManagerUpdatedCallbackFunc(callback);
    
    this->nodeObject->addListener(this);
          
}
// --------------------------------------------------
IRUIFoundation::~IRUIFoundation()
{
    
}
// --------------------------------------------------
void IRUIFoundation::IRKeyPressed(int keyCode, String keyText)
{
    std::cout << "IRUIFoundation IRKeyPressed = " << keyCode << std::endl;

}
// --------------------------------------------------
void IRUIFoundation::IRKeyReleased(int keyCode, String keyText)
{
    std::cout << "IRUIFoundation IRKeyReleased = " << keyCode << std::endl;

}
// --------------------------------------------------
bool IRUIFoundation::keyStateChanged(bool isKeyDown, Component* originatingComponent)
{
    
    // IRKeyPressed() should be callsed in keyPressed event
    if(!isKeyDown) IRKeyReleased(this->pressedKeyCode, this->pressedKeyText);
    
    return true;
}
// --------------------------------------------------

bool IRUIFoundation::keyPressed(const KeyPress &key,
                                Component* originatingComponent)
{
    
    // user defined key commands
    this->pressedKeyCode = key.getKeyCode();
    this->pressedKeyText = key.getTextDescription();
    IRKeyPressed(this->pressedKeyCode, this->pressedKeyText);
    //std::cout << "IRUIFoundation keyPressed = " << key.getKeyCode() << std::endl;
    return true;
}
// --------------------------------------------------

void IRUIFoundation::NodeObjectStatusChanged(IRNodeComponentStatus status)
{
    //std::cout << "NodeObjectStatusChanged : status = " << status << std::endl;
    
    switch (status)
    {
        case IRNodeComponentStatus::EditModeStatus:
            
            // control KeyEvent
            // editmode = does not receive any KeyEvent,
            // controlmode = receive keyEvent
            setEditModeBase(this->nodeObject->isEditMode());
            
            break;
            
        default:
            break;
    }
    
}
// --------------------------------------------------

void IRUIFoundation::setEditModeBase(bool newEditMode)
{
    
    this->editModeFlag = newEditMode;
    
    // if not editMode, get keyboardFocus
    if (! this->editModeFlag)
    {
        setWantsKeyboardFocus(true);
        addKeyListener(this);
        addKeyListener(getStr()->key);

    }
    else
    {
        // otherwise out of keyboard Focus
        setWantsKeyboardFocus(false);
        removeKeyListener(this);
        removeKeyListener(getStr()->key);

    }
    // call it for child class
    setEditMode(newEditMode);
}
// --------------------------------------------------
