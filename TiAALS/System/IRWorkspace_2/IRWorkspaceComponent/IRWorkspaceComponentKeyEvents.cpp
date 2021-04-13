//
//  IRWorkspaceComponentKeyEvents.cpp
//  IRiMaS
//
//  Created by Keitaro on 18/09/2019.
//

#include "IRWorkspaceComponent.hpp"

//bool IRWorkspaceComponent::keyPressed (const KeyPress& key)
bool IRWorkspaceComponent::keyPressed (const KeyPress& key, Component* originatingComponent)
{
    // for some reason, the workspace bihind the topworkspace doesnt give up receiving keyboard event...
    
    std::cout << "IRWorkspaceComponent " << this << " of " << getIndex() << " : keyPressed() of " << this->name << " : " << key.getKeyCode() << " : " << key.getTextDescription() << ", " << key.getTextCharacter() <<   std::endl;
    
  // delete key
    if(key.getKeyCode() == key.deleteKey || key.getKeyCode() == key.backspaceKey)
    {
        
        commandDeleteAction();
        return true;
    }
    
    if(key.getTextDescription() == "command + C")
    {
        commandCAction();
        return true;
    }
    
    if(key.getTextDescription() == "command + V")
    {
        commandVAction();
        return true;
    }
    
    if(key.getTextDescription() == "command + D")
    {
        commandDAction();
        return true;
    }
    
    //create objects
    if(key.getTextDescription() == "command + 1")
    {
        command1Pressed();
        return true;
    }
    
    //text
    if(key.getTextDescription() == "command + 2")
    {
        command2Pressed();
        return true;
    }
    
    //text
    if(key.getTextDescription() == "command + 3")
    {
        command3Pressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + 4")
    {
        command4Pressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + 5")
    {
        command5Pressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + 6")
    {
        command6Pressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + 7")
    {
        command7Pressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + 8")
    {
        command8Pressed();
        return true;
    }
    
    if(key.getTextDescription() == "command + 9")
    {
        command9Pressed();
        return true;
    }
    

    return false;
}



// ==================================================


void IRWorkspaceComponent::registerKeyListener(KeyListener* key)
{
    addKeyListener(key);
}
void IRWorkspaceComponent::registerMouseListener(MouseListener* mouse)
{
    addMouseListener(mouse, false);
}

void IRWorkspaceComponent::command1Pressed()
{
    
}
void IRWorkspaceComponent::command2Pressed()
{
    
}
void IRWorkspaceComponent::command3Pressed()
{
    
}
void IRWorkspaceComponent::commandCAction()
{
    if(this->isAskBeforeCopyObjectByKeyCommand)
    {
        if(!KLib().showOKCancelMessage(this->copyObjectMessage)) return;
    }
    if(this->isEditMode())
    {
        copySelectedObjects();
    }
}
void IRWorkspaceComponent::commandVAction()
{
    if(this->isAskBeforePasteObjectByKeyCommand)
    {
        if(!KLib().showOKCancelMessage(this->pasteObjectMessage)) return;
    }
    if(this->isEditMode())
    {
        pasteSelectedObjects();
    }
}
void IRWorkspaceComponent::commandDAction()
{
    if(this->isAskBeforeDuplicateByKeyCommand)
    {
        if(!KLib().showOKCancelMessage(this->duplicateObjectMessage)) return;
    }
    if(this->isEditMode())
    {
        duplicateSelectedObjects();
    }
}
void IRWorkspaceComponent::commandDeleteAction()
{
    if(this->isAskBeforeDeleteObjectByKeyCommand)
    {
        if(!KLib().showOKCancelMessage(this->deleteObjectMessage)) return;
    }
    
    if(isEditMode()) deleteSelectedObjects();

}
