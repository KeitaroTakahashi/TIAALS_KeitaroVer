//
//  IRVNShapeObject.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 04/04/2021.
//

#include "IRVNShapeObject.hpp"
IRVNShapeObject::IRVNShapeObject(Component* parent, IRStr* str, IRBoundType boundType) : IRShapeObject(parent, str, boundType)
{
    this->UI->setLineWidth(2);
}

IRVNShapeObject::~IRVNShapeObject()
{
    
}

void IRVNShapeObject::initialSetup()
{
    this->UI->setFill(true);
    this->UI->setStatus(IRShapeUI::IRShapeStatus::SQUARE);
    this->UI->setColour(Colour(uint8(255), uint8(0), uint8(0), uint8(100)));
    this->UI->setLineWidth(1);
}
