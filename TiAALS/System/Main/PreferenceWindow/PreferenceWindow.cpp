
#include "PreferenceWindow.hpp"




PreferenceWindow::PreferenceWindow(String name) :
    DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    
    setUsingNativeTitleBar(true);
    
    this->preferenceSpace = std::make_unique<IRPreferenceSpace>("IRiMaS: Object Preferences", Rectangle<int>(0, 0, 400, 720));
    
    this->preferenceSpace->addChangeListener(this);
    setContentOwned(this->preferenceSpace.get(), true);
    
    setResizable(true, true);
    
    setName(this->preferenceSpace->getTitle());
    
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    
    int y = r.getY();
    int w = r.getWidth();
    
    setBounds(w - getWidth(), y, getWidth(), getHeight());
    
    // setVisible(true);
    setVisible(false);
    
}


PreferenceWindow::~PreferenceWindow()
{
    
}


void PreferenceWindow::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == this->preferenceSpace.get())
    {
        
    }
}


void PreferenceWindow::closeButtonPressed()
{
    // This is called when the user tries to close this window. Here, we'll just
    // ask the app to quit when this happens, but you can change this to do
    // whatever you need.
    JUCEApplication::getInstance()->systemRequestedQuit();
}


IRPreferenceSpace* PreferenceWindow::getPreferenceSpace()
{
    return this->preferenceSpace.get();
}




