//
//  IRObjectController.cpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#include "IRObjectController.hpp"

IRObjectController::IRObjectController(String title, IRStr* str) : IRStrComponent(str),
switchButton(str)
{
    
    addAndMakeVisible(&this->LabelTitle);
    this->LabelTitle.setText(title, dontSendNotification);
    this->LabelTitle.setFont(getStr()->SYSTEMCOLOUR.h3);
    this->LabelTitle.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
    this->LabelTitle.setJustificationType(Justification::left);
    
    addMouseListener(str->projectOwner, false);
    this->switchButton.createButton("Main", this);
    this->switchButton.createButton("Arrange", this);
    
    addAndMakeVisible(this->switchButton);
    buttonClicked(this->switchButton.getSquareButtonAt("Main"));
}

IRObjectController::~IRObjectController()
{
    this->arrangeController.reset();

}


void IRObjectController::resized()
{
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    this->LabelTitle.       setBounds(10, y, 300, 30);
    y += yBigIncrement;
    y += yIncrement;
    this->switchButton.setBounds(0, 42, getWidth(), 30);
    if(this->arrangeController.get() != nullptr)
    {
        this->arrangeController->setBounds(0, y, getWidth(), getHeight() - y);
    }
    
    ControllerResized();

}

void IRObjectController::buttonClicked(IRSquareButton* clickedButton)
{
    
    this->switchButton.selectAButton(clickedButton);
    
    if(clickedButton == this->switchButton.getSquareButtonAt("Main"))
    {
        mainControllerSelected();
    }else if(clickedButton == this->switchButton.getSquareButtonAt("Arrange"))
    {
        if(this->arrangeController != nullptr) arrangeControllerSelected();
    }
}

// ==================================================

void IRObjectController::setArrangeControllerVisible(bool shouldBeVisible)
{
    if(this->arrangeController.get() != nullptr)
        this->arrangeController->setVisible(shouldBeVisible);
}

// ==================================================

void IRObjectController::createAndAddArrangeController()
{
    
    this->arrangeController.reset(new ArrangeController(getStr()));
    addAndMakeVisible(this->arrangeController.get());
    this->arrangeController->setVisible(false);
    this->arrangeController->addChangeListener(this);
    
    this->hasArrangeControllerFlag = true;
}


void IRObjectController::changeListenerCallback (ChangeBroadcaster* source)
{
    // this will be overrided by the child class
    controllerChangeListenerCallback(source);
}
