
#include "IRNodeObjectSelector.hpp"

IRNodeObjectSelector::IRNodeObjectSelector(Array<IRNodeObject* > *list, Rectangle<int> draggableArea) :
draggableArea(draggableArea)
{
    this->objectList = list;
}


IRNodeObjectSelector::~IRNodeObjectSelector()
{
    
}

IRNodeObject* IRNodeObjectSelector::getNodeObjectFromOriginalComponent(Component* originalComponent)
{
    IRNodeObject* nodeObj = dynamic_cast<IRNodeObject* >(originalComponent);
    
    if(nodeObj == nullptr)
    {
        //std::cout << "nodeObj null\n";
        auto p = dynamic_cast<IRResizeSquare2*>(originalComponent);
        if(p == nullptr)
        {
            auto p2 = dynamic_cast<IRResizeSquare2::ResizingItem*> (originalComponent);
            
            if(p2 != nullptr)
            {
                nodeObj = dynamic_cast<IRNodeObject* >(p2->getNodeObject());
                return nodeObj;
            } return nullptr;
        }else
        {
            nodeObj = dynamic_cast<IRNodeObject* >(p->getResizedComponent());
            return nodeObj;
        }
    }else return nodeObj;
}

void IRNodeObjectSelector::mouseDownHandler(const MouseEvent& e)
{
    auto nodeObj = getNodeObjectFromOriginalComponent(e.originalComponent);
    
    if (nodeObj != nullptr)
    {
        if(nodeObj->isVisible())
        {
            if (e.mods.isShiftDown() || e.mods.isCommandDown())
            {
                nodeObj->setSelected(! nodeObj->isSelected());
                
            }else if (! nodeObj->isSelected()){ // if object is not selected.
                
                deselectAllObjects();
                
                nodeObj->setSelected(true);
            }
            
            //repaint obj graphics
            nodeObj->repaint();
            
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
        }else{ // if obj is not visible
            nothingSelectedProcess(e);
        }
    }else{ // if obj is nullptr
        nothingSelectedProcess(e);
    }
}

void IRNodeObjectSelector::nothingSelectedProcess(const MouseEvent& e)
{
    //std::cout << "nodeObj null\n";
    if (! e.mods.isShiftDown() && ! e.mods.isCommandDown())
    {
        //if background clicked
        deselectAllObjects();
    }

    beginSelection(e);
    this->multiSelectionFlag = true;
}


void IRNodeObjectSelector::mouseDragHandler(const MouseEvent& e)
{
    
    //std::cout <<"mouseDragHandler\n";
    if (this->multiSelectionFlag)
    {
        dragSelection(e);
    }
    else
    {
        if (! isDragging()) return;
        
       juce::Point<int> delta = e.getEventRelativeTo(getBeingDraggedObject()).getPosition() - this->mouseDownWithinTarget;
        
        /*
        delta.setX( floor(delta.getX()/this->guideInterval)
                   * this->guideInterval);
        delta.setY( floor(delta.getY()/this->guideInterval)
                   * this->guideInterval);
         */

        for (auto comp: this->selectedObjectList)
        {
            if (comp != nullptr)
            {

                Rectangle<int> bounds (comp->getBounds());
                bounds += delta;
                
                bounds.setX( floor(bounds.getX()/this->guideInterval)
                           * this->guideInterval);
                bounds.setY( floor(bounds.getY()/this->guideInterval)
                           * this->guideInterval);
                
                adaptToDraggableArea(bounds);
                comp->setObjectBounds(bounds);
            }
        }
        
        this->totalDragDelta += delta;
    }
}


void IRNodeObjectSelector::mouseUpHandler(const MouseEvent& e)
{
    // finish dragging action
    if (isDragging()) setDragging(false);
    
    if (this->multiSelectionFlag)
    {
        endSelection(e);
        this->multiSelectionFlag = false;
    }
    repaintAllSelectedObjects();
}

void IRNodeObjectSelector::selectAllObjects()
{
    std::cout << "selectAllObjects\n";
    this->selectedObjectList.clear();
    for (auto obj : *this->objectList)
    {
        obj->setSelected(true);
        obj->repaint();
    }
    
    addSelectedObjects();
}


void IRNodeObjectSelector::deselectAllObjects()
{
    this->selectedObjectList.clear();
    for (auto obj : *this->objectList)
    {
        if(obj->isSelected()) obj->setSelected(false);
        obj->repaint();
    }
}

void IRNodeObjectSelector::deselectOtherObejcts(IRNodeObject* selectedObj)
{
    

    this->selectedObjectList.clear();
    for (auto obj : *this->objectList)
    {
        if(obj != selectedObj)
        {
            if(obj->isSelected()) obj->setSelected(false);
            obj->repaint();
        }
    }
    
    this->selectedObjectList.add(selectedObj);

}



void IRNodeObjectSelector::addSelectedObjects()
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


bool IRNodeObjectSelector::removeSelectedObject(IRNodeObject* removeObj)
{
    int index = this->selectedObjectList.indexOf(removeObj);
    if (index >= 0)
    {
        this->selectedObjectList.remove(index);
        return true;
    }
    return false;
}

void IRNodeObjectSelector::repaintAllSelectedObjects()
{
    for(auto obj : this->selectedObjectList)
    {
        obj->repaint();
    }
    
}


void IRNodeObjectSelector::judgeSelection(const Rectangle<int>& area, const MouseEvent& e)
{
    for (auto item : *this->objectList)
    {
        IRNodeObject* obj = static_cast<IRNodeObject*>(item);
        if (obj->isActive() && area.intersects(obj->getBounds()))
        {
            if(e.mods.isShiftDown() || e.mods.isCommandDown())
            {
                obj->setSelected(! obj->isSelected());
            }
            else
            {
                obj->setSelected(true);
            }
        }
    }
    
    addSelectedObjects();
}


Array<IRNodeObject*> IRNodeObjectSelector::getSelectedObjectList() const
{
    return this->selectedObjectList;
}

// ==================================================

// **** **** PRIVATE METHODS **** **** //

Rectangle<int> IRNodeObjectSelector::getAreaOfSelectedObj()
{
    if (this->selectedObjectList.size() == 0)
        return Rectangle<int> (0,0,0,0);
    
    Rectangle<int> a = this->selectedObjectList[0]->getBounds();
    
    for (auto obj : this->selectedObjectList)
        if (obj) a = a.getUnion(obj->getBounds());
    
    return a;
}
// ==================================================

void IRNodeObjectSelector::setDraggableArea(Rectangle<int> area)
{
    this->draggableArea = area;
}


void IRNodeObjectSelector::adaptToDraggableArea(Rectangle<int>& bounds)
{
    
    // adjust
    if(bounds.getX() < this->draggableArea.getX()) bounds.setX(this->draggableArea.getX());
    int deltaW = (bounds.getX() + bounds.getWidth()) - this->draggableArea.getWidth();
    if(deltaW > 0)
    {
        bounds.setX(bounds.getX() - deltaW);
    }
    
    if(bounds.getY() < this->draggableArea.getY()) bounds.setY(this->draggableArea.getY());
    int deltaH = (bounds.getY() + bounds.getHeight()) - this->draggableArea.getHeight();
    if(deltaH > 0)
    {
        bounds.setY(bounds.getY() - deltaH);
    }
}
