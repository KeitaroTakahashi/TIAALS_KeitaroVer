//
//  IRVideoAnnotaterObjectUI.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 19/03/2021.
//

#include "IRVideoAnnotaterObjectUI.hpp"

IRVideoAnnotaterObjectUI::IRVideoAnnotaterObjectUI(IRStr* str) : IRStrComponent(str)
{
    this->openVideoButton.setImage(str->ICONBANK->icon_video.white);
    this->openVideoButton.setDrawCircle(false);
    this->openVideoButton.setDrawRoundedSquare(true);
    addAndMakeVisible(this->openVideoButton);
    this->openVideoButton.onClick = [this] { openVideoButtonClickedAction(); };
    
}

IRVideoAnnotaterObjectUI::~IRVideoAnnotaterObjectUI()
{
    
}

void IRVideoAnnotaterObjectUI::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    
    if(this->clickedFlag)
    {
        g.fillAll(Colours::white);
        this->clickedFlag = false;
    }
}

void IRVideoAnnotaterObjectUI::resized()
{
    this->openVideoButton.setBounds(getLocalBounds());
}

void IRVideoAnnotaterObjectUI::openVideoButtonClickedAction()
{    
    openVideoAnnotater();
    
    if(this->openVideoButtonClicked != nullptr)
        this->openVideoButtonClicked();
}

void IRVideoAnnotaterObjectUI::openVideoAnnotater()
{
    if(this->videoAnnotaterWindow == nullptr) return;
    
    this->videoAnnotaterWindow->setVisible(true);
    this->videoAnnotaterWindow->toFront(true);
    
}

void IRVideoAnnotaterObjectUI::setVideoAnnotaterWindow(VideoAnnotaterWindow* window)
{
    this->videoAnnotaterWindow = window;
}
