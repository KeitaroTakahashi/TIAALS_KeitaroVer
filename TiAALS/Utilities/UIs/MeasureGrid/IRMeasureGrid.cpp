//
//  IRMeasureGrid.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 30/05/2019.
//

#include "IRMeasureGrid.hpp"

IRMeasureGrid::IRMeasureGrid(IRStr *str, IRGridStr::IRMeasureGridType type) :
IRStrComponent(str),
type(type)
{
    
}

IRMeasureGrid::~IRMeasureGrid()
{
    
}
// ==================================================

void IRMeasureGrid::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    
    g.setColour(getStr()->SYSTEMCOLOUR.titleText);
    for(auto grid : gridBuffer)
    {
        //Line<float> l = grid.line;
        //std::cout << "grid draw : x y w h " << l.getStartX() << ", " << l.getStartY() << ", " << l.getEndX() << ", " << l.getEndY() << std::endl;
        g.drawLine(grid.line);
    }
}

void IRMeasureGrid::resized()
{
    createGrids();

}
// ==================================================

void IRMeasureGrid::setRange(float min, float max)
{
    jassert(min < max);
    this->minRange = min;
    this->maxRange = max;
}

void IRMeasureGrid::setSmallGridInterval(float interval)
{
    jassert(interval > 0);
    this->smallGridInterval = interval;
}

void IRMeasureGrid::initGrids()
{
    this->gridBuffer.clear();
}
void IRMeasureGrid::createGrids()
{
    initGrids();
    
    float range = this->maxRange - this->minRange;
    float yIncrement = (float)getHeight() / (range / this->smallGridInterval);
    float xIncrement = (range / this->smallGridInterval);
    
    
    int numGrid = 0;
    if(this->type == IRGridStr::IRMeasureGridType::VERTICAL)
        numGrid = floor(range / this->smallGridInterval);
    else if(this->type == IRGridStr::IRMeasureGridType::HORIZONTAL)
        numGrid = floor(getWidth() / this->smallGridInterval);

    
    int i;
    Line<float>line;
    
    //std::cout << "createGrids numGrid = " << numGrid << " : xIncrement " << xIncrement << " : yIncrement " << yIncrement << std::endl;

    for(i=0;i<numGrid;i++)
    {
        //this->smallGridInterval = this->defaultSmallLineLength;
        float x = xIncrement * (float)i;
        float y = yIncrement * (float)i;

        float value = (float)i * this->smallGridInterval;

 
        if (!(i%this->largeGridInterval)) // large
        {
            if(this->type == IRGridStr::IRMeasureGridType::VERTICAL)
                line = Line<float> (getWidth() - this->LargeLineLength, y,
                                    getWidth(), y);
            else if(this->type == IRGridStr::HORIZONTAL)
                line = Line<float> (x, getHeight(),
                                    x, getHeight() - this->LargeLineLength);

            this->gridBuffer.push_back(IRGridStr(value, IRGridStr::IRGridSize::LARGE, line));
        }else if(!(i%this->medGridInterval)) // medium
        {
            if(this->type == IRGridStr::IRMeasureGridType::VERTICAL)
                line = Line<float> (getWidth() - this->medLineLength, y,
                                    getWidth(), y);
            else if(this->type == IRGridStr::HORIZONTAL)
                line = Line<float> (x, getHeight(),
                                    x, getHeight() - this->medLineLength);
            
            this->gridBuffer.push_back(IRGridStr(value, IRGridStr::IRGridSize::MEDIUM, line));
        }else // small
        {
            if(this->type == IRGridStr::IRMeasureGridType::VERTICAL)
                line = Line<float> (getWidth() - this->smallLineLength, y,
                                    getWidth(), y);
            else if(this->type == IRGridStr::HORIZONTAL)
                line = Line<float> (x, getHeight(),
                                    x, getHeight() - this->smallLineLength);
            
            this->gridBuffer.push_back(IRGridStr(value, IRGridStr::IRGridSize::SMALL, line));
        }
    }
    
}

// ==================================================

void IRMeasureGrid::setMarge(int x, int y)
{
    this->margeX = x;
    this->margeY = y;
    
    if(this->type == IRGridStr::IRMeasureGridType::VERTICAL)
        setSize(x + this->LargeLineLength, getHeight());
    else if(this->type == IRGridStr::IRMeasureGridType::HORIZONTAL)
        setSize(getWidth(), y + this->LargeLineLength);

    
}
// ==================================================


// ==================================================
