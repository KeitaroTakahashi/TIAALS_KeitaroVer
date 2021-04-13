//
//  IRStrComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 29/08/2019.
//

#include "IRStrComponent.hpp"

IRStrComponent::IRStrComponent(IRStr* str, IRStr* parentStr) :
ir_str(str),
ir_parentStr(parentStr)
{

}

IRStrComponent::~IRStrComponent()
{
    
}
// ==================================================


void IRStrComponent::setUIColour(IR::colorPattern pattern)
{
    getStr()->SYSTEMCOLOUR = pattern;
    getStr()->projectOwner->resized();
    getStr()->projectOwner->repaint();
    getStr()->projectOwner->updateAppearance();

}
// ==================================================
