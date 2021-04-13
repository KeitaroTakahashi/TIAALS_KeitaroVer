
#include "IRStartWindow.hpp"



IRStartWindow::IRStartWindow(String name, Rectangle<int> frameRect) :
    DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    // do not show a title bar
    setUsingNativeTitleBar(false);
    setTitleBarHeight(0);

    // get display bounds
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    int x = r.getWidth();
    int y = r.getHeight();
    setBounds(0, 0, frameRect.getWidth(), frameRect.getHeight());
    setCentrePosition(x / 2, y / 2);
    setResizable(false, false);
    
    setVisible(true);
    
    this->starter = std::make_unique<IRStarter>(frameRect);
    this->starter->addChangeListener(this);
    
    setContentOwned(this->starter.get(), true);
    
    
}


IRStartWindow::~IRStartWindow()
{
    
}


IRStarter::MenuActionStatus IRStartWindow::getMenuActionStatus() const
{
    return this->starter->getMenuActionStatus();
}


void IRStartWindow::closeButtonPressed()
{
    
}


// **** **** PRIVATE METHODS **** **** //
void IRStartWindow::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == this->starter.get())
    {
        IRStarter::MenuActionStatus status = this->starter->getMenuActionStatus();
        if (status == IRStarter::MenuActionStatus::CreateNewProjectAction)
        {

            
            sendChangeMessage();
        }
        else if (status == IRStarter::MenuActionStatus::OpenProjectAction)
        {
            sendChangeMessage();
        }
    }
}




