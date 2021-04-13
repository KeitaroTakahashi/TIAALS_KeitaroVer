
#include "IRNodeComponent.hpp"


void IRNodeComponent::mouseDownNodeEvent(const MouseEvent& e)
{
    if (e.mods.isCtrlDown())
    {
        if(isEditMode())
        {
            // show popup menu
            defaultPopupMenuEvents();
        }

    }
    else
    {
        //check if a mouse position is the area of resize trigger
        if (e.getMouseDownX() > (getWidth() - this->resizingArea.x) &&
           e.getMouseDownY() > (getHeight() - this->resizingArea.y) &&
           this->isResizable() && this->isEditMode())
        {
            
            setMovable(false, false, false);
            setResizable(true);
            setPreviousWidth(getWidth());
            setPreviousHeight(getHeight());
            
            sendChangeMessage();
            
        }
        else if (this->isMovable())
        {
            
            setMovable(true, true, true);

        }
    }
    
    // call virtual function
    thisObjectGetFocused();
}


void IRNodeComponent::mouseMoveNodeEvent(const MouseEvent& e)
{
    
    //std::cout << "mouse moving : position = " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
    //std::cout << "mouse moving : down position = " << e.getMouseDownX() << ", " << e.getMouseDownY() << std::endl;
}


void IRNodeComponent::mouseDoubleClickNodeEvent(const MouseEvent& e)
{
    
}


void IRNodeComponent::mouseDragNodeEvent(const MouseEvent& e)
{
    if(isEditMode())
    {
    
        if (this->isMovable())
        {            
            moveThisComponentEvent(e);
            
        } else if (this->isResizable())
        {
            resizeThisComponentEvent(e);
        }
    }
}


void IRNodeComponent::mouseUpNodeEvent(const MouseEvent& e)
{
    recoverEventStatus();
}


void IRNodeComponent::moveThisComponentEvent(const MouseEvent& e)
{
    if (isSelected()){
       // this->dragger.dragComponent(this, e, &constrainer);
        
        
        // also move resizingSquare if visible
        if(this->resizingSquare.isVisible())
        {
            updateResizingSquare();
            //std::cout << "resizing square wh = " << this->resizingSquare.getWidth() << ", " << this->resizingSquare.getHeight() << std::endl;

        }
        
        ObjectBoundsChanged(getBounds());
        // call event
        //ObjectPositionChanged(getBounds().getX(), getBounds().getY());
        ObjectPositionChanged4IRNodeObject(getBounds().getX(), getBounds().getY());
        

    }
}

// ==================================================

void IRNodeComponent::resizeThisComponentEvent(const MouseEvent& e)
{
    IRObjectResizer::resizeThisComponentEvent(e);
}


void IRNodeComponent::setSelected(bool flag)
{
    //std::cout << "setSelected " << flag << " of " << name << " : " << this << std::endl;
    // if this object is not visible, then do nothing.
    
    if(!isActive())
    {
        this->selectedFlag = false;
        showSquare(false);
        
        statusChangedCallback(IRNodeComponentStatus::SelectableStatus); // call back
        selectedChangeEvent();
        
        return;

    }
    
    if(!isVisible()) return;
    
    if(this->selectedFlag == flag) return;
    
    this->selectedFlag = flag;

    if(flag)
    {
 
        if(this->isResizingSquareEnabled() && isEditMode()){
            showSquare(true);
            bringSquareToFront();
        }

    }else{
        showSquare(false);
    }
    
    
    statusChangedCallback(IRNodeComponentStatus::SelectableStatus); // call back
    selectedChangeEvent();
}


void IRNodeComponent::defaultPopupMenuEvents()
{
    /*    int result = this->menu->show();
    
    // 999 is reserved for the object name
    switch (result)
    {
        case 1:
            toFront(true);
            break;
        case 2:
            bringToBack();
            break;
        case 3:
            break;
            
        default:
            break;
    }
    
    // user defined events
    popupMenuEvents();
     */
}

// ==================================================

void IRNodeComponent::showThisObject(bool flag)
{
    setVisible(flag);
    
    if(flag)
    {
        if(isEditMode())
        {
            if(this->isResizingSquareEnabled()) showSquare(flag);
            this->selectedFlag = flag;
        }else{
            showSquare(false);
            this->selectedFlag = false;
        }

        if(!this->parent->isParentOf(&this->resizingSquare))
        {
            std::cout << "add child component \n";
            this->parent->addChildComponent(this->resizingSquare);
        }
    }else{
        this->parent->removeChildComponent(&this->resizingSquare);
        
        std::cout << "resizingSquare removed\n";
    }

}


// ==================================================




