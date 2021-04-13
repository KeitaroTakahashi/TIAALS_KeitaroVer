
#include "IRGraphSelector.hpp"





IRGraphSelector::IRGraphSelector()
{
    
}


IRGraphSelector::~IRGraphSelector()
{
    
}


void IRGraphSelector::mouseDownHandler(const MouseEvent& e)
{
    beginSelection(e);
    this->multiSelectionFlag = true;
}


void IRGraphSelector::mouseDragHandler(const MouseEvent& e)
{
    if(this->multiSelectionFlag)
    {
        dragSelection(e);
    }
}


void IRGraphSelector::mouseUpHandler(const MouseEvent& e)
{
    if(this->multiSelectionFlag){
        endSelection(e);
        this->multiSelectionFlag = false;
    }
}


void IRGraphSelector::setMakeSquareObjectAfterSelection(bool flag)
{
    this->makeSquareObjectAfterSelection = flag;
}


bool IRGraphSelector::isMakeSquareObjectAfterSelection() const
{
    return this->makeSquareObjectAfterSelection;
}




