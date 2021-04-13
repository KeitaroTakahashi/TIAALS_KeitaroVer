
#include "IRPreferenceObject.hpp"





IRPreferenceObject::IRPreferenceObject(String title, Rectangle<int> frameRect, IRStr* str) :
IRStrComponent(str)
{
    this->frameRect = frameRect;
    //setBounds(frameRect.getX(), frameRect.getY(), frameRect.getWidth(), frameRect.getHeight());
}


IRPreferenceObject::~IRPreferenceObject()
{
    
}


void IRPreferenceObject::resized()
{
    //setBounds(frameRect.getX(), frameRect.getY(), frameRect.getWidth(), frameRect.getHeight());
}


void IRPreferenceObject::paint(Graphics& g)
{
    g.fillAll(Colours::white);
}


void IRPreferenceObject::changeListenerCallback(ChangeBroadcaster* source)
{
    
}



