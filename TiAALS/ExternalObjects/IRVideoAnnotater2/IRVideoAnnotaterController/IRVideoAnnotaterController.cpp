//
//  IRVideoAnnotaterController.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 22/03/2021.
//

#include "IRVideoAnnotaterController.hpp"


IRVideoAnnotaterController::IRVideoAnnotaterController(IRStr* str) : IRObjectController("Video Annotater",str)
{
    this->videoAnnotaterController.reset( new VideoAnnotaterController(str) );
    addAndMakeVisible(this->videoAnnotaterController.get());
    
    // create arrange controller
    createAndAddArrangeController();

}

IRVideoAnnotaterController::~IRVideoAnnotaterController()
{
    this->videoAnnotaterController.reset();
}



void IRVideoAnnotaterController::ControllerResized()
{
    //std::cout << "ControllerResized\n";
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    
    y += yBigIncrement;
    y += yIncrement;
    
    this->videoAnnotaterController->setBounds(0, y, getWidth(), getHeight() - y);
}

void IRVideoAnnotaterController::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.setColour(Colours::black);
    g.drawLine(0,42.5,getWidth(),42.5);
    //g.drawLine(0,250, getWidth(), 250);
    //g.drawLine(0,400,getWidth(),400);
}



void IRVideoAnnotaterController::controllerChangeListenerCallback (ChangeBroadcaster* source)
{
    
}


void IRVideoAnnotaterController::mainControllerSelected()
{
    this->videoAnnotaterController->setVisible(true);
    setArrangeControllerVisible(false);
    
}

void IRVideoAnnotaterController::arrangeControllerSelected()
{
    this->videoAnnotaterController->setVisible(false);
    setArrangeControllerVisible(true);
}
