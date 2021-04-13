//
//  IRMouseGrid.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 21/05/2019.
//

#ifndef IRMouseGrid_h
#define IRMouseGrid_h


#include "JuceHeader.h"
#include "ColourLib.h"

class IRMouseGrid : public Component
{
public:
    IRMouseGrid()
    {
        
    }
    
    ~IRMouseGrid()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        g.setColour(Colours::greenyellow);
        g.drawLine(0, this->mousePos.getY(), getWidth(), this->mousePos.getY(), 2);
        g.drawLine(this->mousePos.getX(), 0, this->mousePos.getX(), getHeight(), 2);
    }
    
    void resized() override
    {
        
    }
    
    void setMousePosition(juce::Point<int> pos)
    {
        this->mousePos = pos;
        repaint();
    }
private:
    
    juce::Point<int> mousePos;
    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

};

#endif /* IRMouseGrid_h */
