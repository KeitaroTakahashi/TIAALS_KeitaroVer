//
//  IRProjectWindow2.cpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#include "IRProjectWindow2.hpp"

IRProjectWindow2::IRProjectWindow2(String name, Rectangle<int> frameRect) : IRMainWindow(name)
{
    
    //Rectangle<int> frameRect (10, 10, 1280, 800);
    this->comp.reset(new IRWindowComponent(name, frameRect));
    this->comp->setSize(frameRect.getWidth(), frameRect.getHeight());
    this->comp->windowMoveAction = [this](juce::Point<int>pos) { windowMoveToPos(pos); };
    this->comp->newProjectCallback = [this] { newProjectCallbackAction(); };
    this->comp->closeProjectCallback = [this]{ closeButtonPressed(); };
    this->comp->openProjectCallback = [this] { openProjectCallbackAction(); };
    
    std::cout << "projectTitle = " << name << std::endl;
    this->comp->projectTitle = name;

    setContentOwned (this->comp.get(), true);
    
#if JUCE_IOS || JUCE_ANDROID
    setFullScreen (true);
#else
    setResizable (true, true);
    centreWithSize (getWidth(), getHeight());
#endif
    
    setVisible (true);
}

IRProjectWindow2::~IRProjectWindow2()
{
    this->comp.reset();
}

// ==================================================
void IRProjectWindow2::createInitialWorkspace()
{
    if(this->comp.get() != nullptr)
    {
        this->comp->createNewWorkspace();
    }
}

void IRProjectWindow2::initializeUI()
{
    if(this->comp.get() != nullptr)
    {
        this->comp->initializeUI();
    }
}
// ==================================================

void IRProjectWindow2::changeListenerCallback (ChangeBroadcaster* source)
{
  
}
// ==================================================

void IRProjectWindow2::closeButtonPressed()
{
    
    std::cout << "IRProjectWindow2::closeButtonPressed\n";
    callCloseThisWindow();
}
// ==================================================


void IRProjectWindow2::windowMoveToPos(juce::Point<int>pos)
{
    setTopLeftPosition(pos);
}
// ==================================================

void IRProjectWindow2::callCloseThisWindow()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.closeThisWindow(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

// ==================================================

void IRProjectWindow2::setNewProjectCallbackFunc(std::function<void()> callback)
{
    this->newProjectCallback = callback;
}

void IRProjectWindow2::setOpenProjectCallbackFunc(std::function<void()> callback)
{
    this->openProjectCallback = callback;
}

void IRProjectWindow2::newProjectCallbackAction()
{
    if(this->newProjectCallback != nullptr)
        this->newProjectCallback();
}

void IRProjectWindow2::openProjectCallbackAction()
{
    
    if(this->openProjectCallback != nullptr)
        this->openProjectCallback();
}


// ==================================================

void IRProjectWindow2::loadProjectFromSaveData(t_json saveData)
{
    this->comp->loadProjectFromSavedData(saveData);
}

void IRProjectWindow2::setProjectTitle(String title)
{
    this->comp->setProjectTitle(title);
}

void IRProjectWindow2::setProjectPath(String path)
{
    this->comp->projectPath = path;
}
