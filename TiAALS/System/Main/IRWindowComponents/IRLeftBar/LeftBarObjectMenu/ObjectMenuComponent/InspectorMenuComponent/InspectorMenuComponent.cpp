//
//  InspectorMenuComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#include "InspectorMenuComponent.hpp"


InspectorMenuComponent::InspectorMenuComponent(IRStr* str, Rectangle<int> frameRect) : ObjectMenuComponent(str, frameRect)
{
    setTitleText("Inspector");
    
}

InspectorMenuComponent::~InspectorMenuComponent()
{
    
}

void InspectorMenuComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

void InspectorMenuComponent::resized()
{
    ObjectMenuComponent::resized();
}
// ==================================================

void InspectorMenuComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}

// ==================================================
