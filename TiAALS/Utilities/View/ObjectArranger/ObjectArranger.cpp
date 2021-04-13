//
//  ObjectArranger.cpp
//  IRiMaS
//
//  Created by Keitaro on 04/02/2020.
//

#include "ObjectArranger.hpp"


ArrangeController::ArrangeController(IRStr* str) : IRStrComponent(str),
encloseColour(str->SYSTEMCOLOUR.fundamental.brighter(), 1.0, str)
{
    createLabel(this->labelSize, "Size : ");
    createSmallLabel(this->labelWidth, "Width");
    createSmallLabel(this->labelHeight, "Height");

    createSmallLabel(this->labelSizePixel, "pixel");

    createLabel(this->InputWidth, "0");
    //this->InputWidth.onTextChange = [this]{InputWidthChanged();};
    this->InputWidth.setEditable(true);
    createLabel(this->InputHeight, "0");
    //this->InputHeight.onTextChange = [this]{InputHeightChanged();};
    this->InputHeight.setEditable(true);

    createLabel(this->labelPosition, "Position : ");
    createSmallLabel(this->labelX, "X");
    createSmallLabel(this->labelY, "Y");
    
    createSmallLabel(this->PositionLabelPixel, "pixel");

    createLabel(this->InputX, "0");
    //this->InputX.onTextChange = [this]{InputXChanged();};
    this->InputX.setEditable(true);
    createLabel(this->InputY, "0");
    //this->InputY.onTextChange = [this]{InputYChanged();};
    this->InputY.setEditable(true);
    
    // roration
    
    createLabel(this->labelRotation, "Rotation : ");
    createLabel(this->InputRotation, "0");
    this->InputRotation.setEditable(true);
    
    
    //layer
    createLabel(this->layerLabel, "Layer");
    createButton(this->frontButton, "Front");
    createButton(this->backButton, "Back");

    createLabel(this->statusLabel, "Status");
    createToggleButton(this->encloseButton, "Wrap");
    
    addAndMakeVisible(this->encloseColour);
    this->encloseColour.addChangeListener(this);
    
    createToggleButton(this->activateButton, "Activate");
    this->activateButton.setToggleState(1, dontSendNotification);
    
    createLabel(this->LabelTimeCode, "Time Code");
    createSmallLabel(this->labelTimeCodeBegin, "Begin");
    createSmallLabel(this->labelTimeCodeEnd, "End");
    createLabel(this->InputTimeCodeBegin, "0");
    createLabel(this->InputTimeCodeEnd, "3");
    this->InputTimeCodeBegin.setEditable(true);
    this->InputTimeCodeEnd.setEditable(true);
    
    
    
    setSize (250, 400);

}



ArrangeController::~ArrangeController()
{
}

void ArrangeController::setArrangeController(ArrangeController* controller)
{
    if(controller == nullptr) return;
    
    setRectangle(controller->getRectangle());
    setEncloseColour(controller->getEncloseColour());

}

// =======================================================

void ArrangeController::resized()
{
    int margin = 5;
    int ySmall = 25;
    int yIncrement = 40;
    int y = margin;
    int x = margin;
    this->labelSize.setBounds(x, y, 60, 20);
    this->InputWidth.setBounds(x + 80, y, 60, 20);
    this->InputHeight.setBounds(x + 150, y, 60, 20);
    y += ySmall;
    this->labelWidth.setBounds(x + 80, y, 60, 20);
    this->labelHeight.setBounds(x + 150, y, 60, 20);
    this->labelSizePixel.setBounds(x + 200, y - ySmall/2, 50, 20);
    
    y+= ySmall;
    this->labelPosition.setBounds(margin, y, 100, 20);
    this->InputX.setBounds(x + 80, y, 60, 20);
    this->InputY.setBounds(x + 150, y, 60, 20);
    y += ySmall;
    this->labelX.setBounds(x + 80, y, 60, 20);
    this->labelY.setBounds(x + 150, y, 60, 20);
    this->PositionLabelPixel.setBounds(x + 200, y - ySmall/2, 50, 20);
    y += ySmall;
    this->labelRotation.setBounds(margin, y, 100, 20);
    this->InputRotation.setBounds(x + 80, y, 60, 20);

    y += ySmall;
    this->layerLabel.setBounds(margin, y + 5, 60, 20);
    this->frontButton.setBounds(x + 80, y + 5, 60, 20);
    this->backButton.setBounds(x + 150, y + 5, 60, 20);
    
    y += yIncrement;
    this->statusLabel.setBounds(margin, y, 80, 20);
    this->encloseButton.setBounds(x + 80, y, 100, 20);
    this->encloseColour.setBounds(x + 180, y+3, 80, 20);
    
    y += ySmall;
    this->activateButton.setBounds(x + 80, y, 100, 20);
    
    y += yIncrement;
    this->LabelTimeCode.setBounds(margin, y, 80, 20);
    this->InputTimeCodeBegin.setBounds(x + 80, y, 60, 20);
    this->InputTimeCodeEnd.setBounds(x + 150, y, 60, 20);

    y += ySmall;
    this->labelTimeCodeBegin.setBounds(x + 80, y, 60, 20);
    this->labelTimeCodeEnd.setBounds(x + 150, y, 60, 20);
}

void ArrangeController::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(this->InputWidth.getBounds());
    g.drawRect(this->InputHeight.getBounds());
    g.drawRect(this->InputX.getBounds());
    g.drawRect(this->InputY.getBounds());
    
    g.drawRect(this->InputRotation.getBounds());
    
    g.drawLine(0, this->layerLabel.getY() - 5, getWidth(), this->layerLabel.getY() - 5);
    
    g.drawLine(0, this->statusLabel.getY() - 5, getWidth(), this->statusLabel.getY() - 5);

    g.drawRect(this->InputTimeCodeBegin.getBounds());
    g.drawRect(this->InputTimeCodeEnd.getBounds());

}
// =======================================================

void ArrangeController::createLabel(Label& label, String text)
{
    Font f("Avenir Next",20, Font::plain);
    label.setFont(f);
    label.addListener(this);
    addAndMakeVisible(label);
    label.setText(text, dontSendNotification);
    label.setJustificationType(Justification::left);
}
// =======================================================

void ArrangeController::createSmallLabel(Label& label, String text)
{
    Font f("Avenir Next",16, Font::plain);
    label.setFont(f);
    addAndMakeVisible(label);
    label.setText(text, dontSendNotification);
    label.setJustificationType(Justification::right);
}
// =======================================================


void ArrangeController::labelTextChanged (Label* labelThatHasChanged)
{
    LabelChangeListener(labelThatHasChanged);
}


void ArrangeController::LabelChangeListener(Label* label)
{
    if(label == &this->InputWidth)
    {
        this->status = INPUTWIDTH;
    }else if(label == &this->InputHeight)
    {
        this->status = INPUTHEIGHT;
    }else if(label == &this->InputX)
    {
        this->status = INPUTX;
    }else if(label == &this->InputY)
    {
        this->status = INPUTY;
    }else if(label == &this->InputTimeCodeBegin)
    {
        String val = this->InputTimeCodeBegin.getText();
        if(isDigitNumber(val)) setStartTimeSec(std::stof(val.toStdString()));
        else setStartTimeSec(0);
    }else if(label == &this->InputTimeCodeEnd)
    {
        this->status = TIMECODE_END;
        String val = this->InputTimeCodeEnd.getText();
        if(isDigitNumber(val)) setEndTimeSec(std::stof(val.toStdString()));
        else setEndTimeSec(0);
    }else if(label == &this->InputRotation)
    {
        InputRotationChanged();
    }

    sendChangeMessage();
}


// =======================================================
void ArrangeController::createButton(TextButton& button, String text)
{
    button.setButtonText(text);
    addAndMakeVisible(button);
    button.addListener(this);
}

void ArrangeController::createToggleButton(ToggleButton& button, String text)
{
    button.setButtonText(text);
    addAndMakeVisible(button);
    button.addListener(this);
}


void ArrangeController::buttonClicked(Button* button)
{
    if(button == &this->frontButton)
    {
        this->status = FRONTBUTTON;
        sendChangeMessage();
    }else if(button == &this->backButton)
    {
        this->status = BACKBUTTON;
        sendChangeMessage();
    }else if(button == &this->encloseButton)
    {
        std::cout << "arrangeController ENCLOSEBUTTON clicked!\n";

        this->status = ENCLOSEBUTTON;
        sendChangeMessage();
    }else if(button == &this->activateButton)
    {
        
        this->status = ACTIVATEBUTTON;
        sendChangeMessage();
    }
}

// =======================================================
int ArrangeController::getLabelWidth()
{
    return std::stoi(this->InputWidth.getText().toStdString());
}
int ArrangeController::getLabelHeight()
{
    return std::stoi(this->InputHeight.getText().toStdString());
}
int ArrangeController::getLabelX()
{
    return std::stoi(this->InputX.getText().toStdString());
}
int ArrangeController::getLabelY()
{
    return std::stoi(this->InputY.getText().toStdString());
}

bool ArrangeController::getEnclosedButtonStatus()
{
    return this->encloseButton.getToggleState();
}

bool ArrangeController::getActivateStatus()
{
    return this->activateButton.getToggleState();
}
// =======================================================

void ArrangeController::setRectangle(Rectangle<int> rect)
{
    // if change is made
    if(this->shouldUpdate)
    {
        setLabelWidth(rect.getWidth());
        setLabelHeight(rect.getHeight());
        setLabelX(rect.getX());
        setLabelY(rect.getY());
    }
    this->shouldUpdate = true;
}

Rectangle<int> ArrangeController::getRectangle()
{
    Rectangle<int> b (getLabelX(), getLabelY(),
                      getLabelWidth(), getLabelHeight());
    return b;
}




void ArrangeController::setLabelWidth(int width)
{
    int w = width;
    fixMinMax(w, this->res_min_w, this->res_max_w);
    this->InputWidth.setText(String(w), dontSendNotification);
    
}
void ArrangeController::setLabelHeight(int height)
{
    int h = height;
    fixMinMax(h, this->res_min_h, this->res_max_h);
    this->InputHeight.setText(String(h), dontSendNotification);
}
void ArrangeController::setLabelX(int x)
{
    int val = x;
    fixMinMax(val, this->res_min_x, this->res_max_x);
    this->InputX.setText(String(val), dontSendNotification);
}
void ArrangeController::setLabelY(int y)
{
    int val = y;
    fixMinMax(val, this->res_min_y, this->res_max_y);
    this->InputY.setText(String(val), dontSendNotification);
}

// =======================================================

void ArrangeController::setRestrictPosition(int min_x, int max_x,
                                            int min_y, int max_y)
{
    this->res_min_x = min_x;
    this->res_max_x = max_x;

    this->res_min_y = min_y;
    this->res_max_y = max_y;

}

void ArrangeController::setRestrictSize(int min_w, int max_w,
                                        int min_h, int max_h)
{
    this->res_min_w = min_w;
    this->res_max_w = max_w;

    this->res_min_h = min_h;
    this->res_max_h = max_h;

}

// =======================================================


void ArrangeController::fixMinMax(int& val, int min, int max)
{
    if(val < min) val = min;
    else if(val > max) val = max;
}

// =======================================================

void ArrangeController::changeListenerCallback(ChangeBroadcaster* source)
{
    if(source == &this->encloseColour)
    {
        this->status = ENCLOSECOLOUR;
        sendChangeMessage();
    }
}

// =======================================================


Colour ArrangeController::getEncloseColour() const {
    return this->encloseColour.getCurrentColour();
}

void ArrangeController::setEncloseColour(Colour newColour) {
    this->encloseColour.setCurrentColour(newColour);
    repaint();
}

void ArrangeController::setEncloseToggle(bool flag, NotificationType notification)
{
    this->encloseButton.setToggleState(flag, notification);
}

void ArrangeController::encloseColourChanged()
{
    this->status = EncloseColourChanged;
    sendChangeMessage();
}

// =======================================================
// event
void ArrangeController::InputWidthChanged()
{
    this->status = INPUTWIDTH;
    sendChangeMessage();
}

void ArrangeController::InputHeightChanged()
{
    this->status = INPUTHEIGHT;
    sendChangeMessage();
}

void ArrangeController::InputXChanged()
{
    this->status = INPUTX;
    sendChangeMessage();
}

void ArrangeController::InputYChanged()
{
    this->status = INPUTY;
    sendChangeMessage();
}

void ArrangeController::InputRotationChanged()
{
    this->status = INPUTROTATION;
    sendChangeMessage();
    
    String val = this->InputRotation.getText();
    if(isDigitNumber(val)) this->rotation = std::stof(val.toStdString());
    else this->rotation = 0.0;
}


void ArrangeController::InputTimeCodeBeginChanged()
{
    this->status = TIMECODE_BEGIN;
    sendChangeMessage();
}
void ArrangeController::InputTimeCodeEndChanged()
{
    this->status = TIMECODE_END;
    sendChangeMessage();
}
// =======================================================

void ArrangeController::setStartTimeSec(float sec)
{
    if(this->EndTimeSec < sec)
    {
        setEndTimeSec(sec);
        //setStartTimeSec(this->EndTimeSec);
    }else{
        this->StartTimeSec = sec;
        this->InputTimeCodeBegin.setText(String(sec), dontSendNotification);
        if(this->StartTimeSec == this->EndTimeSec)
            setEndTimeSec(this->StartTimeSec + 0.5);
        
        this->status = TIMECODE_BEGIN;

    }
}

void ArrangeController::setEndTimeSec(float sec)
{
    
    if(this->StartTimeSec > sec)
    {
        setStartTimeSec(sec);
        //setEndTimeSec(this->StartTimeSec);
    }else{
        this->EndTimeSec = sec;
        this->InputTimeCodeEnd.setText(String(sec), dontSendNotification);
        if(this->StartTimeSec == this->EndTimeSec)
            setEndTimeSec(this->StartTimeSec + 0.5);
        
        this->status = TIMECODE_END;

    }
    

}
// =======================================================


void ArrangeController::setRotation(float rotation)
{
    this->InputRotation.setText(String(rotation), dontSendNotification);
}
