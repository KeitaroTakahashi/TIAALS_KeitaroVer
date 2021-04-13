
#ifndef FontGUI_hpp
#define FontGUI_hpp

#include "JuceHeader.h"

#include "IRStrComponent.hpp"
#include "singletonClass.hpp"



class FontGUI : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
public ComboBox::Listener
{
    
public:
    enum FontGUIStatus
    {
        FontChanged,
        FontStyleChanged,
        FontSizeChanged,
        FontAlignChanged,
        FontColourChanged,
        BackgroundColourChanged
    };

    FontGUI(String title, IRStr* str);
    ~FontGUI();
    
    void resized() override;
    void paint(Graphics& g) override;
    
    void getAllFonts();
    void getSelectedFontStyles(String fontName);
    
    void makeFontMenu();
    void makeFontStyleMenu();
    void makeAlignMenu();
    
    void fontMenuChanged();
    void fontStyleMenuChanged();
    void fontSizeInputChanged();
    void fontAlignMenuChanged();
    void fontColourMenuChanged();
    void backgroundColourMenuChanged();
    
    FontGUIStatus getChangeStatus() const;
    
    void setTypefaceNameIndex(int index);
    String getTypefaceName() const;
    void setTypefaceName(const String newStyle);
    
    String getTypefaceStyle() const;
    void setTypefaceStyle(const String newStyle);
    
    int getAlign() const;
    void setAlign(int newId);
    
    float getHeight() const;
    void setHeight(float newHeight);
    
    Colour getTextColour() const;
    void setTextColour(Colour newColour);
    Colour getBackgroundColour() const;
    void setBackgroundColour(Colour newColour);
    
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    
    
private:
    
    Label labelTitle;
    
    Label labelFont;
    ComboBox fontMenu;
    Label labelFontInput;
    
    Label labelStyle;
    ComboBox styleMenu;
    
    Label labelFontSize;
    Label fontSizeInput;
    float fontSize;
    
    Label labelTextColour;
    Label labelBackgroundColour;
    
    Label labelAlign;
    ComboBox alignMenu;
    
    StringArray fontStyleList;
    StringArray fontFamilyList;
    
    ColourSelector textColour
    {
        ColourSelector::showSliders
        | ColourSelector::showColourspace
        | ColourSelector::showAlphaChannel
    };
    
    ColourSelector backgroundColour
    {
        ColourSelector::showSliders
        | ColourSelector::showColourspace
        | ColourSelector::showAlphaChannel
    };
    
    FontGUIStatus status;
    
    // system colour
    //IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FontGUI)
    
};




#endif /* FontGUI_hpp */




