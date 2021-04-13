//
//  IRComponentBase.cpp
//  TiAALS - App
//
//  Created by Keitaro on 24/01/2021.
//

#include "IRObjectBase.hpp"
// ----------------------------------------

IRObjectBase::IRObjectBase(Component *parent,
             String name,
             IRStr* str,
             IRBoundType boundType) : parent(parent)
{
    setBoundType(boundType);
}
IRObjectBase::~IRObjectBase()
{
    
}
// ----------------------------------------

void IRObjectBase::setBoundType(IRBoundType type)
{
    this->bType = type;
}

// ----------------------------------------

void IRObjectBase::setInitialBounds(Rectangle<float> initialBounds)
{
    this->originalAspect = (float)initialBounds.getHeight() / (float)initialBounds.getWidth();

    this->initialBounds = divRectangle(initialBounds, this->zoomRatio);

}


void IRObjectBase::setObjectCentredPosition(int x, int y, NotificationType n)
{
    int fx = getWidth() / 2;
    int fy = getHeight() / 2;
    setObjectBounds(x - fx, y - fy, getWidth(), getHeight());
    
    // NEED TO IMPLEMENT THIS LATER!!!
    //updateResizingSquare();
    
    aboutToMoveAction();
    if(this->aboutToMoveCallback != nullptr)
        this->aboutToMoveCallback();
    
    if(n == NotificationType::sendNotification)
    {
        ObjectBoundsChanged(Rectangle<int>(x - getWidth()/2, y - getHeight()/2,
                                           getWidth(), getHeight()));
        
    }
    
    // update initial bounds
    this->setInitialBounds(getBounds().toFloat());
}

void IRObjectBase::boundChangeTask(Rectangle<int> bounds, NotificationType n)
{
    if(this->bType == ABSOLUTE)
    {
        setBounds(bounds);
        
        
        /*
        if(this->parent != nullptr)
        {

            //update relative bounds to parent
            Rectangle<int> pb = this->parent->getBounds();
            Rectangle<float> b ((float)bounds.getX() / (float)pb.getWidth(),
                                (float)bounds.getY() / (float)pb.getHeight(),
                                (float)bounds.getWidth() / (float)pb.getWidth(),
                                (float)bounds.getHeight() / (float)pb.getHeight());
            setObjectBoundsRelative(b);
            
        }*/
        //std::cout << "ORDINARY\n";

        
    }else if(this->bType == RELATIVE)
    {
        
        //setBoundsRelative(this->relativeBoundsToParent);
    }
    
    // at the end, do rotate if angle is given
    doRotate(true, this->rotateAngle);
    
    //updateResizingSquare();
    
    aboutToResized();
    
    if(n == sendNotification) ObjectBoundsChanged(bounds);

}


void IRObjectBase::setObjectBounds(Rectangle<int> bounds, NotificationType n)
{
    this->setInitialBounds(bounds.toFloat());
    boundChangeTask(bounds, n);

}

void IRObjectBase::setObjectBounds(int x, int y, int w, int h, NotificationType n)
{
    Rectangle<int> bounds(x,y,w,h);
    setObjectBounds(bounds, n);
}

void IRObjectBase::setObjectTopLeftPosition(int x, int y, NotificationType n)
{
    setObjectBounds(x, y, getWidth(), getHeight(), n);
}


void IRObjectBase::setObjectTopLeftPositionRelative(float x, float y)
{
    auto b = this->getObjectBoundsRelative();
    setObjectBoundsRelative(x, y, b.getWidth(), b.getHeight());
}


void IRObjectBase::setObjectBoundsRelative(Rectangle<float> ratioBounds)
{
    
    this->relativeBoundsToParent = ratioBounds;
}

void IRObjectBase::setObjectBoundsRelative(float x, float y, float w, float h)
{
    setObjectBoundsRelative(Rectangle<float> (x, y, w, h));
}

void IRObjectBase::setObjectSize(int w, int h, NotificationType n)
{
    Rectangle<int> bounds(getX(),getY(),w,h);
    setObjectBounds(bounds, n);
}

void IRObjectBase::zoomObjectByRatio(float ratio, bool wZoom, bool hZoom, bool isCallback)
{
    
    this->zoomRatio = ratio;
    
    float x = (float)this->initialBounds.getX();
    float y = (float)this->initialBounds.getY();
    float w = (float)this->initialBounds.getWidth();
    float h = (float)this->initialBounds.getHeight();
    
    float newW = w / ratio;
    float newH = h;
    if(hZoom) newH = newW * this->originalAspect;
    
    float newX = x / ratio;
    float newY = y;
    
    if(hZoom) newY = y / ratio;
    
    if(newW <= 0) newW = 1;
    if(newH <= 0) newH = 1;
    setObjectBoundsByRatioChange(Rectangle<int>(newX, newY, newW, newH));
    
    if(isCallback)
    {
        // call virtual method which affects unique nodeObject setting
        zoomRatioChanged(ratio);
    }
}

void IRObjectBase::setObjectBoundsByRatioChange(Rectangle<int>bounds)
{
    boundChangeTask(bounds);
}

// ----------------------------------------

void IRObjectBase::resized()
{
    
    
    
    resizedOrMoved();
    onResized();
    
    hasResized();
}

void IRObjectBase::moved()
{
    resizedOrMoved();
    onMoved();
    
    hasMoved();
}


// ----------------------------------------

// ----------------------------------------

void IRObjectBase::paint(Graphics& g)
{
    paintOnThis(g);
}

// ----------------------------------------

// ----------------------------------------

void IRObjectBase::setMinimumWidth(const float newMin)
{
    
}
void IRObjectBase::setMinimumHeight(const float newMin)
{
    
}
void IRObjectBase::setMaximumWidth(const float newMax)
{
    
}
void IRObjectBase::setMaximumHeight(const float newMax)
{
    
}
void IRObjectBase::setMinimumSize(const float minWidth, const float minHeight)
{
    setMinimumWidth(minWidth); setMinimumHeight(minHeight);
}
void IRObjectBase::setMaximumSize(const float maxWidth, const float maxHeight)
{
    setMaximumWidth(maxWidth); setMaximumHeight(maxHeight);
}
// ----------------------------------------

// Change status
bool IRObjectBase::isMovable() const
{
    return this->isMovableFlag;
}

bool IRObjectBase::isVerticalMovable() const
{
    return this->isVerticalMovableFlag;
}

bool IRObjectBase::isHorizontalMovable() const
{
    return this->isHorizontalMovableFlag;
}

// all setter
void IRObjectBase::setMovable(bool movable, bool verticalMovable, bool horizontalMovable)
{
    this->isMovableFlag = movable;
    this->isVerticalMovableFlag = verticalMovable;
    this->isHorizontalMovableFlag = horizontalMovable;
}


bool IRObjectBase::isMoving() const
{
    return this->movingFlag;
}


bool IRObjectBase::isDragging() const
{
    return this->draggingFlag;
}



void IRObjectBase::setSize(float width, float height)
{
    float w = width > this->maxWidth ? this->maxWidth : width;
    float h = height > this->maxHeight ? this->maxHeight : height;
    
    
    w = w >= this->minWidth ? w : this->minWidth;
    h = h >= this->minHeight ? h : this->minHeight;
    
    float x = getX();
    float y = getY();
    
    setObjectBounds(x, y, w, h);
    
    
    //updateResizingSquare();
    aboutToResized();
}


void IRObjectBase::setBounds(int x, int y, int w, int h)
{
    Component::setBounds(x, y, w, h);
}

void IRObjectBase::setBounds(Rectangle<int>bounds)
{
    Component::setBounds(bounds);
}

// ==================================================
void IRObjectBase::aboutToResized()
{
    if(this->abountToResizeCallback != nullptr)
        this->abountToResizeCallback();
}

void IRObjectBase::aboutToMoved()
{
    if(this->aboutToMoveCallback != nullptr)
        this->aboutToMoveCallback();
}

void IRObjectBase::hasResized()
{
    if(this->onResizedCallback != nullptr)
        this->onResizedCallback();
}
void IRObjectBase::hasMoved()
{
    if(this->onMovedCallback != nullptr)
        this->onMovedCallback();
}

// ==================================================

Rectangle<float> IRObjectBase::divRectangle(Rectangle<float> bounds, float ratio)
{
    float x = bounds.getX();
    float y = bounds.getY();
    float w = bounds.getWidth();
    float h = bounds.getHeight();
    float newW = w * ratio;
    float newH = newW * this->originalAspect;
    float newX = x * ratio;
    float newY = y * ratio;

    if(!this->widthZoomable)
    {
        newX = x;
        newW = w;
    }
    if(!this->heightZoomable){
        newY = y;
        newH = h;
    }
    
    return  Rectangle<float> (newX, newY, newW, newH);
}

void IRObjectBase::setZoomable(bool width, bool height)
{
    this->widthZoomable = width;
    this->heightZoomable = height;
}

// ==================================================
void IRObjectBase::setRotateAngle(float rotate)
{
    this->rotateAngle = rotate;
    doRotate(true, rotate);
}

void IRObjectBase::doRotate(bool clockwise, float angle)
{
    
    if (! clockwise)
        angle *= -1.0f;
    //setSize(verticalBounds.getHeight(), verticalBounds.getWidth());
    int x = getBounds().getCentreX();
    int y = getBounds().getCentreY();
    //setCentrePosition(0, 0);
    setTransform(AffineTransform::rotation(angle * float_Pi / 180.0, x, y));
}
// ==================================================
