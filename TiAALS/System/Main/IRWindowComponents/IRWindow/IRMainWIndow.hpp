//
//  IRWindow.hpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#ifndef IRWindow_hpp
#define IRWindow_hpp

#include "IRWindowComponent.hpp"


class IRMainWindow : public DocumentWindow
{
    
public:
    IRMainWindow(String name) : DocumentWindow(name,
                                                          Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (ResizableWindow::backgroundColourId),
                                                          DocumentWindow::closeButton)
    {
        // dont use the native title bar
        setUsingNativeTitleBar(false);
        setTitleBarHeight(0);
    }
    
    ~IRMainWindow()
    {
        
        
    }
    
    virtual AudioSource& getMixer() = 0;

    
    // ==================================================
    
    void paint(Graphics& g) override
    {
        
        g.fillAll(Colours::yellow);
        getLookAndFeel().drawDocumentWindowTitleBar(*this, g, getWidth(), 200, 100, 100, nullptr, false);
    }
    
    void resized() override
    {
    }
    
    // remove Border size
    BorderSize<int> getBorderThickness() override
    {
        return BorderSize<int>();
    }
    // ==================================================
    
    void mouseDrag(const MouseEvent &e) override
    {
    }
    
    // ==================================================
private:
};

#endif /* IRWindow_hpp */
