//
//  LayoutStuff.h
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef LayoutStuff_h
#define LayoutStuff_h
#include "JuceHeader.h"
#include "IRImageButton.hpp"

class LayoutStuff
{
public:
    LayoutStuff(IRStr* str) : str(str)
    {
        
    }
    
    void comboBoxLayout(ComboBox* box)
    {
        
        
        
        box->setColour(ComboBox::backgroundColourId, str->SYSTEMCOLOUR.fundamental);
        box->setColour(ComboBox::textColourId, str->SYSTEMCOLOUR.text);
        box->setColour(ComboBox::arrowColourId, str->SYSTEMCOLOUR.text);
        box->setColour(ComboBox::buttonColourId, str->SYSTEMCOLOUR.fundamental);
        box->setColour(ComboBox::outlineColourId, str->SYSTEMCOLOUR.contents);
        box->setColour(ComboBox::focusedOutlineColourId, str->SYSTEMCOLOUR.contents);
        //c.setColour(ComboBox::focusedOutlineColourId, str->SYSTEMCOLOUR.contents);
    }
    

    
private:
    IRStr* str;
    
    //LookAndFeel_V4 c;

};
#endif /* LayoutStuff_h */
