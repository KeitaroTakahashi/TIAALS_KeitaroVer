//
//  ResizingSquares.h
//  IRiMaS
//
//  Created by Keitaro on 16/02/2020.
//

#ifndef ResizingSquares_h
#define ResizingSquares_h

#include "JuceHeader.h"
class ResizingSquares : public Component
{
public:
    // @param1 : set a component on which this squares are drawn.
    ResizingSquares(Component* componentToDraw) :
    componentToDraw(componentToDraw)
    {
        
    }
    
    ~ResizingSquares()
    {
        
    }
    
    // ==================================================
    void resized() override
    {
        
    }
    
    void paint(Graphics& g) override
    {
        
    }
    
    // ==================================================
    // ==================================================

    void setSquareSize(int w, int h)
    {
        this->square_w = w;
        this->square_h = h;
    }
    // ==================================================

private:
    // ==================================================
    
    class square : public Component
    {
    public:
        square() {}
        ~square(){}
        
        void resized() override
        {
            
        }
        
        void paint(Graphics& g) override
        {
            g.setColour(Colours::black);
            g.drawRect(getLocalBounds(), 1);
        }
        
        
    };
    

    int square_w = 30;
    int square_h = 30;
    
    Component* componentToDraw = nullptr;
    
    // ==================================================
    
    
    
    // ==================================================
    // ==================================================

};


#endif /* ResizingSquares_h */
