//
//  IRShapeUI.cpp
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#include "IRShapeUI.hpp"

IRShapeUI::IRShapeUI(IRNodeObject* parent, IRStr* str) :
IRUIFoundation(parent, str),
colour(255,0, 0)
{

}

IRShapeUI::~IRShapeUI()
{

}

//========================================================

void IRShapeUI::resized()
{

}

void IRShapeUI::paint(Graphics& g)
{
    
    g.fillAll(Colours::transparentWhite);
    g.setColour(this->colour);
    switch ( this->status)
    {
        case SQUARE:
            drawSquare(g);
            break;
        case RHOMBUS:
            drawRhombus(g);
            break;
        case CIRCLE:
            drawCircle(g);
            break;
        case TRIANGLE:
            drawTriangle(g);
            break;
        default:
            break;
    }
    
    
}

//========================================================

void IRShapeUI::drawSquare(Graphics& g)
{
    
    if(this->isFill)
        g.fillRect(getLocalBounds());
    else
        g.drawRect(getLocalBounds(),this->lineWidth);
}

void IRShapeUI::drawRhombus(Graphics& g)
{
    if(this->isFill)
    {
        g.fillRect(getLocalBounds());
        
        
    }else{
        g.drawRect(getLocalBounds(),this->lineWidth);
    }
}

void IRShapeUI::drawBorderSquare(Graphics& g)
{
    if(this->isFill)
        g.fillRect(getLocalBounds());
    else
        g.drawRect(getLocalBounds(),this->lineWidth);
    
}
void IRShapeUI::drawCircle(Graphics& g)
{
    Rectangle<float> area = getLocalBounds().toFloat();
    area.setX(area.getX() + this->lineWidth/2);
    area.setY(area.getY() + this->lineWidth/2);

    area.setWidth(area.getWidth() - this->lineWidth);
    area.setHeight(area.getHeight() - this->lineWidth);

    if(this->isFill)
        g.fillEllipse(area);
    else
        g.drawEllipse(area, this->lineWidth);
}
void IRShapeUI::drawTriangle(Graphics& g)
{

    Path p;
    
    p.startNewSubPath(this->lineWidth/2, this->lineWidth/2);
    p.lineTo(getWidth() - this->lineWidth/2, this->lineWidth/2);
    p.lineTo(getWidth()/2, getHeight() - this->lineWidth/2);
    p.closeSubPath();
    if(this->isFill)
        g.fillPath(p);
    else g.strokePath(p, PathStrokeType(this->lineWidth));
    
}
