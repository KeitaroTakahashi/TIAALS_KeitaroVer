//
//  IRVNTextEditorObject.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 04/04/2021.
//

#include "IRVNTextEditorObject.hpp"
IRVNTextEditorObject::IRVNTextEditorObject(Component* parent, IRStr* str, IRBoundType boundType) : IRTextEditorObject(parent, str, boundType)
{
    
}

IRVNTextEditorObject::~IRVNTextEditorObject()
{
    
}

void IRVNTextEditorObject::initialiseSetup(String text, Colour colour)
{
    setTextContents(text);
    setBackgroundColour(colour);
    //setAlign(2); // centre
    setTextColour(Colours::white);
    setObjectSize(getWidth(), 25);
}

void IRVNTextEditorObject::initialiseSetup(String text,
                                           Colour colour,
                                           int fontSize)
{
    setTextContents(text);
    setFontSize(fontSize);
    setBackgroundColour(colour);
    //setAlign(2); // centre
    setTextColour(Colours::white);
    setObjectSize(getWidth(), 25);
}
