//
//  PreferenceMenuComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#include "PreferenceMenuComponent.hpp"


PreferenceMenuComponent::PreferenceMenuComponent(IRStr* str, Rectangle<int> frameRect) :
ObjectMenuComponent(str, frameRect),
gui(str)
{
    setTitleText("Preference");
    
    addAndMakeVisible(&gui);
    
}

PreferenceMenuComponent::~PreferenceMenuComponent()
{
    
}

void PreferenceMenuComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

void PreferenceMenuComponent::resized()
{
    ObjectMenuComponent::resized();
    
    this->gui.setBounds(0, 100, getWidth(), getHeight() - 100);
}
// ==================================================

void PreferenceMenuComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}

