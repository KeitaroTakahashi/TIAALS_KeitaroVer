//
//  IRShapeController.cpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#include "IRShapeController.hpp"

IRShapeController::IRShapeController(IRStr* str) : IRObjectController("Shape", str)
{
    this->ShapeController.reset(new shapeController(str));
    addAndMakeVisible(this->ShapeController.get());
    this->ShapeController->setVisible(true);
    this->ShapeController->addChangeListener(this);
    
    createAndAddArrangeController();
}

IRShapeController::~IRShapeController()
{
    this->ShapeController.reset();
}


void IRShapeController::ControllerResized()
{
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    
    y += yBigIncrement;
    y += yIncrement;
    this->ShapeController->setBounds(0, y, getWidth(), getHeight() - y);
}

void IRShapeController::paint(Graphics& g)
{

}

void IRShapeController::controllerChangeListenerCallback (ChangeBroadcaster* source)
{
    
}

void IRShapeController::mainControllerSelected()
{
    this->ShapeController->setVisible(true);
    setArrangeControllerVisible(false);
    
}

void IRShapeController::arrangeControllerSelected()
{
    this->ShapeController->setVisible(false);
    setArrangeControllerVisible(true);
}
