//
//  IRFileInspecterWindow.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 11/03/2019.
//

#include "IRFileInspecterWindow.hpp"

IRFileInspecterWindow::IRFileInspecterWindow(String name) :
DocumentWindow(name,
               Desktop::getInstance().getDefaultLookAndFeel()
                .findColour (ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
{
    
    // show a title bar
    setUsingNativeTitleBar(true);
    
    
    setBounds(0, 0, getWidth(), getHeight());
    
    this->fileInspecter.reset(new IRFileInspecter());
    setContentOwned(this->fileInspecter.get(), true);

    setVisible(true);

}

IRFileInspecterWindow::~IRFileInspecterWindow()
{

}

void IRFileInspecterWindow::closeButtonPressed()
{
    // This is called when the user tries to close this window. Here, we'll just
    // ask the app to quit when this happens, but you can change this to do
    // whatever you need.
    //JUCEApplication::getInstance()->systemRequestedQuit();
    
    removeFromDesktop();
}

void IRFileInspecterWindow::show()
{
    addToDesktop();
    toFront(true);
}

void IRFileInspecterWindow::updateInspecter()
{
    std::cout << "updateInspecter\n";
    this->fileInspecter->updatePropertyPanel();
}

void IRFileInspecterWindow::setFileManager(IRFileManager* fileManager)
{
    this->fileInspecter->setIRFileManager(fileManager);
}
