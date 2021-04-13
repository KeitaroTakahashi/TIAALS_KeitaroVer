//
//  IRShapePreferenceUI.cpp
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#include "IRShapePreferenceUI.hpp"

IRShapePreferenceUI::IRShapePreferenceUI(IRStr* str) :
IRStrComponent(str)
{
    
    addAndMakeVisible(&this->LabelTitle);
    this->LabelTitle.setText("IRShape", dontSendNotification);
    this->LabelTitle.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);
    this->LabelTitle.setJustificationType(Justification::left);

    
    addAndMakeVisible(&this->shapeMenuLabel);
    this->shapeMenuLabel.setText("Shape", dontSendNotification);
    this->shapeMenuLabel.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);
    this->shapeMenuLabel.setJustificationType(Justification::left);
    
    addAndMakeVisible(&this->shapeMenu);
    this->shapeMenu.setColour(ComboBox::backgroundColourId, SYSTEMCOLOUR.fundamental);
    this->shapeMenu.setColour(ComboBox::outlineColourId, SYSTEMCOLOUR.contents);
    this->shapeMenu.setColour(ComboBox::focusedOutlineColourId, SYSTEMCOLOUR.contents);
    this->shapeMenu.addItem("Square", 1);
    this->shapeMenu.addItem("Circle", 2);
    this->shapeMenu.addItem("Triangle", 3);
    this->shapeMenu.setSelectedId(1, dontSendNotification);
    this->shapeMenu.addListener(this);
    
    
    addAndMakeVisible(&this->lineWidthLabel);
    this->lineWidthLabel.setText("Line Width", dontSendNotification);
    this->lineWidthLabel.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);
    this->lineWidthLabel.setJustificationType(Justification::left);
    
    addAndMakeVisible(&this->lineWidthInput);
    this->lineWidthInput.onTextChange = [this] { lineWidthChanged(); };

    this->lineWidthInput.setColour(Label::textColourId, Colours::black);
    this->lineWidthInput.setColour(Label::textWhenEditingColourId, Colours::black);
    this->lineWidthInput.setText("4", dontSendNotification);
    this->lineWidthInput.setJustificationType(Justification::left);
    this->lineWidthInput.setEditable(true);
    
    addAndMakeVisible(&this->fillLabel);
    this->fillLabel.setText("Fill shape", dontSendNotification);
    this->fillLabel.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);
    this->fillLabel.setJustificationType(Justification::left);
    
    addAndMakeVisible(&this->fillMenu);
    this->fillMenu.setColour(ComboBox::backgroundColourId, SYSTEMCOLOUR.fundamental);
    this->fillMenu.setColour(ComboBox::outlineColourId, SYSTEMCOLOUR.contents);
    this->fillMenu.setColour(ComboBox::focusedOutlineColourId, SYSTEMCOLOUR.contents);
    this->fillMenu.addItem("Fill", 1);
    this->fillMenu.addItem("Border", 2);
    this->fillMenu.setSelectedId(2, dontSendNotification);
    this->fillMenu.addListener(this);
    
    addAndMakeVisible(&this->shapeColourLabel);
    this->shapeColourLabel.setText("Shape colour", dontSendNotification);
    this->shapeColourLabel.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);
    this->shapeColourLabel.setJustificationType(Justification::left);
    addAndMakeVisible(&this->shapeColour);
    
    this->shapeColour.setCurrentColour(Colours::red);
    this->shapeColour.addChangeListener(this);
    

    std::cout << "IRShapePreferenceUI init\n";
}

IRShapePreferenceUI::~IRShapePreferenceUI()
{
    
}

void IRShapePreferenceUI::resized()
{
    int y = 10;
    
    this->LabelTitle.setBounds           (20, y, 300, 30);
    
    this->shapeMenuLabel.setBounds(10, 50, 100, 30);
    this->shapeMenu.     setBounds(110, 50, 250, 30);

    this->lineWidthLabel.     setBounds(10, 90, 100, 30);
    this->lineWidthInput.     setBounds(110, 90, 100, 30);
    
    this->fillLabel         .setBounds(10, 130, 100, 30);
    this->fillMenu          .setBounds(110, 130, 250, 30);
    
    this->shapeColourLabel  .setBounds(10, 170, 100, 30);
    this->shapeColour       .setBounds(110, 170, 250, 200);
    
    
}

void IRShapePreferenceUI::paint(Graphics& g)
{
    g.fillAll(SYSTEMCOLOUR.contents.brighter());
    g.setColour(Colours::black);
    g.drawLine(0,42.5,getWidth(),42.5);
    //g.drawLine(0,250, getWidth(), 250);
    g.drawLine(0,400,getWidth(),400);
}

void IRShapePreferenceUI::shapeColourChanged()
{
    
}

void IRShapePreferenceUI::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == &this->shapeColour)
    {
        shapeColourChanged();
        this->status = ColourChanged;
        sendChangeMessage();
    }
}

void IRShapePreferenceUI::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged == &this->fillMenu)
    {
        
        std::cout << "comboBoxChanged\n";
        this->status = FillMenuSelected;
        sendChangeMessage();
    }else if(comboBoxThatHasChanged == &this->shapeMenu)
    {
        this->status = ShapeMenuSelected;
        sendChangeMessage();
    }
}

void IRShapePreferenceUI::lineWidthChanged()
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

void IRShapePreferenceUI::setFillShape(bool flag)
{
    if(flag)
    {
        this->fillMenu.setSelectedId(1, dontSendNotification);
    }else{
        this->fillMenu.setSelectedId(2, dontSendNotification);
    }
    this->isFill = flag;
}

void IRShapePreferenceUI::setShape(int index)
{
    this->shapeMenu.setSelectedId(index, dontSendNotification);
}
