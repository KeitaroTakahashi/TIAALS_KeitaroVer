//
//  IRSimpleController.cpp
//  IRiMaS
//
//  Created by Keitaro on 23/07/2019.
//

#include "IRSimpleController.hpp"


IRSimpleController::IRSimpleController()
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

IRSimpleController::~IRSimpleController()
{
    
    
}

// ==================================================

void IRSimpleController::resized()
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
void IRSimpleController::paint(Graphics& g)
{
    g.setColour(SYSTEMCOLOUR.contents);
    g.setOpacity(0.6);
    g.fillRect(getLocalBounds());}

// ==================================================
void IRSimpleController::addAllComponent()
{
    removeAllChildren();
    if(this->isZoomIn) addAndMakeVisible(&this->zoomInButton);
    if(this->isZoomOut) addAndMakeVisible(&this->zoomOutButton);
    if(this->isMovable) addAndMakeVisible(&this->movableButton);
    if(this->isComment) addAndMakeVisible(&this->commentButton);
    if(this->isBezier) addAndMakeVisible(&this->bezierButton);

}

// ==================================================

void IRSimpleController::zoomInClicked()
{
    
}

void IRSimpleController::zoomOutClicked()
{
    
}

void IRSimpleController::commentClicked()
{
    
}

void IRSimpleController::bezierClicked()
{
    
}
// ==================================================

void IRSimpleController::setZoomInEvent(std::function<void()> callBack)
{
    this->zoomInButton.onClick = callBack;
}
// --------------------------------------------------
void IRSimpleController::setZoomOutEvent(std::function<void()> callBack)
{
    this->zoomOutButton.onClick = callBack;
}

void IRSimpleController::setCommentEvent(std::function<void()> callBack)
{
    this->commentButton.onClick = callBack;
}

void IRSimpleController::setBezierEvent(std::function<void(IRAutomation::lineStatus)> callBack)
{
    this->bezierButton.statusClicked = callBack;
}

// --------------------------------------------------
void IRSimpleController::setMovableEvent(std::function<void(IRAutomation::movableStatus)> callBack)
{
    this->movableButton.statusClicked = callBack;
}


// ==================================================

void IRSimpleController::setMovableStatus(IRAutomation::movableStatus status)
{
    this->movableButton.setMovableStatus(status);
}

void IRSimpleController::setup(bool isZoomIn,
                               bool isZoomOut,
                               bool isMovable,
                               bool isComment,
                               bool isBezier)

{
    isZoomIn = isZoomIn;
    isZoomOut = isZoomOut;
    isMovable = isMovable;
    isComment = isComment;
    isBezier = isBezier;
    
    addAllComponent();
}
