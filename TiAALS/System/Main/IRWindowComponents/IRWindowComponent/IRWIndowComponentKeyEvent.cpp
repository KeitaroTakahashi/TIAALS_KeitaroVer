//
//  IRWIndowComponentKeyEvent.cpp
//  IRiMaS
//
//  Created by Keitaro on 15/11/2019.
//

#include "IRWindowComponent.hpp"

void IRWindowComponent::DeleteKeyPressed()
{
    
}

void IRWindowComponent::CommandEPressed()
{

     setEditMode(!this->isEditMode());

}

void IRWindowComponent::CommandSPressed()
{
    saveProject();
    
}

void IRWindowComponent::giveKeyFocusOnTopWorkspace()
{
    
    this->leftBar->setWantsKeyboardFocus(false);

    if(this->mainSpace.get() != nullptr)
    {
        this->mainSpace->giveKeyboardFocusOnTopWorkspace();
    }
}


bool IRWindowComponent::CommandShiftNumber(const KeyPress& key)
{
    String base = "shift + command + ";
    
    if(this->mainSpace.get() == nullptr) return false;
    
    if(base + "cursor up" == key.getTextDescription())
    {
        std::cout << "go next page\n";
        this->mainSpace->moveToHigherWorkspace();
        giveKeyFocusOnTopWorkspace();
        return true;
    }else if(base + "cursor down" == key.getTextDescription())
    {
        std::cout << "go back page\n";
        this->mainSpace->moveToLowerWorkspace();
        giveKeyFocusOnTopWorkspace();
        return true;
    }
    return false;
}

