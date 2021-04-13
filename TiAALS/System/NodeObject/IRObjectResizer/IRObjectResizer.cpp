//
//  IRObjectResizer.cpp
//  TiAALS - App
//
//  Created by Keitaro on 03/02/2021.
//

#include "IRObjectResizer.hpp"


IRObjectResizer::IRObjectResizer(IRObjectBase* obj, // object to be resized
                                 Component* parent, // parent where resizer is binded
                                 int minWidth,
                                 int maxWidth,
                                 int minHeight,
                                 int maxHeight) :
resizingSquare(obj, parent), // obj->parent can be nullptr at this moment so give parent itself
obj(obj),
parent(parent),
resizingArea(25, 25),
minWidth(minWidth), maxWidth(maxWidth),
minHeight(minHeight), maxHeight(maxHeight)

{
    this->obj->abountToResizeCallback = [this] { objAboutToResized(); };
    this->obj->aboutToMoveCallback = [this] { objAboutToMoved(); };
    
    

}


IRObjectResizer::~IRObjectResizer()
{
    
}
void IRObjectResizer::bindObjectResizer()
{
    this->parent->addAndMakeVisible(this->resizingSquare);
    showSquare(false);

    this->resizingSquare.resizingSquareClicked = [this] (IRResizeSquare2::MovableDirection direction) { resizingSquareClicked(direction); };
    this->resizingSquare.resizingSquareReleased = [this] (IRResizeSquare2::MovableDirection direction) { resizingSquareReleased(direction); };
    this->resizingSquare.resizingSquareDragged = [this](MouseEvent e){resizingSquareDragged(e);};
}

void IRObjectResizer::resizeThisComponentEvent(const MouseEvent& e)
{
    using t = IRResizeSquare2::MovableDirection;
    switch(this->resizeDirection)
    {
        case t::TopLeft:
            resizeTopLeftComponentEvent(e);
            break;
        case t::TopRight:
            resizeTopRightComponentEvent(e);
            break;
        case t::Top:
            resizeTopComponentEvent(e);
            break;
        case t::Left:
            resizeLeftComponentEvent(e);
            break;
        case t::Right:
            resizeRightComponentEvent(e);
            break;
        case t::Bottom:
            resizeBottomComponentEvent(e);
            break;
        case t::BottomLeft:
            resizeBottomLeftComponentEvent(e);
            break;
        case t::BottomRight:
            resizeBottomRightComponentEvent(e);
            break;
        default:
            break;
    }
}

void IRObjectResizer::setResizableMargin(Rectangle<int> margin)
{
    this->resizableMargin = Rectangle<int>(margin.getX(),
                                         margin.getY(),
                                         margin.getWidth(),
                                         margin.getHeight());
}

void IRObjectResizer::adjustCurrentXYToResizableArea(int& currentX, int& currentY, const MouseEvent& e)
{
    int x = e.getScreenX();
    int y = e.getScreenY();

    int parentX = this->parent->getScreenX();
    int parentY = this->parent->getScreenY();
    
    // margin for the resizable
    int marginX = this->resizableMargin.getX();
    int marginY = this->resizableMargin.getY();
    int marginW = this->resizableMargin.getWidth();
    int marginH = this->resizableMargin.getHeight();

    int xLimit = parentX + marginX;
    int wLimit = parentX + this->parent->getWidth() + marginW;
    
    if(x <= xLimit) x = xLimit;
    else if(x > wLimit) x = wLimit;

    int yLimit = parentY + marginY;
    int hLimit = parentY + this->parent->getHeight() + marginH;
    
    if(y < yLimit) y = yLimit;
    else if(y >= hLimit) y = hLimit;
        
    currentX = x;
    currentY = y;
}


void IRObjectResizer::resizeTopLeftComponentEvent(const MouseEvent& e)
{
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
    
    float deltaX = currentX - e.getMouseDownScreenX();
    float deltaY = currentY - e.getMouseDownScreenY();

    float newWidth = this->previousWidth - deltaX;
    float newHeight = this->previousHeight - deltaY;
    float newX = this->previousX + deltaX;
    float newY = this->previousY + deltaY;
    
    if(newWidth < this->minWidth)
    {
        newX = this->previousX + (this->previousWidth - this->minWidth);
        newWidth = this->minWidth;
    }
    if(newHeight < this->minHeight)
    {
        newY = this->previousY + (this->previousHeight - this->minHeight);
        newHeight = this->minHeight;
    }
    resizeParentObject(Rectangle<int>(newX, newY, newWidth, newHeight));
}

void IRObjectResizer::resizeTopRightComponentEvent(const MouseEvent& e)
{
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
       
    float deltaX = currentX - e.getMouseDownScreenX();
    float deltaY = currentY - e.getMouseDownScreenY();

    float newWidth = this->previousWidth + deltaX;
    float newHeight = this->previousHeight - deltaY;
    float newY = this->previousY + deltaY;
    
    if(newWidth < this->minWidth)
    {
        newWidth = this->minWidth;
    }
    if(newHeight < this->minHeight)
    {
        newY = this->previousY + (this->previousHeight - this->minHeight);
        newHeight = this->minHeight;
    }
    
    Rectangle<int> b2(this->previousX, newY, newWidth, newHeight);
    resizeParentObject(b2);
}
void IRObjectResizer::resizeBottomLeftComponentEvent(const MouseEvent& e)
{
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
    
    float deltaX = currentX - e.getMouseDownScreenX();
    float deltaY = currentY - e.getMouseDownScreenY();

    float newWidth = this->previousWidth - deltaX;
    float newHeight = this->previousHeight + deltaY;
    float newX = this->previousX + deltaX;
    
    if(newWidth < this->minWidth)
    {
        newX = this->previousX + (this->previousWidth - this->minWidth);
        newWidth = this->minWidth;
    }
    if(newHeight < this->minHeight)
    {
        newHeight = this->minHeight;
    }
    resizeParentObject(Rectangle<int>(newX, this->previousY,
                                      newWidth,  newHeight));

}
void IRObjectResizer::resizeBottomRightComponentEvent(const MouseEvent& e)
{
    
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);

    float deltaX = currentX - e.getMouseDownScreenX();
    float deltaY = currentY - e.getMouseDownScreenY();

    float newWidth = this->previousWidth + deltaX;
    float newHeight = this->previousHeight + deltaY;

    if(newWidth < this->minWidth)
    {
       newWidth = this->minWidth;
    }
    if(newHeight < this->minHeight)
    {
       newHeight = this->minHeight;
    }

    resizeParentObject(Rectangle<int>(this->previousX, this->previousY, newWidth, newHeight));
}

void IRObjectResizer::resizeLeftComponentEvent(const MouseEvent& e)
{
    
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
    
    float deltaX = currentX - e.getMouseDownScreenX();

    float newWidth = this->previousWidth - deltaX;
    float newX = this->previousX + deltaX;
    
    if(newWidth < this->minWidth)
    {
        newX = this->previousX + (this->previousWidth - this->minWidth);
        newWidth = this->minWidth;
    }
    
    resizeParentObject(Rectangle<int>(newX, this->previousY,
                                      newWidth, this->previousHeight));
    
}
void IRObjectResizer::resizeRightComponentEvent(const MouseEvent& e)
{

    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
    
    float deltaX = currentX - e.getMouseDownScreenX();

    float newWidth = this->previousWidth + deltaX;
    
    if(newWidth < this->minWidth)
    {
        newWidth = this->minWidth;
    }
    
    resizeParentObject(Rectangle<int>(this->previousX, this->previousY,
                                      newWidth, this->previousHeight));
    
    
}
void IRObjectResizer::resizeTopComponentEvent(const MouseEvent& e)
{
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
    
    float deltaY = currentY - e.getMouseDownScreenY();

    float newHeight = this->previousHeight - deltaY;
    float newY = this->previousY + deltaY;
    
    if(newHeight < this->minHeight)
    {
        newY = this->previousY + (this->previousHeight - this->minHeight);
        newHeight = this->minHeight;
    }
    resizeParentObject(Rectangle<int>(this->previousX, newY,
                                      this->previousWidth, newHeight));
    
}
void IRObjectResizer::resizeBottomComponentEvent(const MouseEvent& e)
{
    int currentX = 0;
    int currentY = 0;
    adjustCurrentXYToResizableArea(currentX, currentY, e);
    
    float deltaY = currentY - e.getMouseDownScreenY();

    float newHeight = this->previousHeight + deltaY;
    
    if(newHeight < this->minHeight)
    {
        newHeight = this->minHeight;
    }
    resizeParentObject(Rectangle<int>(this->previousX, this->previousY,
                                   this->previousWidth, newHeight));
}

// ----------------------------------------
// resizing area
juce::Point<float> IRObjectResizer::getResizingArea() const
{
    return this->resizingArea;
}


void IRObjectResizer::setResizingArea(juce::Point<float> area)
{
    this->resizingArea = area;
}

// ----------------------------------------


int IRObjectResizer::getPreviousWidth() const
{
    return this->previousWidth;
}


int IRObjectResizer::getPreviousHeight() const
{
    return this->previousHeight;
}

// ----------------------------------------


void IRObjectResizer::updateResizingSquare()
{
    int s = this->resizingSquare.getSquareSize() / 2;
    this->resizingSquare.setBounds(this->obj->getBounds().expanded(s));
}

void IRObjectResizer::setResizingSquareColour(Colour colour)
{
    this->resizingSquare.setSquareColour(colour);
}

void IRObjectResizer::setEnableResizingSquare(bool flag)
{
    this->enableResizingSquare = flag;
    
    if(!flag)
    {
        if(this->resizingSquare.isVisible())
        {
            showSquare(false);
        }
    }
    
}

void IRObjectResizer::resizeParentObject(Rectangle<int> newBounds)
{
    
    updateResizingSquare();
    obj->setObjectBounds(newBounds);
}

// ----------------------------------------

void IRObjectResizer::objAboutToResized()
{
    updateResizingSquare();
}
void IRObjectResizer::objAboutToMoved()
{
    updateResizingSquare();
}

// ----------------------------------------

void IRObjectResizer::showSquare(bool flag)
{
    this->resizingSquare.showSquare(flag);
}


void IRObjectResizer::bringSquareToBack()
{
    this->resizingSquare.toBack();
}
void IRObjectResizer::bringSquareToFront()
{
    this->resizingSquare.toFront(true);
}

// ----------------------------------------


void IRObjectResizer::resizingSquareClicked(IRResizeSquare2::MovableDirection direction)
{
    resizingObjectFunc(direction);
    resizingSquareClickedAction(direction);

}

void IRObjectResizer::resizingSquareReleased(IRResizeSquare2::MovableDirection direction)
{
    //std::cout << "resizingSquareReleased : " << direction << std::endl;

    //reset
    resizingObjectFunc(IRResizeSquare2::MovableDirection::None);
    
    resizingSquareReleasedAction(direction);
}

void IRObjectResizer::resizingSquareDragged(MouseEvent e)
{
    //std::cout <<"resizingSquareDragged : dragged!!\n";
    resizeThisComponentEvent(e);
    resizingSquareDraggedAction(e);
}

void IRObjectResizer::setResizable(bool flag, bool isWidthResizableFlag, bool isHeightResizableFlag)
{
    this->isResizableFlag = flag;
    this->isWidthResizableFlag = isWidthResizableFlag;
    this->isHeightResizableFlag = isHeightResizableFlag;
}

bool IRObjectResizer::isResizable() const
{
    return this->isResizableFlag;
}


void IRObjectResizer::resizingObjectFunc(IRResizeSquare2::MovableDirection direction)
{
    using t = IRResizeSquare2::MovableDirection;
    switch (direction)
    {
        case t::TopLeft:
            setResizable(true, true, false);
            setResizingStart(true);
            this->resizeDirection = t::TopLeft;
            break;

        case t::TopRight:
            setResizable(true, true, false);
            setResizingStart(true);
            this->resizeDirection = t::TopRight;
            break;
            
        case t::Top:
            setResizable(true, false, true);
            setResizingStart(true);
            this->resizeDirection = t::Top;
            break;
        case t::Left:
            setResizable(true, false, true);
            setResizingStart(true);
            this->resizeDirection = t::Left;
            break;
        case t::Right:
            setResizable(true, false, true);
            setResizingStart(true);
            this->resizeDirection = t::Right;
            break;
        case t::Bottom:
            setResizable(true, true, true);
            setResizingStart(true);
            this->resizeDirection = t::Bottom;
            break;
        case t::BottomLeft:
            setResizable(true, true, true);
            setResizingStart(true);
            this->resizeDirection = t::BottomLeft;
            break;
        case t::BottomRight:
            setResizable(true, true, true);
            setResizingStart(true);
            this->resizeDirection = t::BottomRight;
            break;
        default:
            setResizable(false, false, false);
            setResizingStart(false);
            break;
    }
}

// ========================================

// return a flag shows whether this Component is being resized or not. Default is false.
bool IRObjectResizer::isResizing() const
{
    return this->resizingFlag;
}

void IRObjectResizer::setResizingStart(bool flag)
{
    
    if(flag)
    {
        this->obj->setMovable(false, false, false);
        //this->isMovableFlag = false;
        this->resizingFlag = true;
        // store the current size
        this->previousWidth = this->obj->getWidth();
        this->previousHeight = this->obj->getHeight();
        this->previousX = this->obj->getX();
        this->previousY = this->obj->getY();
        
        
        // sendChange Message
        setResizingStartFunc();
        
    }else{
        setResizingCompletedFunc();
        recoverEventStatus();
    }
}

bool IRObjectResizer::isRotating() const
{
    return this->rotatingFlag;
}

void IRObjectResizer::setRotatingStart(bool flag)
{
    
}

void IRObjectResizer::setRotatable(bool flag)
{
    this->isRotatableFlag = flag;
}

void IRObjectResizer::setRotateDegree(float amount)
{
    this->rotateAmount = amount;
    
    
    //this->resizingSquare->setTransform(AffineTransform::rotation(amount)
    //.translated(verticalBounds.getCentreX(), verticalBounds.getCentreY()));
    
}


void IRObjectResizer::recoverEventStatus()
{
    if(isResizing())
    {
        this->resizingFlag = false;
        this->obj->setMovable(true, true, true); // recover movableFlag
    }
    
    if(this->obj->isMoving()) this->obj->setMovable(false, false, false);
    
    // important to call bringThisToFront of resizingSquare, so that the square is now on the IRNodeComponent and catch the mouseEvent. The mouseEvent is sent to IRNodeComponent by addMouseListener.
    // Without bringThisToFront, mouseEvent is stolen after enableSquare() at setSelected method and mouseDrag event is not called anymore.
    if(this->isResizingSquareEnabled() && this->isEditModeFlag)
    {
        //this->resizingSquare.bringThisToFront();
        bringSquareToFront();
        
        
    }else{
        
        //this->resizingSquare.toBack();
        //this->resizingSquare.showSquare(false);
        bringSquareToBack();
        showSquare(false);
    }
    
}


void IRObjectResizer::setEditModeToResizeSquare(bool flag)
{
    this->isEditModeFlag = flag;
    if(!flag) this->resizingSquare.showSquare(flag);

}
