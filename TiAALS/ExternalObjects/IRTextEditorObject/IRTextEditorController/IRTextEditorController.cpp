//
//  IRTextEditorController.cpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#include "IRTextEditorController.hpp"


IRTextEditorController::IRTextEditorController(IRStr* str) : IRObjectController("TextEditor", str)
{
    
    
    this->fontController = std::make_unique<FontController>(str);
    addAndMakeVisible(this->fontController.get());
    this->fontController->setVisible(true);
    this->fontController->addChangeListener(this);
    
    // create arrange controller
    createAndAddArrangeController();
}

IRTextEditorController::~IRTextEditorController()
{
    this->fontController.reset();
}

void IRTextEditorController::ControllerResized()
{
    //std::cout << "ControllerResized\n";
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    
    y += yBigIncrement;
    y += yIncrement;
    this->fontController->setBounds(0, y, getWidth(), getHeight() - y);
}

void IRTextEditorController::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.setColour(Colours::black);
    g.drawLine(0,42.5,getWidth(),42.5);
    //g.drawLine(0,250, getWidth(), 250);
    //g.drawLine(0,400,getWidth(),400);
}


FontController* IRTextEditorController::getFontController()
{
    return this->fontController.get();
}

void IRTextEditorController::controllerChangeListenerCallback (ChangeBroadcaster* source)
{
    
}


void IRTextEditorController::mainControllerSelected()
{
    this->fontController->setVisible(true);
    setArrangeControllerVisible(false);
    
}

void IRTextEditorController::arrangeControllerSelected()
{
    this->fontController->setVisible(false);
    setArrangeControllerVisible(true);
}
