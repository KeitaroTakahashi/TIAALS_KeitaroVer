//
//  IRObjectSelection.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 22/08/2018.
//

#ifndef IRObjectSelection_hpp
#define IRObjectSelection_hpp

#include "JuceHeader.h"

template <class SelectableItemType>
class IRObjectSelection : public Component
{
public:
    //==============================================================================

    IRObjectSelection()
    {
        setShiftConstrainsDirection(true);
        setConstrainBoundsToParent(true, {0,0,10,10});
        
    }
    ~IRObjectSelection(){}
    // ------------------------------------------------------------
    // selection mode : default all true
    // # horizontalMovable false = fixed width
    // # verticalMovable false = fixed height
    void setSelectionMode(bool horizontalMovable, bool verticalMovable)
    {
        this->horizontalMovable = horizontalMovable;
        this->verticalMovable = verticalMovable;
    }
    // ------------------------------------------------------------
    // set Parent size to fix width or height of the selection square
    void setParentSize(int w, int h)
    {
        this->parentWidth = w;
        this->parentHeight = h;
    }
    // ------------------------------------------------------------

    // put this method in mouseDown()
    void beginSelection(const MouseEvent& e)
    {
        Rectangle<int> rect(e.getMouseDownX(), e.getMouseDownY(), 1, 1);

        this->selectionArea = rect;
    }
    // ------------------------------------------------------------
    // put this method in mouseDrag()
    void dragSelection(const MouseEvent& e)
    {
        int deltaX = e.getDistanceFromDragStartX();
        int deltaY = e.getDistanceFromDragStartY();
        
        int x = (deltaX > 0) ? e.getMouseDownX() : e.getMouseDownX() + deltaX;
        int y = (deltaY > 0) ? e.getMouseDownY() : e.getMouseDownY() + deltaY;
        
        int w = abs(deltaX);
        int h = abs(deltaY);
        
        if(! this->horizontalMovable)
        {
            x = 0;
            w = this->parentWidth;
        }
        if(! this->verticalMovable)
        {
            y = 0;//this->parentHeight;
            h = this->parentHeight;
        }

        Rectangle<int> rect(x,y,w,h);
        
        this->selectionArea = rect;
        setBounds(x, y, w, h);
        setSize(w,h);
        //std::cout << this << " : x = " << x << " : y = " << y << " : w = " << w << " : h = " << h << std::endl;

    }
    // ------------------------------------------------------------
    // put this method in mouseUp()
    void endSelection(const MouseEvent& e)
    {
        if(! this->isSelectionRectRemainedAfterMouseUp)
        {
            
            judgeSelection(Rectangle<int>(getX(), getY(), getWidth(), getHeight()), e);
         
            if(deleteSquareAfterSelection)
            {
                Rectangle<int> rect(0,0,0,0);
                setBounds(0,0,0,0);
                setSize(0,0);
            
                this->selectionArea = rect;
            }
            

        }
    }
    // ------------------------------------------------------------
    void resized() override
    {
        //setBounds(this->selectionArea.getX(), this->selectionArea.getY(), this->selectionArea.getWidth(), this->selectionArea.getHeight());
    }
    // ------------------------------------------------------------
    enum ColourIds
    {
        fillColour,
        borderColour,
    };
    // ------------------------------------------------------------
    virtual void judgeSelection(const Rectangle<int>& area, const MouseEvent& e )
    {
        
    }
    // ------------------------------------------------------------

    bool hitTest(int, int) override { return false; } // FD - FOR NOW. TO AVOID RETURN TYPE FAULT WARNING
    // ------------------------------------------------------------
    virtual void paint(Graphics& g) override
    {
        g.setColour(Colours::lightgrey);
        g.setOpacity(0.3);
        g.fillAll();        
    }
    
    // ------------------------------------------------------------
  
    virtual void mouseDownHandler(const MouseEvent& e){}

    virtual void mouseDragHandler(const MouseEvent& e){};

    virtual void mouseUpHandler(const MouseEvent& e){};

    // ------------------------------------------------------------
    void deselectAll()
    {
        this->list.removeAll();
    }
    
    // ------------------------------------------------------------
    
    void setBeingDraggedObject(SelectableItemType obj)
    {
        this->beingDraggedObject = obj;
    }
    SelectableItemType getBeingDraggedObject() const { return this->beingDraggedObject; }
    
    bool isDragging() const { return this->dragging; }
    void setDragging(bool flag) { this->dragging = flag; }
    // ------------------------------------------------------------
    void setDeleteSquareAfterSelection(bool flag) { this->deleteSquareAfterSelection = flag; }
    bool getDeleteSquareAfterSelection() const { return this->deleteSquareAfterSelection; }
    // ------------------------------------------------------------
    // ============================================================
    // set
    void setConstrainBoundsToParent(bool constrainToParentSize,
                                    BorderSize<int> amountPermittedOffscreen)
    {
        this->constrainToParent = constrainToParentSize;
        this->amountPermittedOffscreen = amountPermittedOffscreen;
    }
    // ------------------------------------------------------------
    void setShiftConstrainsDirection(bool constrainDirection)
    {
        this->shiftConstrainsDirection = constrainDirection;
    }
    // ------------------------------------------------------------
    void applyDirectionConstraints(const MouseEvent &e, juce::Point<int> &delta)
    {
        if (shiftConstrainsDirection && e.mods.isShiftDown())
        {
            /* xy > 0 == movement mainly X direction, xy < 0 == movement mainly Y direction. */
            int xy = abs(totalDragDelta.x + delta.x) - abs(totalDragDelta.y + delta.y);
            
            /* big movements remove the lock to a particular axis */
            
            if (xy > minimumMovementToStartDrag)
                constrainedDirection = xAxisOnly;
            
            if (xy < -minimumMovementToStartDrag)
                constrainedDirection = yAxisOnly;
            
            if ((xy > 0 && constrainedDirection != yAxisOnly)
                ||
                (constrainedDirection == xAxisOnly))
            {
                delta.y = -totalDragDelta.y; /* move X direction only. */
                constrainedDirection = xAxisOnly;
            }
            else if ((xy <= 0 && constrainedDirection != xAxisOnly)
                     ||
                     constrainedDirection == yAxisOnly)
            {
                delta.x = -totalDragDelta.x; /* move Y direction only. */
                constrainedDirection = yAxisOnly;
            }
            else
            {
                delta = {0, 0};
            }
        }
        else
        {
            constrainedDirection = noConstraint;
            
        }
    }

    // ------------------------------------------------------------

    
    
    /**
     * Adds a specified component as being selected.
     */
    void setSelected(SelectableItemType * component, bool shouldNowBeSelected)
    {
        
        bool isAlreadySelected = isSelected(component);
        
        if (! isAlreadySelected && shouldNowBeSelected)
            selectedComponents.push_back(component);
        
        if (isAlreadySelected && ! shouldNowBeSelected)
            removeSelectedComponent(component);
    }
    
    /** Toggles the selected status of a particular component. */
    void toggleSelection(SelectableItemType * component)
    {
        setSelected(component, ! isSelected(component));
    }
    
    
    
public:
    enum
    {
        noConstraint,
        xAxisOnly,
        yAxisOnly
    } constrainedDirection;
    
    juce::Point<int> mouseDownWithinTarget;
    juce::Point<int> totalDragDelta;
    
    bool constrainToParent = true;
    bool shiftConstrainsDirection = false;
    BorderSize<int> amountPermittedOffscreen;
    
    std::vector<WeakReference<Component>> selectedComponents;
    const int minimumMovementToStartDrag = 10;

private:
    //==============================================================================

    Rectangle<int> selectionArea;
    
    SelectableItemType beingDraggedObject;
    
    bool isSelectionRectRemainedAfterMouseUp = false;
    
    bool dragging = false;
    
    bool horizontalMovable = true;
    bool verticalMovable = true;
    
    bool deleteSquareAfterSelection = true;
    
    int parentWidth = 0;
    int parentHeight = 0;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRObjectSelection)

};

#endif /* IRObjectSelection_hpp */
