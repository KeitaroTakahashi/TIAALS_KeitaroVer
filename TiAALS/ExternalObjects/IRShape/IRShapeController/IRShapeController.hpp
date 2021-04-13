//
//  IRShapeController.hpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef IRShapeController_hpp
#define IRShapeController_hpp

#include "IRObjectController.hpp"
#include "IRColourSelector.h"
#include "shapeController.h"

class IRShapeController : public IRObjectController,
public ChangeBroadcaster

{
public:
    IRShapeController(IRStr* str);
    ~IRShapeController();

    // ==================================================
    
    void ControllerResized() override;
    void paint(Graphics& g) override;
    
    // ==================================================
    
    // called by IRObjectController
    void mainControllerSelected() override;
    void arrangeControllerSelected() override;
    
    shapeController* getShapeController() { return this->ShapeController.get(); }
    
private:
    std::shared_ptr<shapeController> ShapeController;
    
    void controllerChangeListenerCallback (ChangeBroadcaster* source) override;
   
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRShapeController)

};

#endif /* IRShapeController_hpp */
