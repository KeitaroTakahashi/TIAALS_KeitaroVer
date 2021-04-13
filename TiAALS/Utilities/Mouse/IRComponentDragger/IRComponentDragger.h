//
//  IRComponentDragger.h
//  IRiMaS
//
//  Created by Keitaro on 02/03/2020.
//

#ifndef IRComponentDragger_h
#define IRComponentDragger_h

#include "IRNodeComponent.hpp"

/*
// JUCE API modified by k
class IRComponentDragger
{
public:
    IRComponentDragger() {}
    virtual ~IRComponentDragger() {}

   
    void startDraggingComponent (IRNodeComponent* componentToDrag,
                                 const MouseEvent& e)
    {
        jassert (componentToDrag != nullptr);
        jassert (e.mods.isAnyMouseButtonDown()); // The event has to be a drag event!
    
        if (componentToDrag != nullptr)
            mouseDownWithinTarget = e.getEventRelativeTo (componentToDrag).getMouseDownPosition();
    }

    
    void dragComponent (IRNodeComponent* componentToDrag,
                        const MouseEvent& e,
                        ComponentBoundsConstrainer* constrainer)
    {
        jassert (componentToDrag != nullptr);
        jassert (e.mods.isAnyMouseButtonDown()); // The event has to be a drag event!
    
        if (componentToDrag != nullptr)
        {
            auto bounds = componentToDrag->getBounds();
    
            // If the component is a window, multiple mouse events can get queued while it's in the same position,
            // so their coordinates become wrong after the first one moves the window, so in that case, we'll use
            // the current mouse position instead of the one that the event contains...
            if (componentToDrag->isOnDesktop())
                bounds += componentToDrag->getLocalPoint (nullptr, e.source.getScreenPosition()).roundToInt() - mouseDownWithinTarget;
            else
                bounds += e.getEventRelativeTo (componentToDrag).getPosition() - mouseDownWithinTarget;
    
            if (constrainer != nullptr)
                constrainer->setBoundsForComponent (componentToDrag, bounds, false, false, false, false);
            else
                componentToDrag->setObjectBounds (bounds);
        }
    }

private:
    Point<int> mouseDownWithinTarget;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRComponentDragger)
};
 */
#endif /* IRComponentDragger_h */
