//
//  EditModeButton.h
//  IRiMaS
//
//  Created by Keitaro on 07/10/2019.
//

#ifndef EditModeButton_h
#define EditModeButton_h

#include "JuceHeader.h"

class EditModeButton : public Component
{
public:
    EditModeButton(String text)
    {
        label.setText(text, dontSendNotification);
        label.setJustificationType(Justification::centred);
        addAndMakeVisible(&this->label);
        label.addMouseListener(this, false);
    }
    
    ~EditModeButton()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::transparentWhite);
        g.setColour(Colours::white);
        g.drawRoundedRectangle(1, 1, getWidth() - 2, getHeight() - 2, 4.0, 1);
    }
    
    void resized() override
    {
        this->label.setBounds(getLocalBounds());
    }
    
    void mouseDown(const MouseEvent& e) override
    {
        if(onClick != nullptr) onClick();
    }
    
    void setText(String text)
    {
        label.setText(text, dontSendNotification);
    }
    
    std::function<void()> onClick;
    
    
private:
    Label label;
};

#endif /* EditModeButton_h */
