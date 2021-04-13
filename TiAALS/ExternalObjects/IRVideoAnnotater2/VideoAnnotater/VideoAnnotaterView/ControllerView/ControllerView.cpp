//
//  ControllerView.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#include "ControllerView.hpp"

ControllerView::ControllerView(IRStr* str) : IRStrComponent(str)
{
    /*
    this->controller.reset( new VideoAnnotaterWindowController(str) );
    this->controller->getVideoAnnotaterController()->addChangeListener(this);
    addAndMakeVisible(this->controller.get());
     */
}

ControllerView::~ControllerView()
{
    
}

// ==================================================

void ControllerView::changeListenerCallback(ChangeBroadcaster* source)
{
   
}
// ==================================================

void ControllerView::resized()
{
    if(this->controller != nullptr)
        this->controller->setBounds(getLocalBounds());
}

void ControllerView::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.drawText("controller view", getLocalBounds(), Justification::centred);
}
// ==================================================
void ControllerView::setController(IRObjectController* ctl)
{
    if(this->controller != nullptr)
    {
        removeController();
    }
    
    addController(ctl);
}

// ==================================================

void ControllerView::removeController()
{
    removeChildComponent(this->controller);
    this->controller = nullptr;
}

void ControllerView::addController(IRObjectController* controller)
{
    this->controller = controller;
    addAndMakeVisible(this->controller);
    resized();
}
