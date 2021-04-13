
#include "IRPreferenceSpace.hpp"





IRPreferenceSpace::IRPreferenceSpace(String title, Rectangle<int> frameRect)
{
    this->title = title;
    setSize(frameRect.getWidth(), frameRect.getHeight());
}


IRPreferenceSpace::~IRPreferenceSpace()
{
    
}


void IRPreferenceSpace::resized()
{
    if (this->isPreferenceObjAlreadySet == true)
    {
        preferenceObj->setBounds(0, 0, getWidth(), getHeight());
    }
}


void IRPreferenceSpace::paint(Graphics& g)
{
    g.fillAll(Colours::white);
}


String IRPreferenceSpace::getTitle()
{
    return this->title;
}


void IRPreferenceSpace::changeListenerCallback(ChangeBroadcaster* source)
{
    
}


void IRPreferenceSpace::setPreferenceObj(IRPreferenceObject* preferenceObj)
{
    removeAllChildren();
    preferenceObj->setBounds(0, 0, getWidth(), getHeight());
    addAndMakeVisible(preferenceObj);
    this->preferenceObj = preferenceObj;
    
    this->isPreferenceObjAlreadySet = true;
    
    //std::cout << "prefernece OBj set with " << getWidth() << " , " << getHeight() << std::endl;
}


IRPreferenceObject* IRPreferenceSpace::getPreferenceObj()
{
    return this->preferenceObj;
}




