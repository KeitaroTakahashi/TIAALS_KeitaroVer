//
//  IRObjectResizer.hpp
//  TiAALS - App
//
//  Created by Keitaro on 03/02/2021.
//

// enable object to be resized by square UIs

#ifndef IRObjectResizer_hpp
#define IRObjectResizer_hpp

#include "IRObjectBase.hpp"
#include "IRResizeSquare2.h"

class IRObjectResizer
{
public:
    IRObjectResizer(IRObjectBase* obj,
                    Component* parent,
                    int minWidth,
                    int maxWidth,
                    int minHeight,
                    int maxHeight);
    virtual ~IRObjectResizer();
    
    void bindObjectResizer();
    
    virtual void resizingSquareClickedAction(IRResizeSquare2::MovableDirection direction) {}
    virtual void resizingSquareReleasedAction(IRResizeSquare2::MovableDirection direction) {}
    virtual void resizingSquareDraggedAction(MouseEvent e){}
    void resizingObjectFunc(IRResizeSquare2::MovableDirection direction);
    void setResizableMargin(Rectangle<int> margin);
    void adjustCurrentXYToResizableArea(int& currentX, int& currentY, const MouseEvent& e);
    Rectangle<int> resizableMargin;
    
    IRResizeSquare2 resizingSquare;
    void updateResizingSquare();
    void setResizingSquareColour(Colour colour);
    
    void setEnableResizingSquare(bool flag);
    bool isResizingSquareEnabled() const { return this->enableResizingSquare; }
    
    
    void setEditModeToResizeSquare(bool flag);
    // ==================================================
    //Resizing Square
    // create small square on each corner of the object square which enables to resize this object
    bool isResizingSquareInitialized = false;
    
    void showSquare(bool flag);
    void bringSquareToBack();
    void bringSquareToFront();

    // ==================================================

    bool isResizable() const;
    void setResizable(bool flag, bool isWidthResizableFlag, bool isHeightResizableFlag);
    void setResizable(bool flag) { setResizable(flag, flag, flag); }
    // return a flag shows whether this Component is being resized or not. Default is false.
    bool isResizing() const;
    void setResizingStart(bool flag);
    
    bool isRotating() const;
    void setRotatable(bool flag);
    void setRotatingStart(bool flag);
    
    void setRotateDegree(float amount);
    
    void setAngle(float angle) { this->angle = angle; }
    
private:
    void resizingSquareClicked(IRResizeSquare2::MovableDirection direction);
    // called when resizing square is released (mouse up event)
    void resizingSquareReleased(IRResizeSquare2::MovableDirection direction);
    void resizingSquareDragged(MouseEvent e);

    
    bool enableResizingSquare = true;
    bool isResizableFlag = true;
    bool isWidthResizableFlag = true;
    bool isHeightResizableFlag = true;
    bool resizingFlag = false;
    
    bool isRotatableFlag = true;
    bool rotatingFlag = false;
    
    float rotateAmount = 0;
    IRResizeSquare2::MovableDirection resizeDirection = IRResizeSquare2::MovableDirection::None;
    
    void resizeParentObject(Rectangle<int> newBounds);

    // ==================================================
    void objAboutToResized();
    void objAboutToMoved();
    
    Rectangle<float> calcRotatedXY(float deltaX, float deltaY, float angle);
    // ==================================================

    // resizing method
    // this is virtual method so that you can adjust its behavior to your NodeObject
public: virtual void resizeThisComponentEvent(const MouseEvent& e);
private:
    virtual void resizeTopLeftComponentEvent(const MouseEvent& e);
    virtual void resizeTopRightComponentEvent(const MouseEvent& e);
    virtual void resizeBottomLeftComponentEvent(const MouseEvent& e);
    virtual void resizeBottomRightComponentEvent(const MouseEvent& e);
    
    virtual void resizeLeftComponentEvent(const MouseEvent& e);
    virtual void resizeRightComponentEvent(const MouseEvent& e);
    virtual void resizeTopComponentEvent(const MouseEvent& e);
    virtual void resizeBottomComponentEvent(const MouseEvent& e);


public:
    
    void recoverEventStatus();

    
    juce::Point<float> getResizingArea() const;
    void setResizingArea(juce::Point<float> area);
    
    int getPreviousWidth() const;
    int getPreviousHeight() const;
    
    void setPreviousWidth(int pw) { this->previousWidth = pw; };
    void setPreviousHeight(int ph) { this->previousHeight = ph; };
    
protected:
    // get to know that setResizingStart true and send Change mesaage to the child class
    virtual void setResizingStartFunc() = 0;
    virtual void setResizingCompletedFunc() = 0;
     
private:
    
    IRObjectBase* obj = nullptr;
    Component* parent = nullptr;

    juce::Point<float> resizingArea;

    int minWidth;
    int maxWidth;
    int minHeight;
    int maxHeight;
    
    // for resize event
    float previousWidth = 0;
    float previousHeight = 0;
    float previousX = 0;
    float previousY = 0;
        
    bool isEditModeFlag = false;
    
    float angle = 0.0;
    


};

#endif /* IRObjectResizer_hpp */
