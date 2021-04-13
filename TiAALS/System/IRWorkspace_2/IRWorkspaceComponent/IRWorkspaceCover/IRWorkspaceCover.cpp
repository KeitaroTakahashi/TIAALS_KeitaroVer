//
//  IRWorkspaceCover.cpp
//  IRiMaS
//
//  Created by Keitaro on 11/05/2020.
//

#include "IRWorkspaceCover.hpp"

IRWorkspaceCover::IRWorkspaceCover(IRStr* str) :
IRStrComponent(str)
{
    setOpaque(false);

}

IRWorkspaceCover::~IRWorkspaceCover()
{
    std::cout << "pic w = " << this->img.getWidth() << " ; " << this->img.getHeight() <<std::endl;
    
}
// ==================================================

void IRWorkspaceCover::paint(Graphics& g)
{
    g.fillAll(Colours::transparentWhite);

}

void IRWorkspaceCover::resized() 
{
    
}
// ==================================================
void IRWorkspaceCover::setEditMode(bool flag)
{
    this->isEditModeFlag = flag;
    //repaint();
}
void IRWorkspaceCover::setBackgroundColour(Colour colour)
{
    this->backgroundColour = colour;
    //repaint();
}


// ==================================================

// ==================================================

void IRWorkspaceCover::setGridValue(int thinInterval, int thickRatio)
{
    
    //repaint();
}
