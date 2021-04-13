//
//  IRWorkspaceController.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 12/03/2021.
//

#include "IRWorkspaceController.hpp"

IRWorkspaceController::IRWorkspaceController(IRStr* str) : IRObjectController("Workspace", str)
{
    this->UI.reset(new IRWorkspaceControllerUI(str) );
    addAndMakeVisible(this->UI.get());
    this->UI->addChangeListener(this);
}

IRWorkspaceController::~IRWorkspaceController()
{
    this->UI.reset();
}

// ==================================================

void IRWorkspaceController::controllerChangeListenerCallback (ChangeBroadcaster* source)
{
    if(source == this->UI.get())
    {
        UIChangeListener();
    }
}

void IRWorkspaceController::UIChangeListener()
{
    auto status = this->UI->getStatus();
    
    switch(status)
    {
        case IRWorkspaceControllerUI::TITLE:
            this->status = TITLE;
            sendChangeMessage();
            break;
        case IRWorkspaceControllerUI::ASPECT_RATIO:
            this->status = ASPECT_RATIO;
            sendChangeMessage();
            break;
        case IRWorkspaceControllerUI::WIDTH:
            break;
        case IRWorkspaceControllerUI::HEIGHT:
            break;
        case IRWorkspaceControllerUI::X:
            this->status = ASPECT_RATIO;
            break;
        case IRWorkspaceControllerUI::Y:
            this->status = ASPECT_RATIO;
            break;
        default:
            break;
    }
    
    sendChangeMessage();
}

// ==================================================

void IRWorkspaceController::paint(Graphics& g)
{
    
    
    
}


void IRWorkspaceController::ControllerResized()
{
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 30;

    y += yBigIncrement;
    y += yIncrement;
    
    this->UI->setBounds(0, y, getWidth(), getHeight() - y);
    
}

// ==================================================

void IRWorkspaceController::aspectRatioChangedAction(Rectangle<int> aspect)
{
    
}

void IRWorkspaceController::titleChangedAction(String title)
{
    
}
// ==================================================
String IRWorkspaceController::getTitle() const
{
    return this->UI->getTitleText();
}
Rectangle<int> IRWorkspaceController::getInitialBounds() const
{
    return this->UI->getInitialBounds();
}

void IRWorkspaceController::setInitialBounds(int x, int y, int w, int h)
{
    this->UI->setInitialBounds(x, y, w, h);
}

void IRWorkspaceController::setInitialBounds(Rectangle<int> bounds)
{
    this->UI->setInitialBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
}


