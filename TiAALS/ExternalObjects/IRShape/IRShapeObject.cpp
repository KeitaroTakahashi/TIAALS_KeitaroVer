//
//  IRShapeObject.cpp
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#include "IRShapeObject.hpp"

IRShapeObject::IRShapeObject(Component* parent, IRStr* str, IRBoundType boundType) :
IRNodeObject(parent, "IRShape", str, boundType)
{
    
    this->controller = std::make_shared<IRShapeController>(str);
    this->controller->getShapeController()->addChangeListener(this);
    this->controller->getArrangeController()->addChangeListener(this);
    setObjController(this->controller.get());

    setOpaque(false);
    this->UI.reset( new IRShapeUI(this, str) );
    this->UI->setShapeController(this->controller->getShapeController());
    addAndMakeVisible(this->UI.get());
    childComponentManager(this->UI.get());
    
    setObjectSize(200,200);
}

IRShapeObject::~IRShapeObject()
{
    this->UI.reset();
}
IRNodeObject* IRShapeObject::copyThisObject()
{
    IRShapeObject* newObj = new IRShapeObject(this->parent, getStr());
        
    newObj->UI->setColour(this->UI->getColour());
    newObj->UI->setStatus(this->UI->getStatus());
    newObj->UI->setLineWidth( this->UI->getLineWidth() );
    newObj->UI->setFill(this->UI->getFill() );
    newObj->UI->repaint();
    return newObj;
}

t_json IRShapeObject::saveThisToSaveData()
{
    
    Colour c = this->UI->getColour();
    
    t_json saveData = t_json::object({
        {"textColour", json11::Json::array({c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()})},
        {"status", (int)this->UI->getStatus()},
        {"lineWidth", this->UI->getLineWidth()},
        {"setFill", this->UI->getFill()}
    });
    
    t_json save = t_json::object({
        {"shape", saveData}
    });
    
    return save;
}
void IRShapeObject::loadThisFromSaveData(t_json data)
{
    // example : array
    t_json s = data["shape"];
    json11::Json::array c = s["textColour"].array_items();
    int r = c[0].int_value();
    int g = c[1].int_value();
    int b = c[2].int_value();
    int a = c[3].int_value();
    
    Colour textColour = Colour((uint8)r,
                               (uint8)g,
                               (uint8)b,
                               (uint8)a);
    this->UI->setColour(textColour);
    
    this->UI->setStatus((IRShapeUI::IRShapeStatus)s["status"].int_value());
    this->UI->setLineWidth(s["lineWidth"].number_value());
    this->UI->setFill(s["setFill"].bool_value());
    
}

// ------------------------------------------------------------
void IRShapeObject::paint(Graphics &g)
{
    //guide
    if(isEditMode())
    {
        g.setColour(Colours::grey);
        g.drawRect(getLocalBounds(), 1.0);
    }

    g.fillAll(Colours::transparentBlack);
    
}

void IRShapeObject::onResized()
{

    if(this->UI.get() != nullptr)
    {
        this->UI->setBounds(getLocalBounds());
        this->UI->repaint();
    }
}
// ------------------------------------------------------------

void IRShapeObject::mouseDownEvent(const MouseEvent& e)
{
    /*
    this->capturedImage = getCapturedImage();
    this->capturedImageReady = true;
    
    FileOutputStream stream (File ("/Users/keitaro/Desktop/test.png"));
    PNGImageFormat pngWriter;
    pngWriter.writeImageToStream(this->capturedImage, stream);
     */
    
}

// ------------------------------------------------------------

void IRShapeObject::IRChangeListenerCallback (ChangeBroadcaster* source)
{
    shapeController* shapeCtl = this->controller->getShapeController();
    ArrangeController* arrangeCtl = this->controller->getArrangeController();
    
    if(source == shapeCtl)
    {
        shapeControllerChangeListenerCallback(source);
    }else if (source == arrangeCtl)
    {
        arrangeControllerChangeListenerCallback(source);
    }

}

void IRShapeObject::shapeControllerChangeListenerCallback (ChangeBroadcaster* source)
{
    using statusFlag = shapeController::IRShapeControllerStatus;
    auto gui = this->controller->getShapeController();

    statusFlag status = gui->getStatus();
    
    
    if(status == statusFlag::FillMenuSelected)
    {
        
        std::cout << "FillMenu = " << gui->getFillMenuIndex() << std::endl;
        if(gui->getFillMenuIndex() == 1)
        {
            this->UI->setFill(true);
        }else if(gui->getFillMenuIndex() == 2)
        {
            this->UI->setFill(false);
        }
    }else if(status == statusFlag::ShapeMenuSelected)
    {
        switch(gui->getSelectedShapeIndex())
        {
            case 1:
                this->UI->setStatus(IRShapeUI::IRShapeStatus::SQUARE);
                break;
            case 2:
                this->UI->setStatus(IRShapeUI::IRShapeStatus::RHOMBUS);
                break;
            case 3:
                this->UI->setStatus(IRShapeUI::IRShapeStatus::CIRCLE);
                break;
            case 4:
                this->UI->setStatus(IRShapeUI::IRShapeStatus::TRIANGLE);
                break;
            default:
                break;
        }
    }else if(status == statusFlag::ColourChanged)
    {
        this->UI->setColour(gui->getColour());
    }else if(statusFlag::BorderWidthChanged)
    {
        this->UI->setLineWidth(gui->getLineWidth());
    }
    repaint();
}


void IRShapeObject::arrangeControllerChangeListenerCallback (ChangeBroadcaster* source)
{
    
}



void IRShapeObject::zoomRatioChanged(float ratio)
{
    float lineWidth = controller->getShapeController()->getLineWidth();
    
    //adjust line width only if both width and height are zoomable otherwise keep the same line width
    if(isWidthZoomable() && isHeightZoomable())
    {
        float fixedLineWidth = lineWidth / ratio;
        if(fixedLineWidth < 1.0) fixedLineWidth = 1.0;
        this->UI->setLineWidth(fixedLineWidth);
    }
    repaint();

}
