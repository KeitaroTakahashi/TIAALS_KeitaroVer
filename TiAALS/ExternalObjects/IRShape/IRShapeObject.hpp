//
//  IRShapeObject.hpp
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#ifndef IRShapeObject_hpp
#define IRShapeObject_hpp

#include "IRNodeObject.hpp"
#include "IRShapeUI.hpp"

#include "Benchmark.h"

class IRShapeObject : public IRNodeObject
{
public:
    IRShapeObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRShapeObject();
    
    IRNodeObject* copyThisObject() override;
    
    t_json saveThisToSaveData() override;
    void loadThisFromSaveData(t_json data) override;
    
    // ------------------------------------------------------------
    void paint(Graphics &g) override;
    void onResized() override;
    // ------------------------------------------------------------
    
    void mouseDownEvent(const MouseEvent& e) override;
    //void mouseUpEvent(const MouseEvent& e) override;
    
protected:
    
    std::shared_ptr<IRShapeUI> UI;

    std::shared_ptr<IRShapeController> controller;

    void IRChangeListenerCallback (ChangeBroadcaster* source) override;
    
    void shapeControllerChangeListenerCallback(ChangeBroadcaster* source);
    void arrangeControllerChangeListenerCallback(ChangeBroadcaster* source);
    
    // ------------------------------------------------------------
    // call back function automatically called when the status of this object changed by others.
    // write some tasks here
    void statusChangedCallback(IRNodeComponentStatus status) override
    {
        switch(status)
        {
            case EditModeStatus:
                break;
            default:
                break;
        }
    
    }
    // ------------------------------------------------------------
    Image capturedImage;
    bool capturedImageReady = false;
    
    // ------------------------------------------------------------
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRShapeObject)
};


#endif /* IRShapeObject_hpp */
