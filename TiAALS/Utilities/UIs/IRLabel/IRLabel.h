//
//  IRLabel.h
//  TIAALS_LIGHT
//
//  Created by Keitaro on 12/03/2021.
//

#ifndef IRLabel_h
#define IRLabel_h

#include <JuceHeader.h>

class IRLabel : public Label
{
public:
    IRLabel()
    {
        
    }
    
    void setBorderWidth(int newBorderWidth)
    {
        this->borderwidth = newBorderWidth;
    }
    
    void enableBorder(bool flag)
    {
        this->isBorderFlag = flag;
    }
    
    void paint(Graphics& g) override
    {
        Label::paint(g);
        g.setColour(Colours::white);
        if(isBorderFlag)
            g.drawRoundedRectangle(getLocalBounds().toFloat(), this->borderwidth, 2.0f);
    }
    
private:
    int borderwidth = 5;
    
    bool isBorderFlag = false;
};

#endif /* IRLabel_h */
