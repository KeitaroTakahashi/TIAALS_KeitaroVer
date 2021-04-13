//
//  IRTitleBarComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 01/10/2019.
//

#include "IRTitleBarComponent.hpp"

IRTitleBarComponent::IRTitleBarComponent(IRStr* str, String title) :
IRStrComponent(str),
title(title), editModeButton("to Control")
{
    setOpaque(false);
    this->titleLabel.setText(title, dontSendNotification);
    this->titleLabel.setJustificationType(Justification::centred);
    this->titleLabel.setFont(getStr()->SYSTEMCOLOUR.h4);
    this->titleLabel.addMouseListener(this, true);
    addAndMakeVisible(&this->titleLabel);

    createButton(&this->rightBarButton, getStr()->ICONBANK->icon_rightBar);
    this->rightBarButton.onClick = [this]{ rightBarButtonAction(); };
    this->rightBarButton.setDrawCircle(false);
    this->rightBarButton.setDrawRoundedSquare(true);
    addAndMakeVisible(&this->rightBarButton);
    
    this->rightBarLabel.setText("Controller", dontSendNotification);
    addAndMakeVisible(&this->rightBarLabel);
    this->rightBarLabel.setJustificationType(Justification::centred);
    this->rightBarLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

    this->projectButtonComponent.reset( new IRTitleBarProjectButtonArea(getStr()) );
    addAndMakeVisible(this->projectButtonComponent.get());


    createGridAreaComponent();
    
    addAndMakeVisible(&this->editModeButton);
    this->editModeButton.onClick = [this]{ editModeButtonAction(); };
    this->editModeLabel.setText("Mode", dontSendNotification);
    addAndMakeVisible(&this->editModeLabel);
    this->editModeLabel.setJustificationType(Justification::centred);
    this->editModeLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

}


IRTitleBarComponent::~IRTitleBarComponent()
{
    this->projectButtonComponent.reset();
    this->gridAreaComponent.reset();
}


//==================================================
void IRTitleBarComponent::paint (Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
    paintSelectedItem(g);
}

void IRTitleBarComponent::resized()
{
    
    this->titleLabel.setBounds(0, 0, getWidth(), 30);
    this->titleLabel.setCentrePosition(getWidth()/2, 15);
    
    int x = 10;
    //int w = getHeight() * 0.9;
    int h = getHeight() * 0.41;

    //this->buttonSize =juce::Point<int> (w, (float)w * this->rightBarButton.getAspectRatio());
    this->buttonSize =juce::Point<int> (((float)h / this->rightBarButton.getAspectRatio()) * 1.2, h);
    
    //this->closeButton.setBounds(5, 5, 20, 20);

    x = getWidth();
    x -= (this->buttonSize.getX() + marginX);
    int marginY = (getHeight() - this->buttonSize.getY())/2;
    int labelY = getHeight() - marginY + 3;
    int labelHeight = marginY * 0.5;

    this->rightBarButton.setBounds(x,
                                   marginY,
                                   this->buttonSize.getX(),
                                   this->buttonSize.getY());
    
    
    int halfMarginX = marginX / 2;
    this->rightBarLabel.setBounds(x - halfMarginX,
                                  labelY,
                                  this->buttonSize.getX() + marginX,
                                  labelHeight);
    
    x -= (this->buttonSize.getX()*1.6 + marginX);
    this->editModeButton.setBounds(x,
                                   marginY,
                                   this->buttonSize.getX() * 1.6,
                                   this->buttonSize.getY());
    this->editModeLabel.setBounds(x,
                                  labelY,
                                  this->buttonSize.getX() * 1.6,
                                  labelHeight);
    
    x -= 150;
    
    this->projectButtonComponent->setBounds(0, 0, 600, getHeight());
    this->gridAreaComponent->setBounds(x , 0, 150, getHeight());
    
}


void IRTitleBarComponent::paintSelectedItem(Graphics& g)
{
    if(this->selectedButtonType != NONE)
    {
        int marginY = (getHeight() - this->buttonSize.getY())/2;

        g.setColour(getStr()->SYSTEMCOLOUR.contents);
        int index = (int)this->selectedButtonType;
        int y = marginY / 2;
        int x = getWidth() - (this->marginX/2 + (index + 1) * (this->buttonSize.getX() + this->marginX));
        // width should be bigger to hide the right side rounded corner
        int h = getHeight() * 1.2;
        int w = this->buttonSize.getX() + marginX;
        g.fillRoundedRectangle(x, y, w, h, 5);
    }
}

//==================================================


void IRTitleBarComponent::createButton(IRImageButton* button, IRIconBank::IRIconImage img)
{
    if(getStr()->SYSTEMCOLOUR.isWhiteBased)
        button->setImage(img.black);
    else
        button->setImage(img.white);
    
    //button->setDrawCircle(false);
    addAndMakeVisible(button);
}


void IRTitleBarComponent::createGridAreaComponent()
{
    this->gridAreaComponent.reset( new IRTitleBarGridArea(getStr()));
    addAndMakeVisible(this->gridAreaComponent.get());
}
//==================================================

void IRTitleBarComponent::rightBarButtonAction()
{
    
    this->rightBarButton.setSelected(!this->rightBarButton.isSelected());
    
    if(this->rightBarButton.isSelected())
        this->selectedButtonType = rightBar;
    else
        this->selectedButtonType = NONE;
 
    if(this->rightBarButtonCallback != nullptr)
        this->rightBarButtonCallback(this->rightBarButton.isSelected());
    repaint();
}

void IRTitleBarComponent::editModeButtonAction()
{
    if(this->editModeButtonCallback != nullptr)
        this->editModeButtonCallback();
}
//==================================================


void IRTitleBarComponent::setEditMode(bool flag)
{
    if(flag)
    {
        this->editModeButton.setText("to Control");
    }else
    {
        this->editModeButton.setText("to Edit");
    }
}

//==================================================


void IRTitleBarComponent::setTitle(String newTitle)
{
    this->title = newTitle;
    this->titleLabel.setText(newTitle, dontSendNotification);
    repaint();
}
