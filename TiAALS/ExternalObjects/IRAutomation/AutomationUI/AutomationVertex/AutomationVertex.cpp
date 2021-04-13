//
//  AutomationVertex.cpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 01/05/2019.
//

#include "AutomationVertex.hpp"

using namespace IRAutomation;

IRAutomationVertexComponent::IRAutomationVertexComponent(IRStr* str, Component* parent) : IRStrComponent(str)
{
    
    setOpaque(false);
    // set how this vertex can be moved by users inputs
    // no move in horizontal way
    setMovable(true, true, false);
}

IRAutomationVertexComponent::~IRAutomationVertexComponent()
{
    if(this->bezier1 != nullptr) delete this->bezier1;
    if(this->bezier2 != nullptr) delete this->bezier2;
}

void IRAutomationVertexComponent::resized()
{
    
    this->constrainer.setMinimumOnscreenAmounts(getHeight(),
                                                getWidth(),
                                                getHeight(),
                                                getWidth());
    
    
    
    
    
}

void IRAutomationVertexComponent::parentResized()
{
    auto newBounds = getBoundsInParent();
    this->constrainer.checkBounds(newBounds, getBoundsInParent(), newBounds, false, false, false, false);
    // this->constrainer.setMinimumOnscreenAmounts(200,200,200,200);
    this->constrainer.setMinimumOnscreenAmounts(getHeight(),
                                                getWidth(),
                                                getHeight(),
                                                getWidth());
}

// ==================================================

void IRAutomationVertexComponent::paint(Graphics& g)
{
    if(this->isPointFlag)
    {
        if(getCondition() == uiSelected) g.setColour(getStr()->SYSTEMCOLOUR.fundamental);
        else g.setColour(getStr()->SYSTEMCOLOUR.contents);
    
        g.fillEllipse(0, 0, getWidth(), getHeight());
    }
}

// ==================================================
// interaction
void IRAutomationVertexComponent::mouseDown(const MouseEvent& e)
{
    //mouseDownNodeEvent(e);
}

void IRAutomationVertexComponent::mouseMove(const MouseEvent& e)
{
    //mouseUpNodeEvent(e);
}

void IRAutomationVertexComponent::mouseUp(const MouseEvent& e)
{
    //mouseUpNodeEvent(e);
}

void IRAutomationVertexComponent::mouseDoubleClick(const MouseEvent& e)
{
   // mouseDoubleClickNodeEvent(e);
}

void IRAutomationVertexComponent::mouseDrag(const MouseEvent& e)
{
    //mouseDragNodeEvent(e); // defines fundamental behavior
}

// ==================================================

void IRAutomationVertexComponent::mouseDownNodeEvent(const MouseEvent& e)
{

    if (this->isMovable())
    {
        // Move this Node Object
        //prepares our dragger to drag this component
        this->dragger.startDraggingComponent(this, e);
        this->movingFlag = true;
    }
    //toFront(true);
}

void IRAutomationVertexComponent::mouseMoveNodeEvent(const MouseEvent& e)
{
    
    //std::cout << "mouse moving : position = " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
    //std::cout << "mouse moving : down position = " << e.getMouseDownX() << ", " << e.getMouseDownY() << std::endl;
}

void IRAutomationVertexComponent::mouseDoubleClickNodeEvent(const MouseEvent& e)
{
    
}

void IRAutomationVertexComponent::mouseDragNodeEvent(const MouseEvent& e)
{
    if (this->isMovable())
    {
        moveThisComponentEvent(e);
    }
}
void IRAutomationVertexComponent::mouseUpNodeEvent(const MouseEvent& e)
{
    recoverEventStatus();
    
}

void IRAutomationVertexComponent::recoverEventStatus()
{
    if(this->isMoving()) this->movingFlag = false;
}

// ==================================================

bool IRAutomationVertexComponent::isMovable() const
{
    return this->isMovableFlag;
}


bool IRAutomationVertexComponent::isVerticalMovable() const
{
    return this->isVerticalMovableFlag;
}


bool IRAutomationVertexComponent::isHorizontalMovable() const
{
    return this->isHorizontalMovableFlag;
}


bool IRAutomationVertexComponent::isMoving() const
{
    return this->movingFlag;
}


bool IRAutomationVertexComponent::isDragging() const
{
    return this->draggingFlag;
}

// all setter
void IRAutomationVertexComponent::setMovable(bool movable, bool verticalMovable, bool horizontalMovable)
{
    this->isMovableFlag = movable;
    this->isVerticalMovableFlag = verticalMovable;
    this->isHorizontalMovableFlag = horizontalMovable;
}


void IRAutomationVertexComponent::moveThisComponentEvent(const MouseEvent& e)
{
    if(isSelected()) this->dragger.dragComponent(this, e, &constrainer);
}
// ==================================================

bool IRAutomationVertexComponent::hitTest(Rectangle<float> area) const
{
    float x = getX() + getWidth() / 2.0;
    float y = getY() + getHeight() / 2.0;
    
    float powX = (x - area.getX()) * (x - area.getX());
    float powY = (y - area.getY()) * (y - area.getY());
    float dist = sqrt (powX + powY);
    if(dist <= (getWidth()/2 + area.getWidth()/2) || dist <= (getHeight()/2 + area.getHeight()/2))
        return true;
    else return false;
    
}

// ==================================================

void IRAutomationVertexComponent::setSelected(bool flag)
{
    if(flag){
        this->condition = uiSelected;
        juce::Point<int> c = getBounds().getCentre();
        setSize(this->selectedSize, this->selectedSize);
        setCentrePosition(c);
    }
    else
    {
        this->condition = uiOrdinary;
        juce::Point<int> c = getBounds().getCentre();
        setSize(this->ordinarySize, this->ordinarySize);
        setCentrePosition(c);
    }
}
bool IRAutomationVertexComponent::isSelected() { if(this->condition == uiSelected) return true; else return false;}

void IRAutomationVertexComponent::setMouseDownPos(juce::Point<int> pos) { this->mouseDownPos = pos; }
juce::Point<int> IRAutomationVertexComponent::getMouseDownPos() const { return this->mouseDownPos; }

// ==================================================

void IRAutomationVertexComponent::setPosition(juce::Point<float>pos)
{
    this->position = pos;
    setCentrePosition(pos.roundToInt());
}

void IRAutomationVertexComponent::setPosition(juce::Point<int>pos)
{
    this->position = pos.toFloat();
    setCentrePosition(pos);
}

void IRAutomationVertexComponent::setPositionEx(juce::Point<float>pos)
{
    this->position = pos;
    setTopLeftPosition(pos.roundToInt());
}



juce::Point<float> IRAutomationVertexComponent::getPosition()
{
    return this->position;
}

// ==================================================
