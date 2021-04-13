//
//  AudioMenuComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#include "AudioMenuComponent.hpp"

AudioMenuComponent::AudioMenuComponent(IRStr* str, Rectangle<int> frameRect) : ObjectMenuComponent(str, frameRect)
{
    setTitleText("Audio");
    IRObjectFactory2& factory = singleton<IRObjectFactory2>::get_instance();
    auto objects = factory.getRegisteredObjectOfCategory(objectCategory::AUDIOMENU);

    for(auto o : objects)
    {
        std::cout << o->name << std::endl;
        createItem(o);
    }
}

AudioMenuComponent::~AudioMenuComponent()
{
    
}

void AudioMenuComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    
}

void AudioMenuComponent::resized()
{
    ObjectMenuComponent::resized();
}
// ==================================================

void AudioMenuComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}
