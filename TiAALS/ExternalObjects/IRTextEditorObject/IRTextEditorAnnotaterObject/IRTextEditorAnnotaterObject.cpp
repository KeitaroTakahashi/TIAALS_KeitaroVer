//
//  IRTextEditorAnnotaterObject.cpp
//  IRiMaS
//
//  Created by Keitaro on 19/02/2020.
//

#include "IRTextEditorAnnotaterObject.hpp"

IRTextEditorAnnotaterObject::IRTextEditorAnnotaterObject(Component* parent, IRStr* str, IRBoundType boundType) :
IRTextEditorObject(parent, str)
{
    //this->textEditor.setReadOnly(true);
    
    setEditMode(true);
}

IRTextEditorAnnotaterObject::~IRTextEditorAnnotaterObject()
{
    
}
// ==================================================

void IRTextEditorAnnotaterObject::onResized()
{
    IRTextEditorObject::onResized();
}

void IRTextEditorAnnotaterObject::paint(Graphics& g)
{
    IRTextEditorObject::paint(g);
}


// ==================================================

void IRTextEditorAnnotaterObject::setAnnotationBounds(Rectangle<int> bounds4This,
                                                      Rectangle<int> parentBounds)
{
    // calculate ratio relative to the mediaResolution
    juce::Point<float> ratio = juce::Point<float> ((float)parentBounds.getWidth() / (float)this->mediaResolution.getX(),
                                       (float)parentBounds.getHeight() / (float)this->mediaResolution.getY());
    
    setObjectBounds(bounds4This.getX() * ratio.getX(),
                    bounds4This.getY() * ratio.getY(),
                    bounds4This.getWidth() * ratio.getX(),
                    bounds4This.getHeight() * ratio.getY());
    
}

void IRTextEditorAnnotaterObject::setMediaResolution(int w, int h)
{
    this->mediaResolution.setX(w);
    this->mediaResolution.setY(h);
}
// ==================================================
// ==================================================
