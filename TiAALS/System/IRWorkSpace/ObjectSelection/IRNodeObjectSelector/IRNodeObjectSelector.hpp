//
//  IRNodeObjectSelector.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 22/08/2018.
//

#ifndef IRNodeObjectSelector_hpp
#define IRNodeObjectSelector_hpp

#include "IRObjectSelection.hpp"
#include "IRNodeObject.hpp"


class IRNodeObjectSelector : public IRObjectSelection<IRNodeObject* >
{
    
public:
    // ==================================================

    IRNodeObjectSelector(Array<IRNodeObject* > *list, Rectangle<int> draggableArea);
    ~IRNodeObjectSelector();
    // ==================================================

    void mouseDownHandler(const MouseEvent& e) override;
    void mouseDragHandler(const MouseEvent& e) override;
    void mouseUpHandler(const MouseEvent& e) override;
    // ==================================================

    void selectAllObjects();
    void deselectAllObjects();
    void deselectOtherObejcts(IRNodeObject* selectedObj);
    void addSelectedObjects();
    void addActivatedObjects();
    bool removeSelectedObject(IRNodeObject* removeObj);
    bool removeActivatedObject(IRNodeObject* removeObj);

    // ==================================================

    void repaintAllSelectedObjects();
    
    void judgeSelection(const Rectangle<int>& area, const MouseEvent& e) override;

    Array<IRNodeObject* > getSelectedObjectList() const;
    
    void setDraggableArea(Rectangle<int> area);
    void adaptToDraggableArea(Rectangle<int>& bounds);
    
    // ==================================================
    
    // guide to make the object moved
    void setGuideInterval(int guide) { this->guideInterval = guide; }
    // ==================================================


private:

    // ==================================================
    void nothingSelectedProcess(const MouseEvent& e);
    
    // ==================================================

    
    Rectangle<int> getAreaOfSelectedObj();
    
    Array<IRNodeObject* > selectedObjectList;

    
    Array<IRNodeObject* > *objectList;
    
    bool multiSelectionFlag = false;
    
    Rectangle<int> draggableArea;
    // ==================================================
    
    int guideInterval = 1;
    // ==================================================

    
    IRNodeObject* getNodeObjectFromOriginalComponent(Component* originalComponent);
    // ==================================================
    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRNodeObjectSelector)
    
};




#endif /* IRNodeObjectSelector_hpp */




