//
//  IRColourSettingIcon.h
//  IRiMaS
//
//  Created by Keitaro on 22/01/2020.
//

#ifndef IRColourSettingIcon_h
#define IRColourSettingIcon_h

#include "IRColourSettingWindow.h"


class IRColourSettingIcon : public Component,
public IRStrComponent,
public ChangeListener,
public ChangeBroadcaster
{
public:
    IRColourSettingIcon(Colour defaultColour, float alpha, IRStr * str) :
    IRStrComponent(str),
    selectedColour(defaultColour.getRed(), defaultColour.getGreen(), defaultColour.getBlue(), alpha)
    {

    }
    
    ~IRColourSettingIcon()
    {
        this->settingWindow.reset();
    }
    // ==================================================

    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
        g.setColour(this->selectedColour);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0);
    }
    
    void resized() override
    {
        
    }
    // ==================================================

    void mouseDown(const MouseEvent& e) override
    {
        openColourSelector();
    }
    // ==================================================

    void openColourSelector()
    {
        if(this->settingWindow.get() == nullptr){
            this->settingWindow.reset(new IRColourSettingWindow(getStr(),
                                                                "Colour",
                                                                Rectangle<int>(0,0,300,200),
                                                                selectedColour));
            this->settingWindow->addChangeListener(this);
        }
        this->settingWindow->open();
    }
    // ==================================================
    void setCurrentColour(Colour newColour)
    {
        this->selectedColour = newColour;
        repaint();
    }
    Colour getCurrentColour() const { return this->selectedColour; }
    // ==================================================
    // ==================================================

private:
    // ==================================================

    void changeListenerCallback(ChangeBroadcaster* source) override
    {
       if(source == this->settingWindow.get())
       {
           this->selectedColour = this->settingWindow->getSelectedColour();
           sendChangeMessage();
           repaint();
       }
    }
           
    // ==================================================

    Colour selectedColour;
    
    std::shared_ptr<IRColourSettingWindow> settingWindow;
};


#endif /* IRColourSettingIcon_h */
