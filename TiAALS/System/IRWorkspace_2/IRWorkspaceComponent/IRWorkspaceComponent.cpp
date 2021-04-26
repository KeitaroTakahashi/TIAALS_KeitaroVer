//
//  IRWorkspaceComponent.cpp
//  IRiMaS
//
//  Created by Keitaro on 18/09/2019.
//

#include "IRWorkspaceComponent.hpp"

IRWorkspaceComponent::IRWorkspaceComponent(String title,
                                           Rectangle<int> draggableMargin,
                                           IRStr* str,
                                           int index) :
IRStrComponent(str),
draggableMargin(draggableMargin),
index(index)
{
    
    this->name = title;
    this->title = this->name + " (EDIT MODE)";
    
    this->ir_str = str;
    setOpaque(true);
    
    setMovableMargin(Rectangle<int>(50, 50, 0, 0));
    
    this->controller.reset( new IRWorkspaceController(str) );
    
    setWantsKeyboardFocus(true);
        
    this->controller->addChangeListener(this);

    //createCover();
    
    //give object lists to selector
    this->selector.reset(new IRNodeObjectSelector(&this->objects, this->draggableMargin));
    
    this->selector->setShiftConstrainsDirection(true);
    this->selector->setConstrainBoundsToParent(true, {0,0,10,10});
    
    
    
    this->minSize = Rectangle<int>(0, 0, 400, 400);

    
}


IRWorkspaceComponent::~IRWorkspaceComponent()
{
    std::cout << "workspace destructor called" << std::endl;
    //delete this->objectMenuComponent;
    this->selector.reset();
    this->controller.reset();

    // juce::Array free the memory space as well when cleared.
    for(auto obj : this->objects)
    {
        delete obj;
    }

    this->objects.clear();
    
    //this->objects.clearQuick();
    
    //this->cover.reset();
}


void IRWorkspaceComponent::paint (Graphics& g)
{
    g.fillAll(this->backgroundColour);
    //g.setColour(Colours::white);
    //g.drawRect(getLocalBounds());
    
    // virtual method
    onPaint(g);
    //std::cout << " ++++++ workspace repained! ++++++ " << this->bench.stop() << std::endl;

}

void IRWorkspaceComponent::callResize()
{
    resized();
}

void IRWorkspaceComponent::drawShadows(Graphics& g)
{
    // std::cout << "drawing... shadow of " << this->selector->getSelectedObjectList().size() << " items" << std::endl;
    auto list = this->selector->getSelectedObjectList();
    
    for(auto obj : list)
    {
        DropShadow shadow(getStr()->SYSTEMCOLOUR.contents, 30, juce::Point<int>(0,0));
        
        Rectangle<int> b = obj->getBounds();
        Rectangle<int> bounds(b.getX(), b.getY(), b.getWidth(), b.getHeight());
        
        shadow.drawForRectangle(g, bounds);
        
        // we need to explicitly repaint the area of shadow, otherwise it won't be erased.
        repaint(b.getX()-50, b.getY()-50, b.getWidth()+100, b.getHeight()+100);
    }
}
// ==================================================

void IRWorkspaceComponent::copyAllDataToWorkspace(IRWorkspaceComponent* newWorkspace)
{
    auto w = newWorkspace;
    
    //w->enableDrawGrids(isDrawGrids());
    //w->setGridsBackgroundAlpha(this->gridsBackgroundAlpha);
    
    /*
    if(this->parentNodeObject != nullptr)
    {
        auto p = this->parentNodeObject->copyThis();
        w->setParentNodeObject(p);
    }
    
    for(auto obj : this->objects)
    {
        auto o = obj->copyThis();
        w->createObject(o);
    }*/
    
}

// ==================================================

void IRWorkspaceComponent::initializeWorkspace()
{
    deleteAllObjects();
}

void IRWorkspaceComponent::copyWorkspace(IRWorkspaceComponent* space)
{
    auto objectList = space->objects;
    copyObjectListAndCreateObjects(objectList);
}

void IRWorkspaceComponent::copyObjectListAndCreateObjects(Array<IRNodeObject* > list)
{
    for(auto o : list)
    {
        auto saveData = o->saveThisToSaveData();
        auto obj = o->copyThis();
        auto arrangeCtl = o->getArrangeControllerSaveData();
        obj->loadArrangeControllerSaveData(arrangeCtl);
        
        createObject(obj);
        
        obj->loadThisFromSaveData(saveData);

    }
}

void IRWorkspaceComponent::fullScreenMode(bool isFullScreen)
{
    this->isFullScreenModeFlag = isFullScreen;

    if(isFullScreen) addToDesktop(0);
    else removeFromDesktop();
}


// ==================================================
// APPEARANCE
// ==================================================

void IRWorkspaceComponent::setBackgroundColour(Colour colour)
{
    this->backgroundColour = colour;
    /*
    if(this->cover.get() != nullptr)
        this->cover->setBackgroundColour(this->backgroundColour);
    */
    repaint();
}

// ==================================================

void IRWorkspaceComponent::resized()
{
    // update initial
    this->initialBounds = getBounds().toFloat();
    
    
    //resizeNodeObjectsRelativeToWorkspaceSizeChange();
    
    Rectangle<int>   area = getLocalBounds();
    area.setX       (area.getX() + this->draggableMargin.getX());
    area.setY       (area.getY() + this->draggableMargin.getY());
    area.setWidth   (area.getWidth() + this->draggableMargin.getWidth());
    area.setHeight  (area.getHeight() + this->draggableMargin.getHeight());
    
    this->selector->setDraggableArea(area);
    
    /*
    if(this->cover.get() != nullptr)
    {
        //std::cout << "cover resized : " << getLocalBounds().getWidth() << std::endl;
        this->cover->setBounds(getLocalBounds());
        
    }*/
    
    onResized();
    
  

}

void IRWorkspaceComponent::resizeNodeObjectsRelativeToWorkspaceSizeChange()
{
    if(!this->isFixObjectSizeRatio && this->parentNodeObject != nullptr)
    {
        
        if(this->previousBounds.getWidth() != 0 &&
           this->previousBounds.getHeight() != 0)
        {
            auto wb = this->previousBounds.toFloat();
            float ratioW = this->initialBounds.getWidth() / wb.getWidth();
            float ratioH = this->initialBounds.getHeight() / wb.getHeight();
        
            for(auto obj : this->objects)
            {
                auto ob = obj->getInitialBounds().toFloat();
                Rectangle<float> rb(ob.getX() * ratioW,
                                    ob.getY() * ratioH,
                                    ob.getWidth() * ratioW,
                                    ob.getHeight() * ratioH);
                
                obj->setBoundType(IRBoundType::RELATIVE);
                obj->setObjectBounds(rb.toNearestInt());
                obj->setBoundType(IRBoundType::ABSOLUTE);
                
                
                

                
            }
        }
    }
    setPreviousBounds(getBounds().toFloat());
}

void IRWorkspaceComponent::zoomBasedOn(Rectangle<int>baseBound)
{
    
}
void IRWorkspaceComponent::zoom(const MouseEvent& e, float zoomFactor)
{
    if(this->zoomableByMouseWheel)
    {
        zoomByAffineTransform(e, zoomFactor);
    }else
    {
        //zoomByTraditionalWay(e, zoomFactor);
    }
    
}

void IRWorkspaceComponent::zoomByAffineTransform(const MouseEvent& e, float zoomFactor)
{

    auto p = getTransform();
    
    float wZoom = zoomFactor;
    if(!this->widthZoomable) wZoom = 1.0;
    float hZoom = zoomFactor;
    if(!this->heightZoomable) hZoom = 1.0;

    auto t = AffineTransform(p);
    t = t.translated(-e.getPosition().getX(),
                                          -e.getPosition().getY()).
    scaled(wZoom, hZoom).
    translated(e.getPosition().getX(),
               e.getPosition().getY());
        

    setTransform(t);
    
    // calculate zoomRatio
    
    float currentW = (float)getParentComponent()->getLocalArea(this, getLocalBounds()).getWidth();
    this->zoomRatio = currentW / (float)this->originalBounds.getWidth();

    setGuidValue(this->guideValue);
}
void IRWorkspaceComponent::zoomByTraditionalWay(const MouseEvent& e, float zoomFactor)
{
  
    float m_x = (float)e.getEventRelativeTo(this).getPosition().getX();
    float m_y = (float)e.getEventRelativeTo(this).getPosition().getY();
    
    float x=0;
    float y=0;
    float w = (float)getWidth();
    
    float newW = w * zoomFactor;
    
    
    //std::cout << "zoomFactor = " << zoomFactor << std::endl;
    // adjust width in case smaller than the minimum sise
    float minW = this->minSize.getWidth();
    float minH = this->minSize.getHeight();
    if(newW < minW)
    {
        newW = minW;
    }
    
    this->zoomedWidth = newW;

    float newH = 0;
    
    if(this->heightZoomable) newH = newW * this->originalAspect;
    else newH = (float)getHeight();
    
    if(this->widthZoomable) x = (float)getX() - (m_x * zoomFactor - m_x);
    
    if(newW == minW && this->centerMargin.getX() == 0)
    {
        //x = 0;
    }
    if(this->heightZoomable) y = (float)getY() - (m_y * zoomFactor - m_y);
    if(newH == minH && this->centerMargin.getY() == 0)
    {
        //y = 0;
    }
    
    // calculate zoomRatio
    
    //float currentW = (float)getParentComponent()->getLocalArea(this, getLocalBounds()).getWidth();
    this->zoomRatio = (float)getWidth() / (float)this->originalBounds.getWidth();
    
    setBounds(Rectangle<int>(x, y, newW, newH));

    // adjust object coordinates
    adJustObjectsToZoomRatio();
 
    // update guide value
    setGuidValue(this->guideValue);
}

void IRWorkspaceComponent::setZoomRatio(float zoomRatio)
{
    
    //std::cout << "IRWorkspaceComponent::setZoomRatio = " << zoomRatio << std::endl;
    //auto b = this->originalBounds.toFloat();
    /*
    float x=0;
    float y=0;
    float w = b.getWidth();
    float newW = w * zoomRatio;
    // adjust width in case smaller than the minimum sise
    float minW = this->minSize.getWidth();
    if(newW < minW)
    {
        newW = minW;
    }
    float newH = newW * this->originalAspect;

    this->zoomedWidth = newW;
    
    auto p = getParentComponent();
    
    x = (p->getWidth() - newW) / 2;
    y = (p->getHeight() - newH) / 2;
        setBounds(Rectangle<int>(b.getX()*zoomRatio,
                             b.getY()*zoomRatio,
                             newW,
                             b.getHeight()*zoomRatio));
    
    this->zoomRatio = 1.0 / zoomRatio;
    adJustObjectsToZoomRatio();
     */
    
         
    setTransform(AffineTransform::scale(zoomRatio, zoomRatio));
    this->zoomRatio = zoomRatio;
    
}

void IRWorkspaceComponent::setZoomRatio(float x, float y, float zoomRatio)
{
    
    //reset
    
    
    //auto b = this->originalBounds.toFloat();
    
    setZoomRatio(zoomRatio);
    
    auto t = getTransform();
    
    t = t.withAbsoluteTranslation(x, y);
    setTransform(t);
    

    /*
    float w = b.getWidth();
    float newW = w * zoomRatio;
    // adjust width in case smaller than the minimum sise
    float minW = this->minSize.getWidth();
    if(newW < minW)
    {
        newW = minW;
    }
    float newH = newW * this->originalAspect;
    
    auto p = getParentComponent();

        setBounds(Rectangle<int>(x,
                             y,
                             newW,
                             b.getHeight()*zoomRatio));
    this->zoomedWidth = newW;
    
    this->zoomRatio = 1.0 / zoomRatio;
    adJustObjectsToZoomRatio();
     */
}


void IRWorkspaceComponent::setWidthZoomRatio(float zoomRatio, float height)
{
    
    // reset
    /*
    setZoomRatio(1.0);
    
    // change only height ratio
    setUserDefinedRatio(Rectangle<float>(0, 0, this->aspectRatio.getWidth(), height/100.0));
    
    auto p = getTransform();

    setTransform(AffineTransform::scale(zoomRatio, 1.0));
    */
    
    auto b = this->originalBounds.toFloat();

    float x=0;
    float y=0;
    float w = b.getWidth();
    float newW = w * zoomRatio;
    // adjust width in case smaller than the minimum sise
    float minW = this->minSize.getWidth();
    if(newW < minW)
    {
        newW = minW;
    }
    float newH = (height>0)? height : getHeight();
        
    x = b.getX()*zoomRatio;
    y = b.getY()*zoomRatio;
    
    
        setBounds(Rectangle<int>(0,
                             0,
                             newW,
                             newH));
    
    this->zoomedWidth = newW;
    
    this->zoomRatio = zoomRatio;
    adJustObjectsToZoomRatio();
}

/*
void IRWorkspaceComponent::setExpandRatio(float expandRatio)
{
    //std::cout << "IRWorkspaceComponent::setZoomRatio = " << zoomRatio << std::endl;
    auto b = this->originalBounds.toFloat();

    float x=0;
    float y=0;
    float w = b.getWidth();
    float newW = w * zoomRatio;
    // adjust width in case smaller than the minimum sise
    float minW = this->minSize.getWidth();
    if(newW < minW)
    {
        newW = minW;
    }
    float newH = newW * this->originalAspect;

    
    auto p = getParentComponent();
    
    x = (p->getWidth() - newW) / 2;
    y = (p->getHeight() - newH) / 2;
        setBounds(Rectangle<int>(b.getX()*expandRatio,
                             b.getY()*expandRatio,
                             b.getWidth()*expandRatio,
                             b.getHeight()*expandRatio));
    
    this->zoomRatio = 1.0 / expandRatio;
    adJustObjectsToZoomRatio();
}

*/

void IRWorkspaceComponent::setZoomable(bool width, bool height)
{
    this->widthZoomable = width;
    this->heightZoomable = height;
}

void IRWorkspaceComponent::setWidthZoomableTraditionalWay(bool w)
{
    this->widthZoomableTraditionalWay = w;
}

void IRWorkspaceComponent::setZoomableByMouseWheel(bool flag)
{
    this->zoomableByMouseWheel = flag;
}

void IRWorkspaceComponent::setOriginalBounds(Rectangle<int> originalBounds)
{
    this->originalBounds = originalBounds;
    
    this->zoomedWidth = this->originalBounds.getWidth();
    
    // update bounds if not being resized
    if(!isResizing()) setBounds(this->originalBounds);
    
    this->originalAspect = (float)this->aspectRatio.getHeight()/(float)this->aspectRatio.getWidth();

}

void IRWorkspaceComponent::adJustObjectsToZoomRatio()
{
    bool callbackFlag = true;
    
    // callback is called only when both height and width are zoomable.
    //if(!this->heightZoomable || !this->widthZoomable)
      //  callbackFlag = false;
    
    for(auto obj : getObjectList())
    {
        
        obj->zoomObjectByRatio(this->zoomRatio, this->widthZoomable, this->heightZoomable, callbackFlag);
    }
}

// ==================================================


void IRWorkspaceComponent::setPreviousBounds(Rectangle<float> previousBounds)
{
    this->previousBounds = previousBounds;
}

bool IRWorkspaceComponent::isPreviousBoundsAlreadyGiven() const
{
    if(this->previousBounds.getWidth() == 0 &&
       this->previousBounds.getHeight() == 0)
    {
        return false;
    }else return true;
}

// ==================================================

void IRWorkspaceComponent::setFixObjectSizeRatio(bool flag, Rectangle<float> initialBounds)
{
    this->isFixObjectSizeRatio = flag;
    this->initialBounds = initialBounds;
    std::cout << "setFixObjectSizeRatio IRWorkspace updated\n";
}


// ==================================================
void IRWorkspaceComponent::setDraggableMarginWithInThisComponent()
{
    this->draggableMargin = getLocalBounds();
}

void IRWorkspaceComponent::setDraggableMargin(Rectangle<int> newMargin)
{
    this->draggableMargin = newMargin;
}

void IRWorkspaceComponent::setMovableMargin(Rectangle<int> newMargin)
{
    this->movableMargin = newMargin;
}

void IRWorkspaceComponent::setCenterMargin(Rectangle<int> newMargin)
{
    this->centerMargin = newMargin;
    this->hasCenterMargin = true;
}

void IRWorkspaceComponent::mouseDown(const MouseEvent& e)
{
    //std::cout << "IRWorkspaceComponent mouseDown on " << this->name << " : " << e.getEventRelativeTo(this).getPosition().getX() << ", " << e.getEventRelativeTo(this).getPosition().getY() << " : isEditMode " << isEditMode() << std::endl;
    
    // operate selector process if it is enabled
    if(isSelectorEnabled())
        this->selector->mouseDownHandler(e.getEventRelativeTo(this));
    
    if(isEditMode())
    {
        addAndMakeVisible(this->selector.get());
        this->isMultiSelectMode = true;
        //closeObjectListMenu();
    }
    
    // if workspace empty place is clicked, then send a "nothing selected" signal.
    if(this->selector->getSelectedObjectList().size() == 0)
    {
        callNothingSelected();
    }
    
    this->offsetPos = getParentComponent()->getLocalPoint(this,Point<int>(0,0));
    
    this->offsetBounds = getParentComponent()->getLocalArea(this, getLocalBounds());
       
    //std::cout <<"offsetPos " << this->offsetPos.getX() << ", " << this->offsetPos.getY() << std::endl;
           
    
    std::cout << "localArea " << this->offsetBounds.getX() << ", " << this->offsetBounds.getY() << ", " << this->offsetBounds.getWidth() << ", " << this->offsetBounds.getHeight() << std::endl;
    
}


void IRWorkspaceComponent::mouseMove(const MouseEvent& e)
{
    
    this->currentMousePosition = e.getEventRelativeTo(this).getPosition();
    
   
}


void IRWorkspaceComponent::mouseUp(const MouseEvent& e)
{
    
    //std::cout << "IRWorkspaceComponent mouseUp " << e.getPosition().getX() << ", " << e.getPosition().getY() << std::endl;
    this->selector->mouseUpHandler(e.getEventRelativeTo(this));

    if(isEditMode())
    {
    
        if (this->isMultiSelectMode)
        {
            removeChildComponent(this->selector.get());
            this->isMultiSelectMode = false;
        }
        
        if (this->dummy.size() > 0)
        {
            this->dummy.clear();
        }
        //request updating the workspaceList
        if(requestWorkspaceListUpdate != nullptr) requestWorkspaceListUpdate();
    }
}


void IRWorkspaceComponent::mouseDrag(const MouseEvent& e)
{
    
    //std::cout << "IRWorkspaceComponent mouseDrag\n";
    if(isEditMode())
    {
        this->currentMousePosition = e.getEventRelativeTo(this).getPosition();
        
        if(!this->isResizingFlag){
            this->selector->mouseDragHandler(e.getEventRelativeTo(this));
        }
        
        if(this->dummy.size() > 0)
        {
            for(auto obj : this->dummy)
            {
                obj->setObjectCentredPosition(this->currentMousePosition.getX(),
                                              this->currentMousePosition.getY());
            }
        }
    }
}


void IRWorkspaceComponent::mouseDoubleClick(const MouseEvent& e)
{
    this->currentMousePosition = e.getEventRelativeTo(this).getPosition();
    
    if(isEditMode())
    {
        
        // we need the screen position
        //openObjectListMenu(e.getScreenPosition());
    }
}


void IRWorkspaceComponent::setMouseMagnify(const MouseEvent& e, float scaleFactor)
{
    zoom(e, scaleFactor);
    this->controller->setInitialBounds(getBounds());
}

void IRWorkspaceComponent::setMouseWheelMove(const MouseEvent& e, const MouseWheelDetails& w)
{
    auto p = getParentComponent();
    //get real bounds relative to the parent component
    auto bounds = p->getLocalArea(this, getLocalBounds());
    
    float deltaX = w.deltaX * 200.0;
    float deltaY = w.deltaY * 200.0;
    //float newX = (float)getX() + deltaX;
    //float newY = (float)getY() + deltaY;
    float newX = (float)bounds.getX() + deltaX;
    float newY = (float)bounds.getY() + deltaY;
    
    float width = (float)bounds.getWidth();
    float height = (float)bounds.getHeight();
    
    // center margin
    int c_x = 0;//(p->getWidth() - width) / 2;
    int c_y = 0;//(p->getHeight() - height) / 2;
    
    c_x = this->movableMargin.getX();
    c_y = this->movableMargin.getY();
    
    //std::cout << "margin " << c_x << ", " << c_y << ", " << margin_w << ", " << margin_h << std::endl;

    if(width < p->getWidth())
    {
        if(newX <= c_x) newX = c_x;
        if(newX + width + c_x >= p->getWidth()) newX = p->getWidth() - width - c_x;
    }else{
        
        float surplus = width - p->getWidth();
        if(newX < -(surplus+c_x)) newX = -(surplus+c_x);
        if(newX > c_x) newX = c_x;
        
    }
    
    if(height < p->getHeight())
    {
        newY = ((p->getHeight()) - height)/2.0;
    }else{
        float surplus = height - p->getHeight();
        if(newY < -(surplus+c_y)) newY = -(surplus+c_y);
        if(newY > c_y) newY = c_y;
    }
    
    /*
    // FIX TO THE MOVABLE AREA -----
    // width plus margin is larger than the parent width
    if(p->getWidth() <= (width + margin_w*2))
    {
        if(newX + width + margin_w > p->getWidth() + th1 + margin_w)
        {
            float d = newX - margin_w;
            deltaX = 0;
            
            newX = margin_w;
            
            
        }
        else if(-th1 > newX)
        {
            float d = newX - (-th1);
            deltaX = 0;
            newX = -th1;
        }
    }else if(p->getWidth() > (width + margin_w*2))
    {
        if(newX <= c_x){
            
            float d = newX - c_x;
            deltaX = 0;
            newX = c_x;
            
        }
        else if((newX + width) > p->getWidth() - c_x){
            
            float d = newX - (p->getWidth() - width - c_x);
            deltaX = 0;
            newX = p->getWidth() - width - c_x;
        }
    }

    //height plus margin is larger than the parent height
    if(p->getHeight() <= (getHeight() + margin_h*2))
    {
        if(newY + getHeight() + margin_h > p->getHeight() + th2 + margin_h) newY = margin_h;
        else if(-th2 > newY) newY = -th2;
    }else if(p->getHeight() > (getHeight() + margin_h*2))
    {
        if(newY <= c_y) newY = c_y;
        else if(newY + getHeight() > p->getHeight() - c_y) newY = p->getHeight() - getHeight() - c_y;
    }
    */
    
    if(!this->widthZoomable && width <= p->getWidth()) newX = 0;
    if(!this->heightZoomable && getHeight() <= p->getHeight()) newY = 0;
    
    
    this->controller->setInitialBounds(newX, newY, width, height);
    
    
    if(this->zoomableByMouseWheel)
    {
        wheelByAffineTransform(newX, newY);
    }else{
        wheelByBounds(newX, newY);
    }
    
    
    
    //setTopLeftPosition(newX, newY);
}

void IRWorkspaceComponent::wheelByAffineTransform(float newX, float newY)
{
 
    auto ot = getTransform();
    
    auto t = AffineTransform(ot);

    t = t.withAbsoluteTranslation(newX, newY);
    setTransform(t);

}

void IRWorkspaceComponent::wheelByBounds(float newX, float newY)
{
    
      
       setTopLeftPosition(newX, newY);
}


void IRWorkspaceComponent::modifierKeysChanged(const ModifierKeys &mod)
{
    this->isShiftPressed = false;
    this->isCommandPressed = false;
    this->isControlPressed = false;
    this->isAltPressed = false;
    this->isOptionPressed = false;
    
    if(mod.isShiftDown()) this->isShiftPressed = true;
    if(mod.isCommandDown()) this->isCommandPressed = true;
    if(mod.isCtrlDown()) this->isControlPressed = true;
    if(mod.isAltDown()) this->isAltPressed = true;
    
}

// --------------------------------------------------

void IRWorkspaceComponent::changeListenerCallback (ChangeBroadcaster* source)
{    
    if(source == this->controller.get())
    {
        controllerChanged();
    }else{
        IRNodeObject* obj = dynamic_cast<IRNodeObject* >(source);

        if(obj != nullptr)
        {

            if(obj->isSelected())
            {
                
            }
            
            // if resizing, deselect all objects and setSelect true only the resized object.
            if(obj->isResizing())
            {
                this->selector->deselectOtherObejcts(obj);
                //this->selector->addSelectedObjects();
            }
        }else{ std::cout << "changeListenerCallback object nullptr\n"; }
    }
    
    IRChangeListenerCallback(source);
    
}

void IRWorkspaceComponent::controllerChanged()
{
    using s = IRWorkspaceController::IRWorkspaceControllerStatus;
    
    switch(this->controller->getStatus())
    {
        case s::TITLE:
            titleChangedAction();
            break;
        case s::ASPECT_RATIO:
            aspectRatioChangedAction();
            break;
        case s::BOUNDS:
            break;
        default:
            break;
    }
}

void IRWorkspaceComponent::titleChangedAction()
{
    this->title = this->controller->getTitle();
}

void IRWorkspaceComponent::aspectRatioChangedAction()
{
    auto selectedRatioId = this->controller->getSelectedAspectRatioId();
    
    switch(selectedRatioId)
    {
        case 1: // 1:1
            setUserDefinedRatio(Rectangle<float>(0,0,5,5));
            break;
        case 2: // 3:2
            setUserDefinedRatio(Rectangle<float>(0,0,6,4));
            break;
        case 3: // 4:3
            setUserDefinedRatio(Rectangle<float>(0,0,8,6));
            break;
        case 4: // 16:9
            setUserDefinedRatio(Rectangle<float>(0,0,16,9));
            break;
        case 5: // User defined
            setUserDefinedRatio(this->controller->getAspectRatio());
            break;
        default:
            break;
    }
    
    
    //this->aspectRatio = Rectangle<int> ()
}

void IRWorkspaceComponent::setUserDefinedRatio(Rectangle<float> ratio)
{
    
    // reset zoom
    
    setZoomRatio(1.0);
    
    this->aspectRatio.setWidth(ratio.getWidth());
    this->aspectRatio.setHeight(ratio.getHeight());
    
    int newW = this->aspectRatio.getWidth() * 100;
    int newH = this->aspectRatio.getHeight() * 100;
    
   // auto b = Rectangle<int>(getX(), getY(),
    //                        newW,
     //                       newH);
    
    auto b = Rectangle<int>(0, 0,
                            newW,
                            newH);
    setOriginalBounds(b);
    
    //setBounds(b);
    
    // adjust position of the workspace
    /*
    auto p = getParentComponent();
    
    int x = 0;
    if(x >= 0) x = (p->getWidth() - newW) / 2;
    else x = ratio.getX();
    
    int y = 0;
    if(y >= 0) y = (p->getHeight() - newH) / 2;
    else y = ratio.getY();
    */
    setBounds(b);
    this->controller->setInitialBounds(0, 0, newW, newH);

    /*
    // keep zoom ratio
    this->zoomRatio = 1.0;
    
    
    adJustObjectsToZoomRatio();
    */
    
}

void IRWorkspaceComponent::setBoundsAndCalculateRatio(Rectangle<int> localBounds)
{
    float ratioW = (float)localBounds.getWidth() / 100.0;
    float ratioH = (float)localBounds.getHeight() / 100.0;
    
    int subW = localBounds.getWidth() - (int)ratioW * 100;
    int subH = localBounds.getHeight() - (int)ratioH * 100;
    
    int marginX = subW / 2;
    int marginY = subH / 2;
    
    setUserDefinedRatio(Rectangle<float>(0, 0, ratioW, ratioH));

}

// --------------------------------------------------

void IRWorkspaceComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    this->mixer.getAudioSource().prepareToPlay(samplesPerBlockExpected, sampleRate);
}


void IRWorkspaceComponent::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    this->mixer.getAudioSource().getNextAudioBlock(bufferToFill);
}


void IRWorkspaceComponent::releaseResources()
{
    this->mixer.getAudioSource().releaseResources();
}


AudioSource& IRWorkspaceComponent::getMixer()
{
    return this->mixer.getAudioSource();
}


json11::Json IRWorkspaceComponent::makeSaveDataOfThis()
{
    
    std::cout << "makeSaveDataOfThis" << std::endl;
    std::vector<json11::Json::object> objectList;
    
    // to save objects, we need to reverse the order of ObjectZorder
    // The top object is stored the begining of the vector but it needs to be at the end in order to be created at last.
    std::vector<IRNodeObject*> reversedZorder = this->ObjectZorder;
    std::reverse(std::begin(reversedZorder), std::end(reversedZorder));

    KLib k;
    int index = 0;
    for(auto item : reversedZorder)
    {
        std::string s = k.GetNextNumber("object-", index, 5);
        
        json11::Json::object ob = json11::Json::object({
            {s, json11::Json::object({

                {"objectType",          item->name.toStdString()},
                {"objectUniqueID",      item->getUniqueID().toStdString()},
                {"ArrangeController",   item->getArrangeControllerSaveData()},
                {"Annotation",          item->saveAnnotationData()},
                {"ObjectDefined",       item->saveThisToSaveData()}
                
            })},
        });
        
        objectList.push_back(ob);
    }
    
    json11::Json obList = json11::Json { objectList };
    
    auto ob = this->originalBounds;
    auto ap = this->aspectRatio;
    json11::Json obj = json11::Json::object({
        {"Appearance", json11::Json::object({
            {"backgroundColour", "white"},
            {"sortIndex", getIndex()},
            {"originalBounds", json11::Json::array({ob.getX(), ob.getY(), ob.getWidth(), ob.getHeight()})},
            {"aspectRatio", json11::Json::array({ap.getWidth(), ap.getHeight()})},
            {"zoomRatio", getZoomRatio()}
        })},
        {"Objects", obList},
    });

    
    return obj;
}

void IRWorkspaceComponent::loadThisFromSaveData(json11::Json saveData)
{
    
    auto appearance = saveData["Appearance"];
    auto ap = appearance["aspectRatio"].array_items();
    Rectangle<float> aspectRatio = Rectangle<float>(0,0,ap[0].number_value(), ap[1].number_value());
    setUserDefinedRatio(aspectRatio);
    
    setZoomRatio(1.0);
    
    json11::Json Objects = saveData["Objects"];
    json11::Json::array objectArray = Objects.array_items();


    for (int i = 0; i < objectArray.size(); i++) // for each item of the array...
    {
        for (auto it = objectArray[i].object_items().cbegin(); it != objectArray[i].object_items().cend(); ++it)
        {
            
            std::cout << " ===== " << it->first << " ===== " << std::endl;
            
            // ===== create object =====
            std::string objectTypeId = it->second["objectType"].string_value();
            
            IRNodeObject* obj = static_cast<IRNodeObject*>(getStr()->createNewObject(objectTypeId, this, getStr()));
            

            auto annotation = it->second["Annotation"];
            
            std::cout << "Annotation savedata = " << annotation.dump() << std::endl;
            if(annotation["hasAnnotation"].bool_value())
            {
                std::cout <<"hasAnnotation\n";
                
                auto objData = annotation["annotationObject"];
                
            }else{
                std::cout << "no annotation\n";
            }
            
            
            json11::Json arrangeCtl = it->second["ArrangeController"];
            obj->setZoomRatio(1.0);
            obj->loadArrangeControllerSaveData(arrangeCtl);

            createObject(obj);

            // load save dada
            obj->loadThisFromSaveData(it->second["ObjectDefined"]);
            
            // ===== END =====
        }
    }
    setZoomRatio(1.0);

    
}

// ==================================================

bool IRWorkspaceComponent::isEditMode() const
{
    return this->editModeFlag;
}


void IRWorkspaceComponent::setEditMode(bool flag, bool notification)
{
    
    std::cout << "IRWorkspaceComponent::setEditMode : " << flag << std::endl;
    this->editModeFlag = flag;
    
    // reset all selected objects
    this->selector->deselectAllObjects();
    
    // change cover as well
    setCoverEditMode(flag);
    
    for (auto obj : this->objects)
    {
        obj->setEditMode(flag);
    }
    
    if(this->parentNodeObject != nullptr)
    {
        //this->parentNodeObject->setEditMode(flag);
    }
  
    // notify to IRMainSpace
    if(notification) callEditModeChanged();
    
    
    // send change message to IRProject
    sendChangeMessage();
    
    editModeChangedAction();
    
    repaint();
}

void IRWorkspaceComponent::setActive(bool flag)
{
    for(auto obj : this->objects)
    {
        obj->setWorkspaceActive(flag);
    }
}

Array<IRNodeObject*> IRWorkspaceComponent::getObjectList()
{
    return this->objects;
}

Image IRWorkspaceComponent::getSnap()
{
    this->snap = createComponentSnapshot(Rectangle<int>(0, 0, this->getWidth(), this->getHeight()),
                                         false, 0.4);
    return this->snap;
}


void IRWorkspaceComponent::addListener(Listener* newListener)
{
    this->listeners.add(newListener);
}


void IRWorkspaceComponent::removeListener(Listener* listener)
{
    this->listeners.remove(listener);
}

// ==================================================

Image IRWorkspaceComponent::loadImage(String url)
{
    File file = File(IRPath().getAppContentsDirectoryPath() + url);
    return ImageFileFormat::loadFrom(file);
}


// ==================================================

// ==================================================

void IRWorkspaceComponent::enableDrawGrids(bool flag)
{
    this->isdrawGridsFlag = flag;
    
    //this->cover->enableDrawGrids(flag);
}

void IRWorkspaceComponent::setGridInterval(int thinGrid, int thickGrid)
{
    //this->cover->setGridValue(thinGrid, thickGrid);

}

void IRWorkspaceComponent::setGuidValue(int guid)
{
    this->guideValue = guid;
    if(this->selector != nullptr)
    {
        int g = (float)this->guideValue / this->zoomRatio;
        
        //std::cout << guid << " : setGuideValue = " << g << " : zoomRatio = " << this->zoomRatio << std::endl;
        if(g <= 0) g = 1;
        this->selector->setGuideInterval(g);
    }
}

// ==================================================

void IRWorkspaceComponent::enableTemporalPresentationMode()
{
    std::cout << "enableTemporalPresentationMode\n";
    // first store the current edit mode status
    this->previousMode = isEditMode();
    
    // seocond, enable presemntation mode
    this->temporalPresentationMode = true;
    setEditMode(!this->temporalPresentationMode);
    
    
}

void IRWorkspaceComponent::recoverFromTemporarlPresentationMode()
{
    setEditMode(this->previousMode);
    this->temporalPresentationMode = false;
}

// ==================================================

void IRWorkspaceComponent::recoverBounds()
{
    if(this->isTopWorkspaceFlag)
    {
        auto b = this->controller->getInitialBounds();
        setOriginalBounds(Rectangle<int>(0, 0, b.getWidth(), b.getHeight()));
        setBounds(b);
    }
}

// ==================================================

Rectangle<int> IRWorkspaceComponent::getVisibleArea() const
{
    int visibleX = 0;
    int visibleY = 0;
    int visibleW = 0;
    int visibleH = 0;
    
    int x = getX();
    int y = getY();
    int w = getWidth();
    int h = getHeight();
    
    auto parentBounds = getParentComponent()->getBounds();
    
    if(x > 0) visibleX = 0;
    else visibleX = -x;
    
    if(y > 0) visibleY = 0;
    else visibleY = -y;
    
    if(w + x > parentBounds.getWidth()) visibleW = parentBounds.getWidth();
    else visibleW = w;
    
    if(h + y > parentBounds.getHeight()) visibleH = parentBounds.getHeight();
    else visibleH = h;
    
    return Rectangle<int> (visibleX, visibleY, visibleW, visibleH);
    
}

// ==================================================

void IRWorkspaceComponent::exportThisToPNG()
{
    //KLib().showMessage("Zooming function is cancelled to export this workspace to PNG file.");
    
    setZoomRatio(1.0);
    
    componentExportToImage().exportByDialog(this);
}

// ==================================================

void IRWorkspaceComponent::setAskBeforeDeleteObjectByKeyCommand(bool flag, String message)
{
    this->isAskBeforeDeleteObjectByKeyCommand = flag;
    this->deleteObjectMessage = message;
}
void IRWorkspaceComponent::setAskBeforeCopyObjectByKeyCommand(bool flag, String message)
{
    this->isAskBeforeCopyObjectByKeyCommand = flag;
    this->copyObjectMessage = message;
}
void IRWorkspaceComponent::setAskBeforePasteObjectByKeyCommand(bool flag, String message)
{
    this->isAskBeforePasteObjectByKeyCommand = flag;
    this->pasteObjectMessage = message;
}
void IRWorkspaceComponent::setAskBeforeDuplicateByKeyCommand(bool flag, String message)
{
    this->isAskBeforeDuplicateByKeyCommand = flag;
    this->duplicateObjectMessage = message;
}
void IRWorkspaceComponent::setPreventCreateObjectByKeyCommand(bool flag, String message)
{
    this->isPreventCreateObjectByKeyCommand = flag;
    this->preventCreateObjectMessage = message;
}

// ==================================================

Rectangle<int> IRWorkspaceComponent::getTransformedVisibleArea()
{
    auto p = getParentComponent();
    auto b = p->getLocalArea(this, getLocalBounds());
        
    int x = 0; int y = 0; int w = 0; int h = 0;
    
    int xw = b.getX() + b.getWidth();
    int yh = b.getY() + b.getHeight();
    if(b.getX() < 0)
    {
        x = -b.getX();
        
        if(xw > p->getWidth()) w = p->getWidth();
        else w = xw;
        
    }else{
        x = 0;
        
        if(xw > p->getWidth()) w = p->getWidth() - b.getX();
        else w = b.getWidth();
    }
    
    if(b.getY() < 0)
    {
        y = -b.getY();
        
        if(yh > p->getHeight()) h = p->getHeight();
        else h = yh;
        
    }else{
        y = 0;
        if(yh > p->getHeight()) h = p->getHeight() - b.getY();
        else h = b.getHeight();
    }
    
    return Rectangle<int>(x,y,w,h);
}

// ==================================================
