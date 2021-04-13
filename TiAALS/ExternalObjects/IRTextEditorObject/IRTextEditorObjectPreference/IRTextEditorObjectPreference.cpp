
#include "IRTextEditorObjectPreference.hpp"




IRTextEditorObjectPreference::IRTextEditorObjectPreference(String title, Rectangle<int> frameRect, IRStr* str) :
IRPreferenceObject(title,frameRect, str)

{
    // this->fontGUI = new FontGUI(title);
    this->fontGUI = std::make_unique<FontGUI>(title, str);
    addAndMakeVisible(this->fontGUI.get());
    this->fontGUI->addChangeListener(this);
}


IRTextEditorObjectPreference::~IRTextEditorObjectPreference()
{
    
}


void IRTextEditorObjectPreference::resized()
{
    IRPreferenceObject::resized();
    
    this->fontGUI->setBounds(0,0,getWidth(), getHeight());
}


void IRTextEditorObjectPreference::initialize()
{
    
}


void IRTextEditorObjectPreference::changeListenerCallback(ChangeBroadcaster* source)
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


FontGUI* IRTextEditorObjectPreference::getFontGUI()
{
    return this->fontGUI.get();
}





