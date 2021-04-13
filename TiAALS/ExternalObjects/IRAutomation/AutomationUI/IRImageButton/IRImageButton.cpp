//
//  IRImageButton.cpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#include "IRImageButton.hpp"

IRImageButton::IRImageButton(String name) :
name(name),
drawColour(Colour(255, 255, 255))
{
    setOpaque(false);
    
    //setHeavyWeightBackgroundAlpha(0.0);
}

IRImageButton::~IRImageButton()
{
    
}

// ==================================================

void IRImageButton::paint(Graphics& g)

{
    g.fillAll(Colours::transparentBlack);

    
    if(this->mouseDownFlag)
        g.setColour(Colours::lightgrey);
    else g.setColour(Colours::white);

    g.setColour(this->drawColour);
    
    if(this->drawCircle)
    {
        if(!this->mouseDownFlag)
            g.drawEllipse(1, 1, getWidth()-2, getHeight()-2, 1);
        else
            g.fillEllipse(1, 1, getWidth()-1, getHeight()-1);
    }
    
    if(this->drawRoundedSquare)
    {
        if(!this->mouseDownFlag)
            g.drawRoundedRectangle(1, 1, getWidth() - 2, getHeight() - 2, 4.0, 1);
        else
            g.fillRoundedRectangle(1, 1, getWidth() - 2, getHeight() - 2, 4.0);
    }
    
    g.drawImage(this->buttonImage, getLocalBounds().reduced(1).toFloat());
    
}

void IRImageButton::resized()
{
    
}

void IRImageButton::setImage(Image img)
{
    this->buttonImage = img;
    
    this->w_h_ratio = (float)img.getHeight() / (float)img.getWidth();
    
    repaint();
}

void IRImageButton::mouseDown(const MouseEvent& e)
{
    this->mouseDownFlag = true;
    
    // for its child class
    clicked();
    
    if(this->onClick != nullptr) onClick();
    repaint();
    
}


void IRImageButton::mouseUp(const MouseEvent& e)
{
    //std::cout << "IRImageButton::mouseUp\n";
    this->mouseDownFlag = false;
    repaint();
}

