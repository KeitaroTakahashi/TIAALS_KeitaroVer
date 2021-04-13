
#include "IRTextEditorObject.hpp"

IRTextEditorObject::IRTextEditorObject(Component* parent, IRStr* str, IRBoundType boundType) :
IRNodeObject(parent, "IRTextEditor", str, boundType)
{
    this->textColour = Colours::black;
    this->backgroundColour = getStr()->SYSTEMCOLOUR.background.withAlpha(0.0f);
    this->controller.reset(new IRTextEditorController(str));
    this->controller->getFontController()->addChangeListener(this);
    this->controller->getFontController()->setBackgroundColour(this->backgroundColour);
    this->controller->getArrangeController()->addChangeListener(this);
    setObjController(this->controller.get());
    
    //this->font.setTypefaceName("Arial");
    //this->font.setTypefaceStyle("Regular");
    //this->font.setHeight(16.0);
    
    addAndMakeVisible(&this->textEditor);
    this->textEditor.setFont(this->font);
    
    //this->textEditor.onReturnKey = [this] { onReturnKeyAction(); };
    //this->textEditor.onTextChange = [this] { onTextChangeAction(); };
    
    // set editable condition
    
    this->textEditor.setMultiLine(true);
    this->textEditor.setReturnKeyStartsNewLine(true);
    
    childComponentManager(&this->textEditor);
    
    // default size
    setObjectBounds(0, 0, 150, 150);
    
    applyFontFromController();
    
}


IRTextEditorObject::~IRTextEditorObject()
{
    this->controller.reset();
}


IRNodeObject* IRTextEditorObject::copyThisObject()
{
    IRTextEditorObject* newObj = new IRTextEditorObject(this->parent, getStr());
    
    newObj->controller->getFontController()->setFontController(this->controller->getFontController());
    std::cout << "copyThisObject : fontSize = " << this->font.getHeight() << " : copied font " << newObj->getFont().getHeight() <<std::endl;

    /*
    newObj->setFont(this->font);
    newObj->setTextColour(this->textColour);
    newObj->setBackgroundColour(this->backgroundColour);
    newObj->setAlign(this->alignId);
    newObj->textEditor.setText(this->textEditor.getText() ,dontSendNotification);
     */
    
    newObj->applyFontFromController();
    
    return newObj;
}

void IRTextEditorObject::copyData(IRTextEditorObject* data)
{
    this->setFont(data->font);
    this->setTextColour(data->textColour);
    this->setBackgroundColour(data->backgroundColour);
    this->setAlign(data->alignId);
    this->textEditor.setText(data->textEditor.getText() ,dontSendNotification);
    setEncloseMode(data->getEncloseMode());
    
    this->textEditor.applyFontToAllText(this->font);
    this->applyColourToAllText(data->textColour);
}


t_json IRTextEditorObject::saveThisToSaveData()
{
    FontController* gui = this->controller->getFontController();
    Colour c = gui->getTextColour();
    Colour b = gui->getBackgroundColour();
    
    std::string align = std::to_string(gui->getAlign());
    
    //std::string LabelTextContents = this->label
    t_json save = t_json::object({
        {"fontTypefaceName", this->font.getTypefaceName().toStdString()},
        {"fontTypefaceStyle", this->font.getTypefaceStyle().toStdString()},
        {"fontHeight", this->font.getHeight()},
        {"textAlign", gui->getAlign()},
        {"textColour", t_json::array({c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()})},
        {"backgroundColour", t_json::array({b.getRed(), b.getGreen(), b.getBlue(), b.getAlpha()})},
        {"textContents", this->textEditor.getText().toStdString()}
    });
    
    std::cout << "saveThisToSaveData : textHeight = " << this->font.getHeight() << std::endl;

    return save;
}


void IRTextEditorObject::loadThisFromSaveData(t_json data)
{
    // example : string value
    //this->font.setTypefaceName(String(data["fontTypefaceName"].string_value()));
    setTypeFaceName(String(data["fontTypefaceName"].string_value()));
    //this->font.setTypefaceStyle(String(data["fontTypefaceStyle"].string_value()));
    setTypeFaceStyle(String(data["fontTypefaceStyle"].string_value()));
    // example : int value
    //this->font.setHeight(data["fontHeight"].int_value());
    setFontSize(data["fontHeight"].int_value());
    // set align
    setAlign(data["textAlign"].int_value());
    
    // set font
    //setFont(this->font);
    
    // example : array
    t_json::array colour = data["textColour"].array_items();
    Colour textColour = Colour((uint8)colour[0].int_value(),
                               (uint8)colour[1].int_value(),
                               (uint8)colour[2].int_value(),
                               (uint8)colour[3].int_value());
    
    t_json::array colour2 = data["backgroundColour"].array_items();
    Colour backgroundColour = Colour((uint8)colour2[0].int_value(),
                                     (uint8)colour2[1].int_value(),
                                     (uint8)colour2[2].int_value(),
                                     (uint8)colour2[3].int_value());

    // set text contents
    setTextContents(String(data["textContents"].string_value()));
    
    setTextColour(textColour);
    //this->textColour = textColour;
    //this->textEditor.applyColourToAllText(this->textColour, true);
    //this->textEditor.setColour(TextEditor::outlineColourId, Colours::transparentWhite);
    //this->textEditor.setColour(TextEditor::backgroundColourId , backgroundColour);
    setBackgroundColour(backgroundColour);
    
    // gui
    FontController* gui = this->controller->getFontController();
    gui->setTypefaceName(String(data["fontTypefaceName"].string_value()));
    gui->setTypefaceStyle(String(data["fontTypefaceStyle"].string_value()));
    gui->setHeight(data["fontHeight"].int_value());
    gui->setAlign(data["textAlign"].int_value());
    gui->setTextColour(textColour);
    gui->setBackgroundColour(backgroundColour);
    
    std::cout << "loadThisFromSaveData : fontHeight = " << data["fontHeight"].int_value() << std::endl;

}


void IRTextEditorObject::paint(Graphics &g)
{
    //g.fillAll(getStr()->SYSTEMCOLOUR.background);
    if (isEditMode())
    {
        //auto area = getLocalBounds();
        
        //g.setColour (getStr()->SYSTEMCOLOUR.contents);
       // g.drawRoundedRectangle (area.toFloat(), 5.0f, 2.0f);
       // g.drawRect(area.toFloat(), 2.0);
    }
}


void IRTextEditorObject::onResized()
{
    this->textEditor.setBounds(getLocalBounds());
}

// ------------------------------------------------------------


// ------------------------------------------------------------

void IRTextEditorObject::mouseDownEvent(const MouseEvent& e)
{
    
}

// ------------------------------------------------------------

void IRTextEditorObject::IRChangeListenerCallback (ChangeBroadcaster* source)
{
    //std::cout << "IRTextEditorObject::IRChangeListenerCallback\n";
    
    FontController* fontGUI = this->controller->getFontController();
    //ArrangeController* arrangeGUI = this->controller->getArrangeController();

    if(source == fontGUI)
    {
        fontControllerChangedCallback(fontGUI);
    }
}
// ------------------------------------------------------------

void IRTextEditorObject::fontControllerChangedCallback(FontController* source)
{
    
    //std::cout << "IRTextEditorObject::fontControllerChangedCallback : " << source->getChangeStatus() << std::endl;
    switch (source->getChangeStatus()) {
        case FontChanged:
            setTypeFaceName(source->getTypefaceName());
            break;
        case FontStyleChanged:
            setTypeFaceStyle(source->getTypefaceStyle());
            break;
        case FontSizeChanged:
            setFontSize(source->getHeight());
            break;
        case FontAlignChanged:
            setAlign(source->getAlign());
            break;
        case FontColourChanged:
            setTextColour(source->getTextColour());
            break;
        case BackgroundColourChanged:
            setBackgroundColour(source->getBackgroundColour());
            break;
        default:
            break;
    }
}


// ------------------------------------------------------------


void IRTextEditorObject::setFont(Font font)
{
    this->font = font;
    this->textEditor.setFont(this->font);
    
    textArrangeChanged();
}


void IRTextEditorObject::setAlign(int id)
{
    
    this->alignId = id;
    switch(id){
        case 1: // left
            this->textEditor.setJustification(Justification::left);
            break;
        case 2: // center
            this->textEditor.setJustification(Justification::centred);
            break;
        case 3: // right
            this->textEditor.setJustification(Justification::right);
            break;
        default:
            break;
    }
    
    
    textArrangeChanged();
}

// ==================================================

void IRTextEditorObject::setTypeFaceName(const String typefaceName)
{
    this->font.setTypefaceName(typefaceName);
    this->textEditor.applyFontToAllText(this->font);
    textArrangeChanged();
}

void IRTextEditorObject::setTypeFaceStyle(const String typefaceStyle)
{
    this->font.setTypefaceStyle(typefaceStyle);
    this->textEditor.applyFontToAllText(this->font);
    textArrangeChanged();
}

void IRTextEditorObject::setFontSize(int height)
{
    this->font.setHeight(height);
    this->controller->getFontController()->setHeight(height);
    
    float fixedFontSize = (float)height / getZoomRatio();
    if(fixedFontSize < 1.0) fixedFontSize = 1.0;
    this->textEditor.applyFontToAllText(fixedFontSize);
    textArrangeChanged();
}

void IRTextEditorObject::setTextColour(Colour colour)
{
    this->textColour = colour;
    this->textEditor.setColour(TextEditor::textColourId, colour);
    this->controller->getFontController()->setTextColour(colour);
    this->textEditor.applyFontToAllText(this->font);

    textArrangeChanged();
}

void IRTextEditorObject::setTextColour(Colour colour, float alpha)
{
    setTextColour(Colour(colour.getRed(), colour.getGreen(), colour.getBlue(), alpha));

}


void IRTextEditorObject::setTextColour(uint8 red, uint8 green, uint8 blue, float alpha)
{
    setTextColour(Colour(red, green, blue, alpha));
}

void IRTextEditorObject::applyColourToAllText(Colour colour)
{
    this->textColour = colour;
    this->textEditor.applyColourToAllText(colour);
    this->controller->getFontController()->setTextColour(colour);

    textArrangeChanged();
}

void IRTextEditorObject::applyColourToAllText(Colour colour, float alpha)
{
    applyColourToAllText(Colour(colour.getRed(), colour.getGreen(), colour.getBlue(), alpha));

}


void IRTextEditorObject::applyColourToAllText(uint8 red, uint8 green, uint8 blue, float alpha)
{
    applyColourToAllText(Colour(red, green, blue, alpha));
}



void IRTextEditorObject::setTextContents(String content)
{
    this->textEditor.setText(content, dontSendNotification);
}

// ==================================================

void IRTextEditorObject::setBackgroundColour(Colour colour)
{
    this->backgroundColour = colour;
    this->textEditor.setColour(TextEditor::backgroundColourId, colour);
    this->controller->getFontController()->setBackgroundColour(colour);
    repaint();
    
    textArrangeChanged();
}

void IRTextEditorObject::setBackgroundColour(Colour colour, float alpha)
{
    setBackgroundColour(Colour(colour.getRed(), colour.getGreen(), colour.getBlue(), alpha));

}


void IRTextEditorObject::setBackgroundColour(uint8 red, uint8 green, uint8 blue, float alpha)
{
    setBackgroundColour(Colour(red, green, blue, alpha));
}

// ==================================================
Font IRTextEditorObject::getFont() const
{
    return this->font;
}


Colour IRTextEditorObject::getTextColour() const
{
    return this->textColour;
}

Colour IRTextEditorObject::getBackgroundColour() const
{
    return this->backgroundColour;
}

int IRTextEditorObject::getAlignId() const
{
    return this->alignId;
}

int IRTextEditorObject::getTextWidth() const
{
    return this->textEditor.getTextWidth();
}
int IRTextEditorObject::getTextHeight() const
{
    return this->textEditor.getTextHeight();
}

void IRTextEditorObject::encloseStatusChangedListener()
{
    auto arr = this->controller->getArrangeController();
    
    bool id = arr->getEnclosedButtonStatus();
    
}


// ------------------------------------------------------------

void IRTextEditorObject::statusInEditMode()
{
    this->textEditor.setCaretVisible(true);
    this->textEditor.setReadOnly(false);
    
    // redefine MouseLIstenr
    //this->textEditor.addMouseListener(this, true);
    //this->textEditor.setInterceptsMouseClicks(true, false);
    
}

void IRTextEditorObject::statusInControlMode()
{
    this->textEditor.setCaretVisible(true);
    this->textEditor.setReadOnly(false);
    
    
}
// **** **** PRIVATE METHODS **** **** //

// ------------------------------------------------------------

void IRTextEditorObject::statusChangedCallback(IRNodeComponentStatus status)
{
    switch (status)
    {
        case EditModeStatus:
            if(isEditMode()) statusInEditMode();
            else statusInControlMode();
            break;
        case SelectableStatus:
            break;
        default:
            break;
    }
}

void IRTextEditorObject::selectedChangedAction(bool flag)
{
    if(flag)
    {
        this->textEditor.setColour(TextEditor::outlineColourId,
                                   Colours::black);
        this->textEditor.setColour(TextEditor::focusedOutlineColourId,
                                   Colours::black);
    }else{
        this->textEditor.setColour(TextEditor::outlineColourId,
                                   Colours::transparentBlack);
        this->textEditor.setColour(TextEditor::focusedOutlineColourId,
                                   Colours::transparentBlack);
    }
}


// ------------------------------------------------------------
/*

void IRTextEditorObject::onReturnKeyAction()
{
    //if(this->onReturnKey != nullptr)
     //   this->onReturnKey();
}
void IRTextEditorObject::onTextChangeAction()
{

    //if(this->onTextChange != nullptr)
     //   this->onTextChange();
}*/

void IRTextEditorObject::textArrangeChanged()
{
    repaint();

    //onTextChangeAction();
}

// ------------------------------------------------------------


void IRTextEditorObject::showTextContents()
{
    std::cout << this->textEditor.getText() << std::endl;
}

// ------------------------------------------------------------

int IRTextEditorObject::getCaretPosition()
{
    return this->textEditor.getCaretPosition();
}

void IRTextEditorObject::setCaretPosition(int newIndex)
{
    this->textEditor.setCaretPosition(newIndex);
}
// ------------------------------------------------------------


void IRTextEditorObject::arrangeControllerChangedNotify()
{
    std::cout << "arrangeControllerChangedNotify\n";
    //onTextChangeAction();
}

// ------------------------------------------------------------

void IRTextEditorObject::applyFontFromController()
{
    
    auto c = this->controller->getFontController();
    
    this->font.setTypefaceName(c->getTypefaceName());
    this->font.setTypefaceStyle(c->getTypefaceStyle());
    this->font.setHeight(c->getHeight());
    setAlign(c->getAlign());
    this->textColour = c->getTextColour();
    this->backgroundColour = c->getBackgroundColour();
    setBackgroundColour(this->backgroundColour);
    
    
    this->textEditor.setColour(TextEditor::backgroundColourId, this->backgroundColour);
    this->textEditor.setColour(TextEditor::outlineColourId,
                               Colours::transparentBlack);
    this->textEditor.setColour(TextEditor::focusedOutlineColourId,
                               Colours::transparentBlack);
    

    
    this->textEditor.setText("text...", dontSendNotification);


    this->textEditor.applyColourToAllText(this->textColour, true);
    
    this->textEditor.applyFontToAllText(this->font);
    repaint();

}

// ------------------------------------------------------------

void IRTextEditorObject::zoomRatioChanged(float ratio)
{
    
    if(isWidthZoomable() && isHeightZoomable())
    {
        int fontSize = this->font.getHeight();
        
        // change only the font size of textEditor and not for controller
        // this is temporarl change. The original font size should be maintained
        float fixedFontSize = fontSize / ratio;
        if(fixedFontSize < 1.0) fixedFontSize = 1.0;
        this->textEditor.applyFontToAllText(fixedFontSize);
        textArrangeChanged();
    }
}
