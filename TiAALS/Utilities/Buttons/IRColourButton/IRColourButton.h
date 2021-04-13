//
//  IRColourButton.h
//  IRiMaS
//
//  Created by Keitaro on 21/10/2019.
//

#ifndef IRColourButton_h
#define IRColourButton_h

#include "JuceHeader.h"
#include "ColourLib.h"

// button designed for selecting the appearance colour

class IRColourButton : public Component
{
public:
    IRColourButton(IR::colorPattern pattern = IR::colorPattern())
    {
        this->pattern = pattern;
    }
    
    ~IRColourButton()
    {
        
    }
    // --------------------------------------------------

    void resized() override
    {
        
    }
    
    void paint(Graphics& g) override
    {
        float w = (float)getWidth();
        float h = (float)getHeight();
        float x = (float)w/2.0;
        float y = (float)h/2.0;
        
        float left = -PI * 0.666666;
        float right = PI * 0.5;

        // fill circle
        g.setColour(pattern.fundamental);
        g.fillEllipse(1, 1, getWidth()-2, getHeight()-2);
        
        // fill a half circle
        g.setColour(pattern.contents);
        Path p;
        p.addCentredArc(x, y,
                        w/2, h/2,
                        0.0,
                        left, right, true);
        
        g.fillPath(p);
        
        g.setColour(Colours::white);
        g.drawEllipse(1, 1, getWidth()-2, getHeight()-2, 1);
        

    }
    // --------------------------------------------------
    void mouseDown(const MouseEvent& e) override
    {
        if(this->onClick != nullptr)
            this->onClick(this);
    }
    
    // --------------------------------------------------
    IR::colorPattern getColourPattern() const { return this->pattern; }
    // --------------------------------------------------

    // --------------------------------------------------
    std::function<void(IRColourButton*)> onClick;
private:
    
    float PI = 3.141592653589793238;
    
    IR::colorPattern pattern;
    
};
#endif /* IRColourButton_h */
