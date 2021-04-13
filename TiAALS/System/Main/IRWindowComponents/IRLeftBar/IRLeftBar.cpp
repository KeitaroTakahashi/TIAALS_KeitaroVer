//
//  IRLeftBar.cpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#include "IRLeftBar.hpp"


IRLeftBar::IRLeftBar(IRStr* str) : IRStrComponent(str)
{
    setFps(60);
    setOpaque(true);
        
    
    //OBJECT MENU
    this->objectMenuComponent.reset(new LeftBarObjectMenu(str,
                                                          this->buttonSize,
                                                          this->topMarge,
                                                          this->leftMarge,
                                                          this->yMarge,
                                                          this->menuSpace,
                                                          this->preferenceMaxWidth,
                                                          this->buttomSpace,
                                                          this));
    
    this->objectMenuComponent->workspaceSelectedCallback = [this](IRWorkspace* space) { workspaceSelectedAction(space); };
    this->objectMenuComponent->workspaceDeleteCallback = [this](IRWorkspace* space) {
        workspaceDeleteAction(space);
    };
    this->objectMenuComponent->addMouseListener(this, true);
    this->objectMenuComponent->addChangeListener(this);
    addAndMakeVisible(this->objectMenuComponent.get());
    addButtons();
    
    this->ordinaryWidth = this->leftMarge + this->rightMarge + this->buttonSize;
    this->maxWidth = this->leftMarge + this->rightMarge + this->buttonSize + this->menuSpace;
    
    //key
    setWantsKeyboardFocus(true);
    addKeyListener(this);

}

IRLeftBar::~IRLeftBar()
{
    this->objectMenuComponent.reset();
}

//==================================================

void IRLeftBar::resized()
{
    int s = this->buttonSize;
    int y = 0; //this->topMarge;
    this->objectMenuComponent->setBounds(0, y,
                                         this->ordinaryWidth,
                                         getHeight() - y);
   
}

void IRLeftBar::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
  

}

//==================================================

void IRLeftBar::mouseDrag(const MouseEvent& e)
{
    this->currentPos = e.getScreenPosition();

    if(this->isMovable)
    {
       juce::Point<int>delta = this->currentPos - this->prevPos;
        // We need to subtract 1 to fix the gap between view position and window position!!
        this->pos.setX(getScreenX() + delta.getX());
        this->pos.setY(getScreenY() + delta.getY() - getY());
        this->status = MoveWindow;
        sendChangeMessage();
        this->prevPos = e.getScreenPosition();
    }
    
    
}

void IRLeftBar::mouseUp(const MouseEvent& e)
{
    
}

void IRLeftBar::mouseDown(const MouseEvent& e)
{
    std::cout << "IRLeftBar mouseDown\n";
        
    auto pos = e.getScreenPosition();
    this->prevPos = pos;
    checkResizableFromMouseDownPosition(pos);
    
    
    toFront(true);
}

void IRLeftBar::mouseMove(const MouseEvent& e)
{
    
}


//==================================================
void IRLeftBar::checkResizableFromMouseDownPosition(juce::Point<int> pos)
{
    
}

//==================================================

// ==================================================

void IRLeftBar::createButton(IRImageButton* button, IRIconBank::IRIconImage img)
{
    if(getStr()->SYSTEMCOLOUR.isWhiteBased)
        button->setImage(img.black);
    else button->setImage(img.white);
    
    addAndMakeVisible(button);
}

void IRLeftBar::addButtons()
{
   
}

// ==================================================

void IRLeftBar::toNavigatorAction(bool notify)
{
    // close object menu
    this->objectMenuComponent->closeObjectMenu();
    this->objectMenuComponent->toNavigatorAction();
}

void IRLeftBar::toObjectMenuAction(bool notify)
{
    //if(notify) this->objectSlideSwitchButton->switchToNavigatorButton();
    this->objectMenuComponent->toObjectMenuAction();
    
    //removeChildComponent(this->slideMenuComponent.get());
    addAndMakeVisible(this->objectMenuComponent.get());
}

// ==================================================

// ==================================================

void IRLeftBar::changeListenerCallback (ChangeBroadcaster* source)
{
    
}


// ==================================================

void IRLeftBar::addNewWorkspaceSlide(IRWorkspace* space)
{
    //this->slideMenuComponent->addNewWorkspaceSlide(space);
    this->objectMenuComponent->addNewWorkspaceSlide(space);
    // switch to slide emenu
    //toNavigatorAction(true);
}

// ==================================================
void IRLeftBar::workspaceSelectedAction(IRWorkspace* space)
{
    std::cout <<"IRLeftBar::workspaceSelectedAction\n";
    if(this->workspaceSelectedCallback != nullptr)
        this->workspaceSelectedCallback(space);
}

void IRLeftBar::workspaceDeleteAction(IRWorkspace* space)
{
    
    if(this->workspaceDeleteCallback != nullptr)
        this->workspaceDeleteCallback(space);
    

}

// ==================================================

void IRLeftBar::closeObjectMenu()
{
    this->objectMenuComponent->closeObjectMenu();
}

void IRLeftBar::attachObjectMenu()
{
    
}

void IRLeftBar::removeObjectMenu()
{
    
}

void IRLeftBar::attachPreferenceMenu()
{
    
}

void IRLeftBar::removePreferenceMenu()
{
    
}
// ==================================================


bool IRLeftBar::keyPressed(const KeyPress& key, Component* originatingComponent)
{
    std::cout << "IRLeftBar keyPressed() : " << key.getKeyCode() << " : " << key.getTextDescription() << ", " << key.getTextCharacter() <<   std::endl;
    
    if(key.getKeyCode() == key.deleteKey || key.getKeyCode() == key.backspaceKey)
    {
        deleteKeyPressed();
        return true;
    }
    
    else if(key.getTextDescription() == "command + N")
    {
        commandNKeyPressed();
        return true;
    }
    
    else if(key.getKeyCode() == key.upKey)
    {
        upKeyPressed();
        return true;
    }
    
    else if(key.getKeyCode() == key.downKey)
    {
        downKeyPressed();
        return true;
    }

    
    return false;
}
// ==================================================

bool IRLeftBar::reloadThumbnails()
{
    if(this->slideMenuComponent.get() != nullptr)
    {
        //return this->slideMenuComponent->reloadThumbnails();
        return true;
    }else return false;
}
