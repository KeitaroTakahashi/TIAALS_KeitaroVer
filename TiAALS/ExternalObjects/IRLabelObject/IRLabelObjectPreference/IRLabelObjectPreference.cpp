
#include "IRLabelObjectPreference.hpp"




IRLabelObjectPreference::IRLabelObjectPreference(String title, Rectangle<int> frameRect, IRStr* str) :
IRPreferenceObject(title,frameRect, str)
{
    std::cout << "IRLABELOBJECTPREFERENCE CONSTRUCTOR" << std::endl;
    this->fontGUI = std::make_unique<FontGUI>(title, str);
    addAndMakeVisible(this->fontGUI.get());
    this->fontGUI->addChangeListener(this);

}


IRLabelObjectPreference::~IRLabelObjectPreference()
{
    std::cout << "~IRLABELOBJECTPREFERENCE DESTRUCTOR" << std::endl;
}


void IRLabelObjectPreference::resized()
{
    IRPreferenceObject::resized();
    
    this->fontGUI->setBounds(0, 0, getWidth(), getHeight());
}


void IRLabelObjectPreference::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == this->fontGUI.get())
    {
        switch (this->fontGUI->getChangeStatus())
        {
            case FontGUI::FontChanged:
                break;
            case FontGUI::FontStyleChanged:
                break;
            case FontGUI::FontSizeChanged:
                break;
            case FontGUI::FontAlignChanged:
                break;
            case FontGUI::FontColourChanged:
                break;
            default:
                break;
        }
        
    }
}


FontGUI* IRLabelObjectPreference::getFontGUI()
{
    return this->fontGUI.get();
}




