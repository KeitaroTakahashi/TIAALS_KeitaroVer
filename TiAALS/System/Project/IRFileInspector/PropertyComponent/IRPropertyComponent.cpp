//
//  PropertyComponent.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 13/03/2019.
//

#include "IRPropertyComponent.hpp"

IRPropertyComponent::IRPropertyComponent(const String &propertyName,juce::Point<int>Marge, Rectangle<int> objectBounds, int preferredHeight) :
PropertyComponent(propertyName, preferredHeight)
{
    this->objectBounds = objectBounds;
    this->title.setText(propertyName + " : (" + String(this->objectBounds.getX()) + ", " + String(this->objectBounds.getY()) + ")", dontSendNotification);
    addAndMakeVisible(this->title);
    
    setMarge(Marge.getX(), Marge.getY());
}

IRPropertyComponent::~IRPropertyComponent()
{
    
}

void IRPropertyComponent::resized()
{
    this->title.setBounds(this->xMarge, this->yMarge, getWidth(), getHeight());
}
void IRPropertyComponent::paint(Graphics& g)
{
    
}

void IRPropertyComponent::refresh()
{
    
}

void IRPropertyComponent::setMarge(int x, int y)
{
    this->xMarge = x;
    this->yMarge = y;
}


void IRPropertyComponent::setObjectPosition(Rectangle<int> bounds)
{
    this->objectBounds = bounds;
}
