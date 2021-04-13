//
//  IRViewUI.cpp
//  IRiMaS
//
//  Created by Keitaro on 12/07/2019.
//

#include "IRViewUI.hpp"

IRViewUI::IRViewUI(IRStr* str, Component* main,
                   float vmin, float vmax,
                   float hmin, float hmax) : IRViewPort(str),
verticalGrid(str, IRGridStr::IRMeasureGridType::VERTICAL),
horizontalGrid(str, IRGridStr::IRMeasureGridType::HORIZONTAL)
{
    this->verticalGrid.setRange(vmin, vmax);
    this->horizontalGrid.setRange(hmin, hmax);
    this->viewPort = std::make_shared<Component4ViewPort>(main,
                                                          &this->verticalGrid,
                                                          &this->horizontalGrid,
                                                          this->gridSize);
    setViewedComponent(this->viewPort.get());
}

IRViewUI::~IRViewUI()
{
    
}

void IRViewUI::setComponentBounds(int x, int y, int w, int h)
{
    this->viewPort->setThisBounds(x, y, w, h);
}

void IRViewUI::setVisibleArea(Rectangle<int> area)
{
    this->viewPort->setVisibleArea(area);
}

void IRViewUI::visibleAreaChangedAction(const Rectangle< int > &newVisibleArea)
{
    
    this->viewPort->setHorizontalBounds(newVisibleArea.getX(),
                                        newVisibleArea.getWidth());
}
