//
//  TimeMeasure.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 03/04/2021.
//

#include "TimeMeasure.hpp"

TimeMeasure::TimeMeasure()
{
    
}

TimeMeasure::~TimeMeasure()
{
    
}

// ----------------------------------------

void TimeMeasure::resized()
{
    
}

void TimeMeasure::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    drawIntervalLine(g);
}

void TimeMeasure::drawIntervalLine(Graphics& g)
{
    auto b = getLocalBounds();
    int h = b.getHeight();
    float w = (float)b.getWidth();
    
    if(this->length == 0) return;
    
    float wInterval = this->interval * w / this->length;
    
    // line number
    int n = floor(w / this->interval);
    
    g.setColour(Colours::black);
    for(int i = 0; i < n; i ++)
    {
        int x = n * wInterval;
        g.drawLine(x, 0, x, this->shortLineRatio * h, 1);
    }
}

// ----------------------------------------
void TimeMeasure::setLengthInSec(float sec)
{
    this->length = sec;
    repaint();
}
void TimeMeasure::setIntervalInSec(float sec)
{
    this->interval = sec;
    repaint();
}
// ----------------------------------------
