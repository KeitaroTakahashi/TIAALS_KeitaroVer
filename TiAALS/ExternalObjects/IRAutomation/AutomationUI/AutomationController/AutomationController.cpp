//
//  AutomationController.cpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#include "AutomationController.hpp"

AutomationController::AutomationController(IRStr* str) : IRStrComponent(str)
{
    this->zoomInButton.setImage(this->ImageBank.getZoomIn().white);
    addAndMakeVisible(&this->zoomInButton);
    this->zoomInButton.onClick = [this] {zoomInClicked(); };
    
    this->zoomOutButton.setImage(this->ImageBank.getZoomOut().white);
    addAndMakeVisible(&this->zoomOutButton);
    this->zoomOutButton.onClick = [this] {zoomOutClicked(); };
    
    addAndMakeVisible(&this->movableButton);
    
    this->commentButton.setImage(this->ImageBank.getComment().white);
    this->commentButton.onClick = [this] { commentClicked(); };
    addAndMakeVisible(&this->commentButton);
    
    //this->bezierButton.setImage(this->ImageBank.getBezier().white);
    //this->bezierButton.onClick = [this] { bezierClicked(); };
    addAndMakeVisible(&this->bezierButton);
    
    
}

AutomationController::~AutomationController()
{
    
}

// ==================================================

void AutomationController::resized()
{
    int x = this->buttonInterval;
    int y = 0;
    int s = getHeight();
    if(s > 100) s = 100;
    
    this->zoomInButton.setBounds(x, y, s, s);
    this->zoomOutButton.setBounds((x * 2) + s, y, s, s);
    this->movableButton.setBounds((x * 3) + (s * 2), y, s, s);
    this->commentButton.setBounds((x * 4) + (s * 3), y, s, s);
    this->bezierButton.setBounds((x * 5) + (s * 4), y, s, s);

    
}
void AutomationController::paint(Graphics& g)
{
    g.setColour(getStr()->SYSTEMCOLOUR.contents);
    g.setOpacity(0.6);
    g.fillRect(getLocalBounds());}

// ==================================================

void AutomationController::zoomInClicked()
{
    
}

void AutomationController::zoomOutClicked()
{
    
}

void AutomationController::commentClicked()
{
    
}

void AutomationController::bezierClicked()
{
    
}
// ==================================================

void AutomationController::setZoomInEvent(std::function<void()> callBack)
{
    this->zoomInButton.onClick = callBack;
}
// --------------------------------------------------
void AutomationController::setZoomOutEvent(std::function<void()> callBack)
{
    this->zoomOutButton.onClick = callBack;
}

void AutomationController::setCommentEvent(std::function<void()> callBack)
{
    this->commentButton.onClick = callBack;
}

void AutomationController::setBezierEvent(std::function<void(IRAutomation::lineStatus)> callBack)
{
    this->bezierButton.statusClicked = callBack;
}

// --------------------------------------------------
void AutomationController::setMovableEvent(std::function<void(IRAutomation::movableStatus)> callBack)
{
    this->movableButton.statusClicked = callBack;
}


// ==================================================

void AutomationController::setMovableStatus(IRAutomation::movableStatus status)
{
    this->movableButton.setMovableStatus(status);
}
