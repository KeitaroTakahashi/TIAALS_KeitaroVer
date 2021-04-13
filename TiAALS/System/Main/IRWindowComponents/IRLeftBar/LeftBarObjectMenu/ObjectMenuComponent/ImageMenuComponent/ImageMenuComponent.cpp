//
//  ImageMenuComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 12/08/2019.
//

#include "ImageMenuComponent.hpp"


ImageMenuComponent::ImageMenuComponent(IRStr* str, Rectangle<int> frameRect) :
ObjectMenuComponent(str, frameRect)
{
    setTitleText("Graphics");
    
        IRObjectFactory2& factory = singleton<IRObjectFactory2>::get_instance();
    auto objects = factory.getRegisteredObjectOfCategory(objectCategory::IMAGEMENU);

    for(auto o : objects)
    {
        std::cout << o->name << std::endl;
        createItem(o);
    }
}

ImageMenuComponent::~ImageMenuComponent()
{
    
}


// ==================================================
void ImageMenuComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

void ImageMenuComponent::resized()
{
    ObjectMenuComponent::resized();
}
// ==================================================

void ImageMenuComponent::itemSelected(IRObjectFactory2::t_object* obj)
{
    
}

// ==================================================
// ==================================================
// ==================================================
