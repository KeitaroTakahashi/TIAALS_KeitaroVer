//
//  IREnclosedObject.cpp
//  IRiMaS
//
//  Created by Keitaro on 23/02/2020.
//

#include "IREnclosedObject.hpp"

IREnclosedObject::IREnclosedObject()
{
    
}

IREnclosedObject::~IREnclosedObject()
{
    
}
// ==================================================

void IREnclosedObject::resized()
{
    
}

void IREnclosedObject::paint(Graphics& g)
{
    g.fillAll(this->bodyColour);
}

// ==================================================

void IREnclosedObject::mouseDown(const MouseEvent& e)
{
    if(this->onClick != nullptr) this->onClick();
}

// ==================================================

void IREnclosedObject::setColour(Colour colour)
{
    this->bodyColour = colour;
    repaint();
}

Colour IREnclosedObject::getColour() const { return this->bodyColour; }

// ==================================================
// ==================================================
