//
//  PlayerMenuComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#include "PlayerMenuComponent.hpp"

PlayerMenuComponent::PlayerMenuComponent(IRStr* str, Rectangle<int> frameRect) : ObjectMenuComponent(str, frameRect)
{
    setTitleText("Players");
    IRObjectFactory2& factory = singleton<IRObjectFactory2>::get_instance();
    auto objects = factory.getRegisteredObjectOfCategory(objectCategory::PLAYERMENU);

    for(auto o : objects)
    {
        std::cout << o->name << std::endl;
        createItem(o);
    }
}

PlayerMenuComponent::~PlayerMenuComponent()
{
    
}

void PlayerMenuComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

void PlayerMenuComponent::resized()
{
    ObjectMenuComponent::resized();
}
// ==================================================

void PlayerMenuComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}

// ==================================================

