//
//  LeftBarSlideMenu.cpp
//  IRiMaS
//
//  Created by Keitaro on 17/09/2019.
//

#include "LeftBarSlideMenu.hpp"

LeftBarSlideMenu::LeftBarSlideMenu(IRStr* str) :
IRViewPort(str)
{
    this->slideMenu = std::make_shared<SlideMenu>(str);
    this->slideMenu->slideMenuUpdated = [this]{ slideMenuUpdatedAction(); };
    this->slideMenu->slideHasSelected = [this] (IRWorkspaceSlide* slide){ slideHasSelectedAction(slide); };
    this->slideMenu->addMouseListener(this, true);
    this->viewPort = std::make_shared<Component4ViewPort>(this->slideMenu.get());
        
    setViewedComponent(this->viewPort.get());
    
    this->addNewSlideButton.setButtonText("+");
    this->deleteSlideButton.setButtonText("-");
    
    

}

LeftBarSlideMenu::~LeftBarSlideMenu()
{
    
}

// ==================================================
void LeftBarSlideMenu::paint(Graphics& g)
{
    
}

void LeftBarSlideMenu::resized()
{
    this->viewPort->setBounds(0,0,getWidth()-10, getHeight());
    this->slideMenu->setBounds(0, 0, getWidth()-10, getHeight());
    
    this->viewPort->toFront(true);
}

// ==================================================

void LeftBarSlideMenu::visibleAreaChangedAction(const Rectangle<int> &newVisibleArea)
{

}
// ==================================================

void LeftBarSlideMenu::addNewWorkspaceSlide(IRWorkspace* space)
{
    this->slideMenu->addNewWorkspaceSlide(space);
}
// ==================================================

void LeftBarSlideMenu::slideMenuUpdatedAction()
{
    this->viewPort->setSize(getWidth() - 10, this->slideMenu->getHeight());
}

void LeftBarSlideMenu::slideHasSelectedAction(IRWorkspaceSlide* slide)
{
    std::cout << "LeftBarSlideMenu::slideHasSelectedAction\n";
    if(this->workspaceSelectedCallback != nullptr)
        this->workspaceSelectedCallback(slide->getWorkspace());
}


// ==================================================
void LeftBarSlideMenu::deleteSelectedWorkspaceSlide()
{
    std::cout << "LeftBarSlideMenu : deleteSelectedWorkspaceSlide() " << std::endl;
    auto willBeDeletedWs = this->slideMenu->deleteSelectedWorkspaceSlide();
    
    // inform parent object which workspace will need to be deleted in accordance of the deleted slide.
    if(this->workspaceDeleteCallback != nullptr)
        this->workspaceDeleteCallback(willBeDeletedWs);
    
}

// ==================================================
IRWorkspaceSlide* LeftBarSlideMenu::getSelectedSlide()
{
    return  this->slideMenu->getSelectedSlide();
}

// ==================================================


void LeftBarSlideMenu::moveToLowerSlide()
{
    this->slideMenu->moveToLowerSlide();
}

void LeftBarSlideMenu::moveToHigherSlide()
{
    this->slideMenu->moveToHigherSlide();
}

// ==================================================

bool LeftBarSlideMenu::reloadThumbnails()
{
    return this->slideMenu->reloadThumbnails();
}
