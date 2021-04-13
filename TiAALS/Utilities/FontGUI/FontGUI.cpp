
#include "FontGUI.hpp"



FontGUI::FontGUI(String title, IRStr* str) :
IRStrComponent(str)
{
    
    addAndMakeVisible(this->labelTitle);
    this->labelTitle.setText(title, dontSendNotification);
    this->labelTitle.setColour(Label::textColourId, Colours::black);
    this->labelTitle.setJustificationType(Justification::left);
    
    addAndMakeVisible(this->labelFont);
    this->labelFont.setText("Font : ", dontSendNotification);
    this->labelFont.setColour(Label::textColourId, Colours::black);
    this->labelFont.setJustificationType(Justification::left);
    
    // get info
    getAllFonts();
    
    makeFontMenu();
    makeFontStyleMenu();
    
    addAndMakeVisible(this->labelStyle);
    this->labelStyle.setText("Style : ", dontSendNotification);
    this->labelStyle.setColour(Label::textColourId, Colours::black);
    this->labelStyle.setJustificationType(Justification::left);
    
    addAndMakeVisible(this->labelFontSize);
    this->labelFontSize.setText("Font size : ", dontSendNotification);
    this->labelFontSize.setColour(Label::textColourId, Colours::black);
    this->labelFontSize.setJustificationType(Justification::left);
    
    addAndMakeVisible(this->fontSizeInput);
    this->fontSizeInput.setEditable(true);
    this->fontSizeInput.setText("16", dontSendNotification);
    this->fontSizeInput.setColour(Label::textColourId, Colours::black);
    this->fontSizeInput.setColour(Label::textWhenEditingColourId, Colours::black);
    
    this->fontSizeInput.setJustificationType(Justification::left);
    this->fontSizeInput.onTextChange = [this] { fontSizeInputChanged(); };
    
    addAndMakeVisible(this->labelAlign);
    this->labelAlign.setText("Align : ", dontSendNotification);
    this->labelAlign.setColour(Label::textColourId, Colours::black);
    this->labelAlign.setJustificationType(Justification::left);
    
    makeAlignMenu();
    
    addAndMakeVisible(this->labelTextColour);
    this->labelTextColour.setText("Text Colour : ", dontSendNotification);
    this->labelTextColour.setColour(Label::textColourId, Colours::black);
    this->labelTextColour.setJustificationType(Justification::left);
    
    addAndMakeVisible(this->textColour);
    this->textColour.setCurrentColour(Colours::black);
    this->textColour.addChangeListener(this);
    
    
    addAndMakeVisible(this->labelBackgroundColour);
    this->labelBackgroundColour.setText("BackGround Colour : ", dontSendNotification);
    this->labelBackgroundColour.setColour(Label::textColourId, Colours::black);
    this->labelBackgroundColour.setJustificationType(Justification::left);
    
    addAndMakeVisible(this->backgroundColour);
    this->backgroundColour.setCurrentColour(getStr()->SYSTEMCOLOUR.background);
    this->backgroundColour.addChangeListener(this);
    
}


FontGUI::~FontGUI()
{
    
}


void FontGUI::resized()
{
    
    // margin 10
    this->labelTitle.setBounds              (20, 10, 300, 30);
    
    this->labelFont.setBounds               (10, 50, 100, 30);
    this->fontMenu.setBounds                (110, 50, 250, 30);
    
    this->labelStyle.setBounds              (10, 90, 100, 30);
    this->styleMenu.setBounds               (110, 90, 250, 30);
    
    this->labelFontSize.setBounds           (10, 130, 100, 30);
    this->fontSizeInput.setBounds           (110, 130, 100, 30);
    
    this->labelAlign.setBounds              (10, 170, 100, 30);
    this->alignMenu.setBounds               (110, 170, 250, 30);
    
    this->labelTextColour.setBounds         (10, 210, 100, 30);
    this->textColour.setBounds              (110, 210, 250, 250);
    
    this->labelBackgroundColour.setBounds   (10, 470, 100, 30);
    this->backgroundColour.setBounds        (110, 470, 250, 250);
    
}


void FontGUI::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    g.setColour(Colours::black);
    g.drawLine(0, 42.5, getWidth(), 42.5);
}


void FontGUI::getAllFonts()
{
    Font f;
    this->fontFamilyList = f.findAllTypefaceNames();
    
    /*
     for(auto family : this->fontFamilyList){
     std::cout << family << std::endl;
     }*/
}


void FontGUI::getSelectedFontStyles(String fontName)
{
    Font f;
    f.setTypefaceName(fontName);
    this->fontStyleList = f.getAvailableStyles();
    
}


void FontGUI::makeFontMenu()
{
    addAndMakeVisible(this->fontMenu);
    
    this->fontMenu.setColour(ComboBox::backgroundColourId, getStr()->SYSTEMCOLOUR.fundamental);
    this->fontMenu.setColour(ComboBox::outlineColourId, getStr()->SYSTEMCOLOUR.contents);
    this->fontMenu.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);
    int index = 1;
    for (auto family : this->fontFamilyList)
    {
        this->fontMenu.addItem(family, index);
        index++;
    }
    this->fontMenu.onChange = [this] { fontMenuChanged(); };
    this->fontMenu.addListener(this);
    int defaultFontIndex = 1;
    this->fontMenu.setSelectedId(defaultFontIndex);
    
    getSelectedFontStyles(this->fontFamilyList[defaultFontIndex-1]);
}


void FontGUI::makeFontStyleMenu()
{
    addAndMakeVisible(this->styleMenu);
    
    this->styleMenu.setColour(ComboBox::backgroundColourId, getStr()->SYSTEMCOLOUR.fundamental);
    this->styleMenu.setColour(ComboBox::outlineColourId, getStr()->SYSTEMCOLOUR.contents);
    this->styleMenu.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);
    int index = 1;
    for (auto style : this->fontStyleList)
    {
        this->styleMenu.addItem(style, index);
        index++;
    }
    int defaultFontIndex = 1;
    this->styleMenu.setSelectedId(defaultFontIndex);
    this->styleMenu.onChange = [this] { fontStyleMenuChanged(); };
}


void FontGUI::makeAlignMenu()
{
    addAndMakeVisible(this->alignMenu);
    this->alignMenu.setColour(ComboBox::backgroundColourId, getStr()->SYSTEMCOLOUR.fundamental);
    this->alignMenu.setColour(ComboBox::outlineColourId, getStr()->SYSTEMCOLOUR.contents);
    this->alignMenu.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);
    
    this->alignMenu.addItem("Left",1);
    this->alignMenu.addItem("Centre",2);
    this->alignMenu.addItem("Right",3);
    this->alignMenu.setSelectedId(1);
    this->alignMenu.onChange = [this] { fontAlignMenuChanged(); };
}


void FontGUI::fontMenuChanged()
{
    
    this->status = FontChanged;
    sendChangeMessage();
    
}


void FontGUI::fontStyleMenuChanged()
{
    this->status = FontStyleChanged;
    sendChangeMessage();
}


void FontGUI::fontSizeInputChanged()
{
    std::string val = this->fontSizeInput.getText().toStdString();
    float valFloat = atof(val.c_str());
    //std::cout << "fontSize value = " << valFloat << std::endl;
    
    if (valFloat == 0.0f)
    {
        valFloat = 1.0f;
        this->fontSizeInput.setText("16", dontSendNotification);
    }
    
    this->fontSize = valFloat;
    
    this->status = FontSizeChanged;
    sendChangeMessage();
}


void FontGUI::fontAlignMenuChanged()
{
    this->status = FontAlignChanged;
    sendChangeMessage();
}


void FontGUI::fontColourMenuChanged()
{
    this->status = FontColourChanged;
    sendChangeMessage();
}


void FontGUI::backgroundColourMenuChanged()
{
    this->status = BackgroundColourChanged;
    sendChangeMessage();
}


FontGUI::FontGUIStatus FontGUI::getChangeStatus() const
{
    return this->status;
}


void FontGUI::setTypefaceNameIndex(int index)
{
    this->fontMenu.setSelectedId(index);
}


String FontGUI::getTypefaceName() const
{
    return this->fontFamilyList[this->fontMenu.getSelectedId() - 1];
}


void FontGUI::setTypefaceName(const String newStyle)
{
    this->fontMenu.setSelectedId(this->fontFamilyList.indexOf(newStyle) + 1);
}


String FontGUI::getTypefaceStyle() const
{
    return this->fontStyleList[this->styleMenu.getSelectedId() - 1];
}


void FontGUI::setTypefaceStyle(const String newStyle)
{
    this->styleMenu.setSelectedId(this->fontStyleList.indexOf(newStyle) + 1);
}


int FontGUI::getAlign() const
{
    return this->alignMenu.getSelectedId();
}


void FontGUI::setAlign(int newId)
{
    this->alignMenu.setSelectedId(newId);
}


float FontGUI::getHeight() const
{
    return this->fontSize;
}


void FontGUI::setHeight(float newHeight)
{
    this->fontSize = newHeight;
}


Colour FontGUI::getTextColour() const
{
    return this->textColour.getCurrentColour();
}


void FontGUI::setTextColour(Colour newColour)
{
    this->textColour.setCurrentColour(newColour);
}


Colour FontGUI::getBackgroundColour() const
{
    return this->backgroundColour.getCurrentColour();
}


void FontGUI::setBackgroundColour(Colour newColour)
{
    this->backgroundColour.setCurrentColour(newColour);
}


void FontGUI::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == &this->textColour)
    {
        // colour changed
        fontColourMenuChanged();
    }
    else if (source == &this->backgroundColour)
    {
        backgroundColourMenuChanged();
    }
}


void FontGUI::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{

}

