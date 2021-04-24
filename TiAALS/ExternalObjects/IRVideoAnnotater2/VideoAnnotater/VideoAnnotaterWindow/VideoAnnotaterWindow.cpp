//
//  VideoAnnotaterWindow.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 22/03/2021.
//

#include "VideoAnnotaterWindow.hpp"


VideoAnnotaterWindow::VideoAnnotaterWindow(IRStr* str) : DocumentWindow("Video Annotater",
                                                              Desktop::getInstance().getDefaultLookAndFeel()
                                                              .findColour (ResizableWindow::backgroundColourId),
                                                              DocumentWindow::allButtons)
{
    
    setUsingNativeTitleBar(true);
    setResizeLimits(1000, 600, 6000, 6000);
    this->view.reset( new VideoAnnotaterView(str) );
    this->view->setBounds(0, 0, 1200, 800);
    setContentOwned(this->view.get(), false);
    
    setResizable(true, true);
    setBounds(0, 0, 1200, 800);
    
    
    this->view->initializeArea();
}

VideoAnnotaterWindow::~VideoAnnotaterWindow()
{
    this->view.reset();
}


void VideoAnnotaterWindow::close()
{
    setVisible(false);
}

void VideoAnnotaterWindow::open()
{
    setVisible(true);
}


void VideoAnnotaterWindow::closeButtonPressed()
{
    close();
}

void VideoAnnotaterWindow::minimiseButtonPressed()
{
    setFullScreen(false);
}

void VideoAnnotaterWindow::maximiseButtonPressed()
{
    setFullScreen(true);
}

// ------------------------------
