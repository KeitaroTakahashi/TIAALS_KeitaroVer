
#include "ObjectMenuWindow.hpp"




ObjectMenuWindow::ObjectMenuWindow(String name, Rectangle<int> frameRect, ObjectListMenu* menu) :
DocumentWindow (name,
                Desktop::getInstance().getDefaultLookAndFeel()
                .findColour (ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
{
    // do not show a title bar
    setUsingNativeTitleBar(false);
    setTitleBarHeight(0);
    setBounds(frameRect);
    setVisible(true);
    // do not deallocate menu object here.
    setContentNonOwned(menu,true);
    
}


ObjectMenuWindow::~ObjectMenuWindow()
{
    
}


