//
//  VideoAnnotaterWindowController.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 24/03/2021.
//

#include "VideoAnnotaterWindowController.hpp"


VideoAnnotaterWindowController::VideoAnnotaterWindowController(IRStr* str) : IRObjectController("Video Annotater",str)
{
    this->videoAnnotaterController.reset( new VideoAnnotaterWindowControllerUI(str) );
    addAndMakeVisible(this->videoAnnotaterController.get());
    this->videoAnnotaterController->addChangeListener(this);
    
    // create arrange controller
    //createAndAddArrangeController();

}

VideoAnnotaterWindowController::~VideoAnnotaterWindowController()
{
    this->videoAnnotaterController.reset();
}



void VideoAnnotaterWindowController::ControllerResized()
{
    //std::cout << "ControllerResized\n";
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    
    y += yBigIncrement;
    y += yIncrement;
    
    this->videoAnnotaterController->setBounds(0, y, getWidth(), getHeight() - y);
}

void VideoAnnotaterWindowController::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.setColour(Colours::black);
    g.drawLine(0,42.5,getWidth(),42.5);
    //g.drawLine(0,250, getWidth(), 250);
    //g.drawLine(0,400,getWidth(),400);
}



void VideoAnnotaterWindowController::controllerChangeListenerCallback (ChangeBroadcaster* source)
{
    if(source == this->videoAnnotaterController.get())
    {
        using s = VideoAnnotaterWindowControllerUI::VideoAnnotaterWindowControllerUIStatus;
        
        switch(this->videoAnnotaterController->getStatus())
        {
            case s::openVideoFile:
                callVideoFileCallback();
                break;
            case s::videoSizePercent:
                callVideoSizePercentCallback();
            default:
                break;
        }
    }
}


void VideoAnnotaterWindowController::mainControllerSelected()
{
    this->videoAnnotaterController->setVisible(true);
    setArrangeControllerVisible(false);
    
}

void VideoAnnotaterWindowController::arrangeControllerSelected()
{
    //this->videoAnnotaterController->setVisible(false);
    //setArrangeControllerVisible(true);
}

void VideoAnnotaterWindowController::callVideoFileCallback()
{
    if(this->openVideoFileCallback != nullptr)
    {
        this->openVideoFileCallback();
    }
}

void VideoAnnotaterWindowController::callVideoSizePercentCallback()
{
    std::cout << "callVideoSizePercentCallback\n";
    if(this->videoSizePercentCallback != nullptr)
        this->videoSizePercentCallback(this->videoAnnotaterController->getVideoSizePercent());
    
}
