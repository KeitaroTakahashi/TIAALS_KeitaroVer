//
//  newFontController.h
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef newFontController_h
#define newFontController_h

#include "IRColourSettingIcon.h"

enum FontControllerStatus
{
    FontChanged,
    FontStyleChanged,
    FontSizeChanged,
    FontAlignChanged,
    FontColourChanged,
    BackgroundColourChanged
};


class FontController : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
public ComboBox::Listener
{
    
public:
    
    FontController(IRStr* str) : IRStrComponent(str),
    textColourIcon(Colours::black, 1.0, str),
    backgroundColourIcon(Colours::transparentWhite, 1.0, str)
    {
        addAndMakeVisible(this->labelFont);
        this->labelFont.setText("Font : ", dontSendNotification);
        //this->labelFont.setColour(Label::textColourId, Colours::black);
        this->labelFont.setJustificationType(Justification::left);

        getAllFonts();
        makeFontMenu();
        makeFontStyleMenu();

        addAndMakeVisible(this->labelStyle);
        this->labelStyle.setText("Style : ", dontSendNotification);
        this->labelStyle.setJustificationType(Justification::left);
        
        
        addAndMakeVisible(this->labelFontSize);
        this->labelFontSize.setText("Font size : ", dontSendNotification);
        this->labelFontSize.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->fontSizeInput);
        this->fontSizeInput.setEditable(true);
        this->fontSizeInput.setText("16", dontSendNotification);
        this->fontSize = 16;
                
        this->fontSizeInput.setJustificationType(Justification::left);
        this->fontSizeInput.onTextChange = [this] { fontSizeInputChanged(); };
        
        addAndMakeVisible(this->labelAlign);
        this->labelAlign.setText("Align : ", dontSendNotification);
        this->labelAlign.setJustificationType(Justification::left);
        
        makeAlignMenu();
        
        addAndMakeVisible(this->labelTextColour);
        this->labelTextColour.setText("Text Colour : ", dontSendNotification);
        this->labelTextColour.setJustificationType(Justification::left);
        

        // colour icon
        addAndMakeVisible(this->textColourIcon);
        this->textColourIcon.addChangeListener(this);
        
        addAndMakeVisible(this->backgroundColourIcon);
        this->backgroundColourIcon.addChangeListener(this);

        addAndMakeVisible(this->labelBackgroundColour);
        this->labelBackgroundColour.setText("BackGround Colour : ", dontSendNotification);
        this->labelBackgroundColour.setJustificationType(Justification::left);
        
       
    }
    ~FontController() {}
    
    void resized() override
    {
        int y = 0;
        int yIncrement = 30;
        int yBigIncrement = 30;
        
        int menuWidth = getWidth() - 20;
        int shortMenuWidth = getWidth() - 100;

        // margin 10
        //this->labelTitle.setBounds              (10, y, 300, 30);
        
        this->labelFont.setBounds               (10, y, 100, 30);
        y += yIncrement;
        this->fontMenu.setBounds                (10, y, menuWidth, 30);
        
        y += yBigIncrement;

        this->labelStyle.setBounds              (10, y, 80, 30);
        this->styleMenu.setBounds               (90, y, shortMenuWidth, 30);
        
        y += yBigIncrement;

        this->labelFontSize.setBounds           (10, y, 80, 30);
        this->fontSizeInput.setBounds           (90, y, shortMenuWidth, 30);
        
        y += yBigIncrement;

        this->labelAlign.setBounds              (10, y, 80, 30);
        this->alignMenu.setBounds               (90, y, shortMenuWidth, 30);
        
        y += yBigIncrement + 5;

        this->labelTextColour.setBounds         (10, y, 100, 30);
        this->textColourIcon.setBounds          (getWidth() - 10 - 80, y + 5, 80, 20);
        y += yBigIncrement;
        this->labelBackgroundColour.setBounds   (10, y, 140, 30);
        this->backgroundColourIcon.setBounds    (getWidth() - 10 - 80, y + 5, 80, 20);
        /*
        this->labelBackgroundColour.setBounds   (10, y, 100, 30);
        y += yIncrement;
        this->backgroundColour.setBounds        (10, y, menuWidth, 200);
         */
    }
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::transparentWhite);
        g.setColour(Colours::black);
        //g.drawLine(0, 42.5, getWidth(), 42.5);
    }
    
    void getAllFonts()
    {
        Font f;
        this->fontFamilyList = getStr()->fontFamilyList;
    }
    void getSelectedFontStyles(String fontName)
    {
        Font f;
        f.setTypefaceName(fontName);
        this->fontStyleList = f.getAvailableStyles();
    }
    
    void makeFontMenu()
    {
        addAndMakeVisible(this->fontMenu);
        
        this->fontMenu.setColour(ComboBox::backgroundColourId, getStr()->SYSTEMCOLOUR.fundamental);
        this->fontMenu.setColour(ComboBox::outlineColourId, getStr()->SYSTEMCOLOUR.contents);
        this->fontMenu.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);
        int index = 1;
        int defaultFontIndex = -1;

        for (auto family : this->fontFamilyList)
        {
            this->fontMenu.addItem(family, index);
            
            if(family == "Arial")
            {
                defaultFontIndex = index;
            }
            index++;
        }
        this->fontMenu.onChange = [this] { fontMenuChanged(); };
        this->fontMenu.addListener(this);
        
        
        this->fontMenu.setSelectedId(defaultFontIndex);
        
        getSelectedFontStyles(this->fontFamilyList[defaultFontIndex-1]);
    }
    void makeFontStyleMenu()
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
    
    void makeAlignMenu()
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
    
    void fontMenuChanged()
    {
        
        this->status = FontChanged;
        sendChangeMessage();
    }
    void fontStyleMenuChanged()
    {
        this->status = FontStyleChanged;
        sendChangeMessage();
    }
    void fontSizeInputChanged()
    {
        
        std::string val = this->fontSizeInput.getText().toStdString();
        std::cout << "fontsizeinputchanged : " << val << std::endl;

        float valFloat = atof(val.c_str());
        std::cout << "fontSize value = " << valFloat << std::endl;
        
        if (valFloat == 0.0f)
        {
            valFloat = 1.0f;
            this->fontSizeInput.setText("16", dontSendNotification);
        }
        std::cout << "fontSize value fixed = " << valFloat << std::endl;

        this->fontSize = valFloat;
        
        this->status = FontSizeChanged;
        sendChangeMessage();
    }
    void fontAlignMenuChanged()
    {
        this->status = FontAlignChanged;
        sendChangeMessage();
    }
    void fontColourMenuChanged()
    {
        this->status = FontColourChanged;
        sendChangeMessage();
    }
    void backgroundColourMenuChanged()
    {
        this->status = BackgroundColourChanged;
        sendChangeMessage();
    }
    
    FontControllerStatus getChangeStatus() const { return this->status; }
    
    // ============================================================
    void setTypefaceNameIndex(int index) { this->fontMenu.setSelectedId(index); }
    int getTypefaceNameIndex() const { return this->fontMenu.getSelectedId(); }
    String getTypefaceName() const { return this->fontFamilyList[this->fontMenu.getSelectedId() - 1]; }
    void setTypefaceName(const String newStyle) { this->fontMenu.setSelectedId(this->fontFamilyList.indexOf(newStyle) + 1); }
    
    String getTypefaceStyle() const { return this->fontStyleList[this->styleMenu.getSelectedId() - 1]; }
    void setTypefaceStyle(const String newStyle) { this->styleMenu.setSelectedId(this->fontStyleList.indexOf(newStyle) + 1); }
    
    int getAlign() const { return this->alignMenu.getSelectedId(); }
    void setAlign(int newId) { this->alignMenu.setSelectedId(newId); }
    
    float getHeight() const { return this->fontSize; }
    void setHeight(float newHeight)
    {
        std::cout << "FontController setHeight = " << newHeight <<std::endl;
        this->fontSizeInput.setText(String(newHeight), dontSendNotification);
        this->fontSize = newHeight;
        // call this manually here! setText onTextChanged not called by above method
        //fontSizeInputChanged();
    }
    
    Colour getTextColour() const { return this->textColourIcon.getCurrentColour(); }
    void setTextColour(Colour newColour) { this->textColourIcon.setCurrentColour(newColour); repaint(); }
    Colour getBackgroundColour() const { return this->backgroundColourIcon.getCurrentColour(); }
    void setBackgroundColour(Colour newColour) { this->backgroundColourIcon.setCurrentColour(newColour); repaint(); }
    // ============================================================

    void changeListenerCallback(ChangeBroadcaster* source) override
    {
       if (source == &this->textColourIcon)
        {
            fontColourMenuChanged();
        }else if(source == &this->backgroundColourIcon)
        {
            backgroundColourMenuChanged();
        }
    }
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override
    {

    }
    
    void setFontController(FontController* c)
    {
        
        setTypefaceNameIndex(c->getTypefaceNameIndex());
        setTypefaceName(c->getTypefaceName());
        
        setTypefaceStyle(c->getTypefaceStyle());
        setAlign(c->getAlign());
        std::cout << "c->getHeight() = " << c->getHeight() << std::endl;
        setHeight(c->getHeight());
        setTextColour(c->getTextColour());
        setBackgroundColour(c->getBackgroundColour());
    }
    
    
private:
    
    //Label labelTitle;
    
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
    
    IRColourSettingIcon textColourIcon;
    IRColourSettingIcon backgroundColourIcon;
    
    FontControllerStatus status;
    
    // system colour
    //IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FontController)
    
};


#endif /* newFontController_h */
