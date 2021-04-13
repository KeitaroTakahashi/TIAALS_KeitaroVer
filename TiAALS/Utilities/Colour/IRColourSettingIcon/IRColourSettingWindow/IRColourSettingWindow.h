//
//  IRColourSettingWindow.h
//  IRiMaS
//
//  Created by Keitaro on 22/01/2020.
//

#ifndef IRColourSettingWindow_h
#define IRColourSettingWindow_h

#include "JuceHeader.h"
#include "IRStrComponent.hpp"

class IRColourSettingWindow : public DocumentWindow,
public IRStrComponent,
public ChangeListener,
public ChangeBroadcaster
{
public:
    IRColourSettingWindow(IRStr* str,
                          String name,
                          Rectangle<int>frameRect,
                          Colour defaultColour) :
       DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons),
       IRStrComponent(str),
        colourComponent(defaultColour)
    
    {
        setUsingNativeTitleBar(true);
        setResizable(true, true);
        setName(name);
        setBounds(frameRect);
        
        Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
        setResizeLimits(300, 200, r.getWidth(), r.getHeight());
        
        this->colourComponent.setBounds(0, 0, frameRect.getWidth(), frameRect.getHeight());
        setContentOwned(&this->colourComponent, true);
        this->colourComponent.addChangeListener(this);
        //addKeyListener(&this->colourComponent);
        
    }
    
    ~IRColourSettingWindow()
    {
        
    }
    
    // ==================================================
    void open()
    {
        setVisible(true);
        toFront(true);
    }
    void close()
    {
        setVisible(false);
    }
    // ==================================================
    Colour getSelectedColour() { return this->colourComponent.getColour(); }
    void setSelectedColour(Colour newColour)
    {
        this->colourComponent.setColour(newColour);
    }
    // ==================================================

    
private:
    // ==================================================

    void changeListenerCallback(ChangeBroadcaster* source) override
    {
        if(source == &this->colourComponent)
        {
            
            sendChangeMessage();
        }
    }
    // ==================================================
    
    void closeButtonPressed() override
    {
        close();
    }
    
    // ==================================================

    class IRColourSettingComponent : public Component,
    public ChangeBroadcaster,
    public ChangeListener
    {
    public:
        IRColourSettingComponent(Colour defaultColour)
        {
            addAndMakeVisible(this->colourChart);
            this->colourChart.setCurrentColour(defaultColour);
            this->colourChart.addChangeListener(this);
        }
        
        ~IRColourSettingComponent()
        {
            
        }
        // ==================================================

        void resized() override
        {
            this->colourChart.setBounds(0,0,getWidth(),200);
        }
        // ==================================================

        Colour getColour() { return this->colourChart.getCurrentColour(); }
        void setColour(Colour newColour) { this->colourChart.setCurrentColour(newColour); }
        
    private:
        // ==================================================

        void changeListenerCallback(ChangeBroadcaster* source) override
        {
            if(source == &this->colourChart)
            {
                sendChangeMessage();
            }
        }
        // ==================================================

        ColourSelector colourChart
        {
           ColourSelector::showSliders
           | ColourSelector::showColourspace
           | ColourSelector::showAlphaChannel
        };
    };
    // ==================================================
    // ==================================================
    // ==================================================

    
    IRColourSettingComponent colourComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRColourSettingWindow)

};

#endif /* IRColourSettingWindow_h */
