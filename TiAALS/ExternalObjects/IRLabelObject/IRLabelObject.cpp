
#include "IRLabelObject.hpp"

IRLabelObject::IRLabelObject(Component* parent, IRStr* str, IRBoundType boundType) :
IRNodeObject(parent, "IRLabel", str, boundType)
{
    StopWatch bench;
    bench.start();
    // initialize controller
    this->controller.reset( new IRLabelController(str) );
    bench.result("Label controller");
    this->controller->getFontController()->addChangeListener(this);
    
    setObjController(this->controller.get());
    
    this->font.setTypefaceName("Arial");
    this->font.setTypefaceStyle("Regular");
    this->font.setHeight(20);
    
    setObjectSize(100,40);
    addAndMakeVisible(&this->label);
    this->label.setFont(this->font);

    this->label.setText("text...", dontSendNotification);
    this->label.setJustificationType(Justification::left);
    this->label.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.titleText);
    this->label.setColour(Label::textWhenEditingColourId, Colours::lightgrey);

    this->label.setMinimumHorizontalScale(1.0);
    // set editable condition
    this->label.setEditable(false, // edit on single click
                            true, // edit on double click
                            false // loss of focus discards changes
                            );
    
    childComponentManager(&this->label);
        
    // Link Menu
    /*
    clearLinkParam();
    addLinkParam(TextLinkFlag);
    addLinkParam(ConsoleLinkFlag);
    addLinkParam(AudioLinkFlag);
    addLinkParam(ImageLinkFlag);
    addLinkParam(DataLinkFlag);
*/
}


IRLabelObject::~IRLabelObject()
{
    // std::cout << "~IRLABELOBJECT DESTRUCTOR" << std::endl;
    this->controller.reset();
}


IRNodeObject* IRLabelObject::copyThisObject()
{
    IRLabelObject* newObj = new IRLabelObject(this->parent, getStr());
    newObj->setFont(this->font);
    newObj->label.setText(label.getText(true) ,dontSendNotification);
    //newObj->label.setColour(this->controller->getFontController()->getTextColour());
    return newObj;
}


t_json IRLabelObject::saveThisToSaveData()
{
    FontController* gui = this->controller->getFontController();
    Colour c = gui->getTextColour();
    
    std::string align = std::to_string(gui->getAlign());
    
    //std::string LabelTextContents = this->label
    t_json save = t_json::object({
        {"fontTypefaceName", this->font.getTypefaceName().toStdString()},
        {"fontTypefaceStyle", this->font.getTypefaceStyle().toStdString()},
        {"fontHeight", this->font.getHeight()},
        {"textAlign", gui->getAlign()},
        {"textColour", json11::Json::array({c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()})},
        {"textContents", this->label.getText().toStdString()}
    });
    
    
    return save;
}


void IRLabelObject::loadThisFromSaveData(t_json data)
{
    // example : string value
    this->font.setTypefaceName(String(data["fontTypefaceName"].string_value()));

    this->font.setTypefaceStyle(String(data["fontTypefaceStyle"].string_value()));
    // example : int value
    this->font.setHeight(data["fontHeight"].int_value());

    // set align
    setAlign(data["textAlign"].int_value());
    
    // set font
    setFont(this->font);

    // example : array
    json11::Json::array c = data["textColour"].array_items();
    int r = c[0].int_value();
    int g = c[1].int_value();
    int b = c[2].int_value();
    int a = c[3].int_value();
    
    Colour textColour = Colour((uint8)r,
                               (uint8)g,
                               (uint8)b,
                               (uint8)a);
    
    this->label.setColour(Label::textColourId, textColour);
    
    this->label.setText(String(data["textContents"].string_value()), dontSendNotification);
    
    // gui
    FontController* gui = this->controller->getFontController();
    gui->setTypefaceName(String(data["fontTypefaceName"].string_value()));
    gui->setTypefaceStyle(String(data["fontTypefaceStyle"].string_value()));
    gui->setHeight(data["textHeight"].int_value());
    gui->setAlign(data["textAlign"].int_value());
    gui->setTextColour(textColour);
        
}


void IRLabelObject::paint(Graphics &g)
{
    g.fillAll(Colours::transparentBlack);
    if (isEditMode())
    {
        auto area = getLocalBounds();
        g.setColour (Colours::grey);
        g.drawRect (area, 1.0);
    }
}

void IRLabelObject::paintOnWorkspace(Graphics& g, Component* workspace)
{
    
}


void IRLabelObject::onResized()
{
    this->label.setBounds(5,5, getWidth()-10, getHeight()-10);

}


void IRLabelObject::mouseDownEvent(const MouseEvent& e)
{
    //change preference Window if not yet
    /*
    if(getPreferenceWindow() != nullptr)
    {
        IRPreferenceSpace* space = getPreferenceWindow()->getPreferenceSpace();
        
        IRPreferenceObject* current = space->getPreferenceObj();
        
        std::cout << "PreferenceOBject = " << preference << std::endl;
        
        if (current != preference){
            space->setPreferenceObj(preference);
        }
    }*/
}


void IRLabelObject::IRChangeListenerCallback (ChangeBroadcaster* source)
{
    FontController* fontGUI = this->controller->getFontController();
    
    
    if(source == fontGUI)
    {
        //std::cout << fontGUI->getChangeStatus() << std::endl;
        switch (fontGUI->getChangeStatus()) {
            case FontChanged:
                this->font.setTypefaceName(fontGUI->getTypefaceName());
                this->label.setFont(this->font);
                break;
            case FontStyleChanged:
                this->font.setTypefaceStyle(fontGUI->getTypefaceStyle());
                this->label.setFont(this->font);
                break;
            case FontSizeChanged:
                this->font.setHeight(fontGUI->getHeight());
                this->label.setFont(this->font);
                break;
            case FontAlignChanged:
                                
                setAlign(fontGUI->getAlign());
                break;
            case FontColourChanged:
                this->label.setColour(Label::textColourId, fontGUI->getTextColour());
                repaint();
                break;
            default:
                break;
        }
        
    }
}


void IRLabelObject::setFont(Font font)
{
    this->font = font;
    this->label.setFont(this->font);
}


Font IRLabelObject::getFont() const
{
    return this->font;
}


void IRLabelObject::setAlign(int newAlign)
{
    switch(newAlign)
    {
        case 1: // left
            this->label.setJustificationType(Justification::left);
            break;
        case 2: // center
            this->label.setJustificationType(Justification::centred);
            break;
        case 3: // right
            this->label.setJustificationType(Justification::right);
            break;
        default:
            break;
    }
}




// **** **** PRIVATE METHODS **** **** //




void IRLabelObject::statusChangedCallback(IRNodeComponentStatus status)
{
    switch (status)
    {
        case EditModeStatus:
            break;
        case SelectableStatus:
            break;
        default:
            break;
    }
}



