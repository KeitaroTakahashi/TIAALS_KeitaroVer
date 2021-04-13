//
//  WorkspaceSlideComponent.cpp
//  IRIMAS2020July - App
//
//  Created by Keitaro on 14/09/2020.
//

#include "WorkspaceSlideComponent.hpp"

WorkspaceSlideComponent::WorkspaceSlideComponent(IRStr* str, Rectangle<int> frameRect) :
ObjectMenuComponent(str, frameRect),
IRThread("WorkspaceSlideComponent Thread")
{
    //setTitleText("Graphics");
    
    this->slideMenu.reset( new LeftBarSlideMenu(str) );
    this->slideMenu->workspaceSelectedCallback = [this](IRWorkspace* space) { workspaceSelectedAction(space); };
    this->slideMenu->workspaceDeleteCallback = [this](IRWorkspace* space) { workspaceDeleteAction(space); };

    addAndMakeVisible(this->slideMenu.get());
    
    setFps(33);
}

WorkspaceSlideComponent::~WorkspaceSlideComponent()
{
    stopAnimation();
}


// ==================================================
void WorkspaceSlideComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

void WorkspaceSlideComponent::resized()
{
    //ObjectMenuComponent::resized();
    
    this->slideMenu->setBounds(getLocalBounds());
    
}
// ==================================================

void WorkspaceSlideComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}

void WorkspaceSlideComponent::itemReleased(IRObjectFactory2::t_object* obj)
{
    
    
}


void WorkspaceSlideComponent::menuCtlButtonClicked()
{
    this->slideMenu->deleteSelectedWorkspaceSlide();
}

// ==================================================

void WorkspaceSlideComponent::addNewWorkspaceSlide(IRWorkspace* space)
{
    
    std::cout << "WorkspaceSlideComponent::addNewWorkspaceSlide : " << space << " : " << this->slideMenu.get() << std::endl;
    
    this->slideMenu->addNewWorkspaceSlide(space);
    
    //updateWorkspaceThumbnail();
}

void WorkspaceSlideComponent::updateWorkspaceThumbnail()
{
    this->startTime = Time::getMillisecondCounter();
    
    std::cout << "updateWorkspaceThumbnail\n";
    startAnimation();
    // wake up background thread
    startThreadTask();
}

void WorkspaceSlideComponent::task()
{
    createThumbnail();
}

void WorkspaceSlideComponent::createThumbnail()
{
    auto w = getStr()->TopWorkspace;
    if(w != nullptr){
        int index = static_cast<IRWorkspaceComponent*>(w)->getIndex();
        //this->exportScreenshotCompleted = [this]{ thumbnailExportCompleteAction(); };
        
       
    }else{
        //std::cout << "Error : failed to create Thumbnail of the workspace " << w << std::endl;
    }
    
    // terminate thread process
    exitThread();
    
}

// ==================================================

void WorkspaceSlideComponent::updateAnimationFrame()
{
    if(this->completedFlag)
    {
        this->slideMenu->reloadThumbnails();
        this->completedFlag = false;
        
        stopAnimation();
    }

}
// ==================================================

void WorkspaceSlideComponent::workspaceSelectedAction(IRWorkspace* space)
{
    if(this->workspaceSelectedCallback != nullptr)
        this->workspaceSelectedCallback(space);
}

void WorkspaceSlideComponent::workspaceDeleteAction(IRWorkspace* space)
{
    if(this->workspaceDeleteCallback != nullptr)
        this->workspaceDeleteCallback(space);
}
