//
//  IRLeftBarKeyEvents.cpp
//  IRiMaS
//
//  Created by Keitaro on 29/01/2020.
//

#include "IRLeftBar.hpp"

void IRLeftBar::deleteKeyPressed()
{
    
    IRWorkspace* space = this->slideMenuComponent->getSelectedSlide()->getWorkspace();
    
    workspaceDeleteAction(space);
    
    this->slideMenuComponent->deleteSelectedWorkspaceSlide();

}

void IRLeftBar::commandNKeyPressed()
{
    
}


void IRLeftBar::upKeyPressed()
{
    std::cout << "up";
    this->slideMenuComponent->moveToLowerSlide();
}

void IRLeftBar::downKeyPressed()
{
    this->slideMenuComponent->moveToHigherSlide();
}
