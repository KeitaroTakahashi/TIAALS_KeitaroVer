//
//  IRImageViewerController.cpp
//  IRiMaS
//
//  Created by Keitaro on 03/10/2019.
//

#include "IRImageViewerController.hpp"

IRImageViewerController::IRImageViewerController(IRStr* str) : IRObjectController("ImageViewer", str),
UI(str)
{
    addAndMakeVisible(&this->LabelTitle);
    this->LabelTitle.setText("ImageViewer", dontSendNotification);
    this->LabelTitle.setFont(getStr()->SYSTEMCOLOUR.h3);
    this->LabelTitle.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
    this->LabelTitle.setJustificationType(Justification::left);
    
    addAndMakeVisible(&this->UI);
    this->UI.addChangeListener(this);
    
    // create arrange controller
    createAndAddArrangeController();
}
IRImageViewerController::~IRImageViewerController()
{
    
}

void IRImageViewerController::ControllerResized()
{
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    y += yBigIncrement;
    y += yIncrement;

    //this->LabelTitle.       setBounds(10, y, getWidth() - 20, 30);
    
    //y += yBigIncrement;
    
    this->UI.               setBounds(0, y, getWidth(), getHeight() - y);
}
void IRImageViewerController::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.setColour(Colours::black);
    g.drawLine(0,42.5,getWidth(),42.5);
}

void IRImageViewerController::changeListenerCallback (ChangeBroadcaster* source)
{
    if(source == &this->UI)
    {
        switch (this->UI.getStatus())
        {
            case ImageController::OpenImageFile:
                this->status = OpenImageFile;
                sendChangeMessage();
                break;
                
            default:
                break;
        }
    }
}



void IRImageViewerController::mainControllerSelected()
{
    this->UI.setVisible(true);
    setArrangeControllerVisible(false);
    
}

void IRImageViewerController::arrangeControllerSelected()
{
    this->UI.setVisible(false);
    setArrangeControllerVisible(true);
}
