//
//  shapeController.h
//  IRiMaS
//
//  Created by Keitaro on 03/03/2020.
//

#ifndef shapeController_h
#define shapeController_h

#include "JuceHeader.h"

class shapeController : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
private ComboBox::Listener
{
public:
    enum IRShapeControllerStatus
    {
       ColourChanged,
       FillMenuSelected,
       LineWidthChanged,
       ShapeMenuSelected,
       BorderWidthChanged
    };
    
    shapeController(IRStr* str) :
    IRStrComponent(str),
    comboBoxFont(str)
    
    {
     /*
        addAndMakeVisible(&this->shapeMenuLabel);
        this->shapeMenuLabel.setText("Shape", dontSendNotification);
        this->shapeMenuLabel.setFont(getStr()->SYSTEMCOLOUR.h4);
        this->shapeMenuLabel.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
        this->shapeMenuLabel.setJustificationType(Justification::left);
        */
        
        addAndMakeVisible(&this->shapeMenu);
        this->shapeMenu.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);
        this->shapeMenu.addItem("Square", 1);
        this->shapeMenu.addItem("Rhombus", 2);
        this->shapeMenu.addItem("Circle", 3);
        this->shapeMenu.addItem("Triangle", 4);
        this->shapeMenu.setSelectedId(1, dontSendNotification);
        this->shapeMenu.addListener(this);
        
        addAndMakeVisible(&this->lineWidthLabel);
        this->lineWidthLabel.setText("Line Width", dontSendNotification);
        this->lineWidthLabel.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
        this->lineWidthLabel.setJustificationType(Justification::left);
        
        addAndMakeVisible(&this->lineWidthInput);
        this->lineWidthInput.onTextChange = [this] { lineWidthChanged(); };

        this->lineWidthInput.setColour(Label::textWhenEditingColourId, getStr()->SYSTEMCOLOUR.text);
        this->lineWidthInput.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
        this->lineWidthInput.setText("4", dontSendNotification);
        this->lineWidthInput.setJustificationType(Justification::left);
        this->lineWidthInput.setEditable(true);
        
        addAndMakeVisible(&this->fillLabel);
        this->fillLabel.setText("Fill shape", dontSendNotification);
        this->fillLabel.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
        this->fillLabel.setJustificationType(Justification::left);
        
        addAndMakeVisible(&this->fillMenu);
        this->fillMenu.setColour(ComboBox::backgroundColourId, getStr()->SYSTEMCOLOUR.fundamental);
        this->fillMenu.setColour(ComboBox::outlineColourId, getStr()->SYSTEMCOLOUR.contents);
        this->fillMenu.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);
        this->fillMenu.addItem("Fill", 1);
        this->fillMenu.addItem("Border", 2);
        this->fillMenu.setSelectedId(2, dontSendNotification);
        this->fillMenu.addListener(this);
        
        addAndMakeVisible(&this->shapeColourLabel);
        this->shapeColourLabel.setText("Shape colour", dontSendNotification);
        this->shapeColourLabel.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
        this->shapeColourLabel.setJustificationType(Justification::left);
        addAndMakeVisible(&this->shapeColour);
        
        this->shapeColour.setCurrentColour(Colours::red);
        this->shapeColour.addChangeListener(this);
    }
    
    ~shapeController()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    }
    
    void resized() override
    {
        int y = 0;
        int yIncrement = 30;
        int yBigIncrement = 30;
            
        //this->shapeMenuLabel.   setBounds(10, y, 100, 30);
        //y += yIncrement;
        this->shapeMenu.        setBounds(10, y, getWidth() - 20, 30);
        
        y += yBigIncrement;

        this->lineWidthLabel.   setBounds(10, y, 100, 30);
        this->lineWidthInput.   setBounds(110, y, 100, 30);
        
        y += yBigIncrement;

        this->fillLabel.        setBounds(10, y, 100, 30);
        this->fillMenu.         setBounds(110, y, 100, 30);
        
        y += yBigIncrement;

        this->shapeColourLabel. setBounds(10, y, 100, 30);
        y += yIncrement;
        this->shapeColour.      setBounds(10, y, getWidth() - 20, 200);
    }
    
    // ==================================================
    
    void setColour(Colour colour) { this->shapeColour.setCurrentColour(colour); }
    Colour getColour() const { return this->shapeColour.getCurrentColour(); }
    void setLineWidth(float width) { this->lineWidth = width; }
    float getLineWidth() const { return this->lineWidth; }
    void setFillShape(bool flag)
    {
        if(flag) this->fillMenu.setSelectedId(1, dontSendNotification);
        else this->fillMenu.setSelectedId(2, dontSendNotification);
        this->isFill = flag;
    }
    bool isFillShape() const { return this->isFill; }
    int getSelectedShapeIndex() const { return this->shapeMenu.getSelectedId(); }
    
    void setShape(int index)
    {
        this->shapeMenu.setSelectedId(index, dontSendNotification);
    }
    
    int getFillMenuIndex() const { return this->fillMenu.getSelectedId(); }
    void lineWidthChanged()
    {
        std::string val = this->lineWidthInput.getText().toStdString();
        float valFloat = atof(val.c_str());
        //std::cout << "fontSize value = " << valFloat << std::endl;
        
        if (valFloat == 0.0f)
        {
            valFloat = 4;
            this->lineWidthInput.setText("4", dontSendNotification);
        }
        
        this->lineWidth = valFloat;
        
        this->status = LineWidthChanged;
        sendChangeMessage();
    }
    
    IRShapeControllerStatus getStatus() const { return this->status; }

    
private:
    // ==================================================
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override
    {
        if(comboBoxThatHasChanged == &this->fillMenu)
        {
            this->status = FillMenuSelected;
            sendChangeMessage();
        }else if(comboBoxThatHasChanged == &this->shapeMenu)
        {
            this->status = ShapeMenuSelected;
            sendChangeMessage();
        }
    }
    void changeListenerCallback(ChangeBroadcaster* source) override
    {
        if (source == &this->shapeColour)
        {
            shapeColourChanged();
            this->status = ColourChanged;
            sendChangeMessage();
        }
    }
    // ==================================================

    IRShapeControllerStatus status;
    
    
    //Label LabelTitle;
    //Label shapeMenuLabel;
    ComboBox shapeMenu;
    
    Label fillLabel;
    ComboBox fillMenu;
    bool isFill = false;
    
    Label lineWidthLabel;
    Label lineWidthInput;
    float lineWidth = 4;
    
    Label shapeColourLabel;
    void shapeColourChanged() {}
    ColourSelector shapeColour
    {
        ColourSelector::showSliders
        | ColourSelector::showColourspace
        | ColourSelector::showAlphaChannel
    };
    // ==================================================
    
    
    //for combo box
    class BoxLookAndFeel : public LookAndFeel_V3
    {
    public:
        BoxLookAndFeel(IRStr* str) : str(str) {}
        
        Font getComboBoxFont(ComboBox& /* box */) override
        {
            return getNewFont();
        }
        Font getPopupMenuFont() override
        {
            return getNewFont();
        }
        
    private:
        IRStr* str;
        Font getNewFont()
        {
            return this->str->SYSTEMCOLOUR.h5;
        }
    };
    
    BoxLookAndFeel comboBoxFont;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(shapeController)
    
};

#endif /* shapeController_h */
