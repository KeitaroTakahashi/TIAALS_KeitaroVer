//
//  IRNodeObjectWorkspace.cpp
//  IRiMaS
//
//  Created by Keitaro on 10/03/2020.
//

#include "IRNodeObjectWorkspace.hpp"

IRNodeObjectWorkspace::IRNodeObjectWorkspace(String title, Rectangle<int> draggableMargin, IRStr* str) :
IRWorkspaceComponent(title, draggableMargin, str)
{
    enableDrawGrids(false);
    setGridsBackgroundAlpha(0.0);
    
}

IRNodeObjectWorkspace::~IRNodeObjectWorkspace()
{
    
}


void IRNodeObjectWorkspace::setFixObjectSizeRatioWithOriginalSize(bool flag, Rectangle<float> originalSize)
{
    setFixObjectSizeRatio(flag, originalSize);

}

void IRNodeObjectWorkspace::bindObjectOnWorkspace(IRNodeObject* nodeObj)
{
    nodeObj->setObjectBounds(this->getWidth()/2,
                             this->getHeight()/2,
                             this->getWidth()/2,
                             60);
    
    this->createObject(nodeObj);
    nodeObj->toFront(true);
    this->deselectAllObjects();
    
    nodeObj->setSelected(true);
}

void IRNodeObjectWorkspace::removeObjectOnWorkspace(IRNodeObject* nodeObj)
{
    deleteObject(nodeObj);
}
