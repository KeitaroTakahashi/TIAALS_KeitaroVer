//
//  TextMenuComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 12/08/2019.
//

#include "TextMenuComponent.hpp"

TextMenuComponent::TextMenuComponent(IRStr* str,Rectangle<int> frameRect) :
ObjectMenuComponent(str, frameRect)
{
    setTitleText("Texts");

    IRObjectFactory2& factory = singleton<IRObjectFactory2>::get_instance();
    auto objects = factory.getRegisteredObjectOfCategory(objectCategory::TEXTMENU);
    
    for(auto o : objects)
    {
        std::cout << o->name << std::endl;
        createItem(o);
    }
}

TextMenuComponent::~TextMenuComponent()
{
    
}


// ==================================================
void TextMenuComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

void TextMenuComponent::resized()
{
    ObjectMenuComponent::resized();
}
// ==================================================
void TextMenuComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}


// ==================================================
// ==================================================
// ==================================================
