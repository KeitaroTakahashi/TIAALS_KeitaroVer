
#include "IRWaveformObjectUI.hpp"




void IRWaveformObjectUI::mouseDown(const MouseEvent& e)
{
    this->previousWidth = getWidth();
    this->previousHeight = getHeight();
    
    mouseDownHandler(e);
    
    // play selected area
    playSelectedArea();
    
    // show controller
  
    if(e.mods.isCtrlDown())
    {
        addAndMakeVisible(&this->controller);
    }else{
        if(this->controller.isVisible())
            removeChildComponent(&this->controller);
    }
}


void IRWaveformObjectUI::mouseDownHandler(const MouseEvent& e)
{
    IRMultiPurposeObject* nodeObj = dynamic_cast<IRMultiPurposeObject* >(e.originalComponent);

    if(nodeObj != nullptr)
    {

        if(e.mods.isShiftDown() || e.mods.isCommandDown())
        {
            nodeObj->setSelected(! nodeObj->isSelected());
        }else if(! nodeObj->isSelected()){ // if the object is not yet selected.
            deselectAllSquareObject(); // CLEAR
            nodeObj->setSelected(true);
        }
        //repaint obj graphics
        nodeObj->repaint();
        
        //add all selected nodeObj to a list
        addSelectedObjects();
        
        
    }
    else
    {
        if (! e.mods.isShiftDown() && ! e.mods.isCommandDown())
        {
            //if background clicked, clear all selected status
            deselectAllSquareObject();
            //add all selected nodeObj to a list
            addSelectedObjects();
        }
        // make selection square
        if (this->selectFlag && ! isEditMode())
        {
            this->selector->mouseDownHandler(e);
            addAndMakeVisible(this->selector.get());
            this->selectModeFlag = true;
        }
    }
 
}


void IRWaveformObjectUI::mouseUp(const MouseEvent& e)
{
    if(this->selectModeFlag && isSelectMode())
    {
        createSquareObject(this->selector->getBounds());
        this->selector->mouseUpHandler(e);
        this->selectModeFlag = false;
    }
    
    mouseUpHandler(e);
}


void IRWaveformObjectUI::mouseUpHandler(const MouseEvent& e)
{
    
    // THIS DOES NOT WORK!!! because mouse event is out of focus when drag out from the object
    if(this->dragdropCalled)
    {

        for(auto obj : this->selectedSquareObjectList)
        {
            this->status = DROPOUT;
            sendChangeMessage();
        }
        
        this->dragdropCalled = false;
    }
}


void IRWaveformObjectUI::mouseDrag(const MouseEvent& e)
{
    if (this->selectModeFlag && isSelectMode())
    {
        this->selector->mouseDragHandler(e);
    }
    mouseDragHandler(e);
}


void IRWaveformObjectUI::mouseDragHandler(const MouseEvent& e)
{
    
    // get position relative to the parent
    int x = e.getEventRelativeTo(this).getPosition().getX();
    int y = e.getEventRelativeTo(this).getPosition().getY();
    
    
    if(x > getWidth()   ||
       x < 0            ||
       y > getHeight()  ||
       y < 0)
    {
        if(! this->dragdropCalled)
        {
            for(auto obj : this->selectedSquareObjectList)
            {
                //this->callDragOutNodeObjectFromParent();
                this->status = DRAGOUT;
                sendChangeMessage();
            }
            this->dragdropCalled = true;
        }
    }
}


void IRWaveformObjectUI::playSelectedArea()
{
    for(auto obj : this->selectedSquareObjectList)
    {
        int displayedBegingSample = getStart() * (int)this->getSampleRate();
        int displaySampleLength = getDisplayDuration() * (int)this->getSampleRate();
        int totalLength = getTotalLength() * (int)this->getSampleRate();

        Rectangle<float> bounds = obj->getBoundsInRatio();
        int startSample     = round((float)displayedBegingSample + (float)displaySampleLength*bounds.getX());
        int durationSample  = round((float)displaySampleLength * bounds.getWidth());
        
        int endSampleIndex = startSample + durationSample;
        if(endSampleIndex > totalLength) durationSample -= (endSampleIndex - totalLength);
        play(startSample, durationSample, this->playOffset, this->looping);
        
        //std::cout << "play data from " << startSample << " for " << durationSample << " : displayedSampleLength = " << displaySampleLength << " : width ratio = " << bounds.getWidth() << std::endl;
    }
}

void IRWaveformObjectUI::playFromBegin()
{
    play();
}


void IRWaveformObjectUI::stopPlaying()
{
   if (this->player->isPlaying())
   {
       stop();
   }
}


