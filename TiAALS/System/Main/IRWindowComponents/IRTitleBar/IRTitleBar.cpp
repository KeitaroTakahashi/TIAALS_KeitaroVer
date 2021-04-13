//
//  IRTitleBar.cpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#include "IRTitleBar.hpp"

//==============================================================================
IRTitleBar::IRTitleBar(IRStr* str, String title) :
IRStrComponent(str),
comp(str, title)
{
    setOpaque(false);

    this->comp.addMouseListener(this, true);
    addAndMakeVisible(&this->comp);
    
    
}

IRTitleBar::~IRTitleBar()
{
}

//==============================================================================
void IRTitleBar::paint (Graphics& g)
{
    
}

void IRTitleBar::resized()
{
    
    this->comp.setBounds(getLocalBounds());
}

void IRTitleBar::mouseDrag(const MouseEvent& e)
{
    this->currentPos = e.getScreenPosition();
   juce::Point<int>delta = this->currentPos - this->prevPos;
    
    this->pos.setX(getScreenX() + delta.getX());
    this->pos.setY(getScreenY() + delta.getY());
    
    this->status = MoveWindow;
    sendChangeMessage();

    this->prevPos = e.getScreenPosition();
}
//==============================================================================

void IRTitleBar::mouseUp(const MouseEvent& e)
{
    
}
void IRTitleBar::mouseDown(const MouseEvent& e)
{
    auto pos = e.getScreenPosition();
    this->prevPos = pos;
    checkResizableFromMouseDownPosition(pos);
}

void IRTitleBar::mouseDoubleClick(const MouseEvent& e)
{
    if(this->titleDoubleClickedCallback != nullptr)
        this->titleDoubleClickedCallback();
}

void IRTitleBar::checkResizableFromMouseDownPosition(juce::Point<int> pos)
{
    
}


void IRTitleBar::mouseMove(const MouseEvent& e)
{
    //std::cout << "mouse move : " << e.getPosition().getX() << " : " << e.getPosition().getY() << std::endl;
}
//==============================================================================

void IRTitleBar::changeListenerCallback (ChangeBroadcaster* source)
{
    if(source == &this->comp)
    {
        switch(this->comp.getSelectedButtonType())
        {
            case IRTitleBarComponent::SelectedButtonType::rightBar:
                break;
            case IRTitleBarComponent::SelectedButtonType::leftBar:
                break;
            default:
                break;
        }
    }
}
//==============================================================================

//==============================================================================
