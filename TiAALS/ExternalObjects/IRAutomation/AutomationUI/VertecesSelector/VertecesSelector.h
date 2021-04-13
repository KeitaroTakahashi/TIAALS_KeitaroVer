//
//  VertecesSelector.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 30/04/2019.
//

#ifndef VertecesSelector_h
#define VertecesSelector_h

#include "IRObjectSelection.hpp"

#include "AutomationVertex.hpp"

using namespace IRAutomation;

class VertecesSelector : public IRObjectSelection<IRAutomationVertexComponent* >
{
    
public:
    
    VertecesSelector(Array<IRAutomationVertexComponent* > *list, Component* parent)
    {
        this->objectList = list;
        this->parent = parent;
    }
    ~VertecesSelector() {}
    
    void mouseDownHandler(const MouseEvent& e) override
    {
        juce::Point<int> pos = e.getEventRelativeTo(this->parent).getPosition();
        
        IRAutomationVertexComponent* nodeObj = nullptr;
        for(auto obj : *this->objectList)
        {
            bool flag = obj->hitTest(Rectangle<float> (pos.getX(),
                                                       pos.getY(),
                                                       1, 1));
            if(flag)
            {
                nodeObj = obj;
                break;
            }
        }
        
        if (nodeObj != nullptr)
        {
            if (e.mods.isShiftDown() || e.mods.isCommandDown())
            {
                nodeObj->setSelected(! nodeObj->isSelected());
                
            }
            else if (! nodeObj->isSelected()){ // if the object is not yet selected.
                deselectAllObjects(); // CLEAR
                nodeObj->setSelected(true);
            }
            
            //add all selected nodeObj to a list
            addSelectedObjects();
            
            //if this object is selected
            if (nodeObj->isSelected())
            {
                setDragging(true);
                // set this object to be dragged.
                this->setBeingDraggedObject(nodeObj);
                this->mouseDownWithinTarget = e.getEventRelativeTo(nodeObj).getMouseDownPosition();//e.originalComponent->getPosition();//
                this->totalDragDelta = {0,0};
                this->constrainedDirection = noConstraint;
            }
        }
        else
        {
            if (! e.mods.isShiftDown() && ! e.mods.isCommandDown())
            {
                //if background clicked
                deselectAllObjects();
            }
            
            beginSelection(e);
            this->multiSelectionFlag = true;
        }
    }
    
    void mouseDragHandler(const MouseEvent& e) override
    {
        if (this->multiSelectionFlag)
        {
            dragSelection(e);
        }
        else
        {
            if (! isDragging()) return;
            
            juce::Point<int> delta = e.getEventRelativeTo(getBeingDraggedObject()).getPosition() - this->mouseDownWithinTarget;
            
            if(! isVerticalMovable) delta.setY(0);
            if(! isHorizontalMovable) delta.setX(0);
            
            for (auto comp: this->selectedObjectList)
            {
                if (comp != nullptr)
                {
                    Rectangle<int> bounds (comp->getBounds());
                    bounds += delta;
                    
                    bounds = boundsConstrainAboveZero(bounds);
                    bounds = boundsConstrainWithinParent(bounds);
                    
                    comp->setBounds(bounds);
                    //comp->setPosition(juce::Point<float>(bounds.getX(), bounds.getY()));
                }
            }
            this->totalDragDelta += delta;
        }
    }
    void mouseUpHandler(const MouseEvent& e) override
    {
        // finish dragging action
        if (isDragging()) setDragging(false);
        
        if (this->multiSelectionFlag)
        {
            endSelection(e);
            this->multiSelectionFlag = false;
        }else{
            for(auto comp : this->selectedObjectList)
            {
                Rectangle<float> b = comp->getBounds().toFloat();
                comp->setPosition(juce::Point<float>(b.getX() + b.getWidth()/2, b.getY() + b.getHeight()/2));
            }
        }
    }
    
    void deselectAllObjects()
    {
        this->selectedObjectList.clear();
        for (auto obj : *this->objectList)
        {
            if(obj->isSelected()) obj->setSelected(false);
        }
    }
    void addSelectedObjects()
    {
        this->selectedObjectList.clear();
        for (auto obj : *this->objectList)
        {
            if (obj->isSelected())
            {
                this->selectedObjectList.add(obj);
            }
        }
    }
    bool removeSelectedObject(IRAutomationVertexComponent* removeObj)
    {
        int index = this->selectedObjectList.indexOf(removeObj);
        if (index >= 0)
        {
            this->selectedObjectList.remove(index);
            return true;
        }
        return false;
    }
    
    void judgeSelection(const Rectangle<int>& area, const MouseEvent& e) override
    {
        for (auto item : *this->objectList)
        {
            IRAutomationVertexComponent* obj = static_cast<IRAutomationVertexComponent*>(item);
            
            if (area.intersects(obj->getBounds().toNearestInt()))
            {
                if(e.mods.isShiftDown() || e.mods.isCommandDown())
                {
                    obj->setSelected(! obj->isSelected());
                }
                else
                {
                    obj->setSelected(true);
                }
            }else{
            }
        }
        addSelectedObjects();
    }
    
    Array<IRAutomationVertexComponent* > getSelectedObjectList() const
    {
        return this->selectedObjectList;
    }
    
    void setMovableDirection(bool vertical, bool horizontal)
    {
        this->isVerticalMovable = vertical;
        this->isHorizontalMovable = horizontal;
    }
    
private:
    
    Rectangle<int> getAreaOfSelectedObj()
    {
        if (this->selectedObjectList.size() == 0)
            return Rectangle<int> (0,0,0,0);
        
        Rectangle<int> a = this->selectedObjectList[0]->getBounds();
        
        for (auto obj : this->selectedObjectList)
            if (obj) a = a.getUnion(obj->getBounds());
        
        return a;
    }
    Array<IRAutomationVertexComponent* > selectedObjectList;
    Array<IRAutomationVertexComponent* > *objectList;
    bool multiSelectionFlag = false;
    bool isVerticalMovable = true;
    bool isHorizontalMovable = true;
    Component* parent;
    Rectangle<int> boundsConstrainAboveZero(Rectangle<int> rect)
    {
        Rectangle<int> newRect = rect;
        int wh = rect.getWidth()/2;
        int hh = rect.getHeight()/2;
        if(rect.getX() < 0 - wh) newRect.setX(0 - wh);
        if(rect.getY() < 0 - hh) newRect.setY(0 - hh);
        
        
        return newRect;
    }
    Rectangle<int> boundsConstrainWithinParent(Rectangle<int> rect)
    {
        Rectangle<int> newRect = rect;
        int wh = rect.getWidth()/2;
        int hh = rect.getHeight()/2;
        
        if(rect.getX() > (this->parent->getWidth() - wh)) newRect.setX(this->parent->getWidth() - wh);
        if(rect.getY() > this->parent->getHeight() - hh) newRect.setY(this->parent->getHeight() - hh);
        
        return newRect;
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VertecesSelector)
    
};
#endif /* VertecesSelector_h */
