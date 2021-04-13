//
//  IRVideoAnnotaterController.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 22/03/2021.
//

#ifndef IRVideoAnnotaterController_hpp
#define IRVideoAnnotaterController_hpp

#include "IRObjectController.hpp"
#include "VideoAnnotaterController.h"

class IRVideoAnnotaterController : public IRObjectController
{
public:
    IRVideoAnnotaterController(IRStr* str);
    ~IRVideoAnnotaterController();
    
    
    VideoAnnotaterController* getVideoAnnotaterController() { return this->videoAnnotaterController.get(); }
    
private:
    void ControllerResized() override;
    void paint(Graphics& g) override;
    
    
    // called by IRObjectController
    void mainControllerSelected() override;
    void arrangeControllerSelected() override;

    void controllerChangeListenerCallback (ChangeBroadcaster* source) override;
    
    std::shared_ptr<VideoAnnotaterController> videoAnnotaterController;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRVideoAnnotaterController)

};

#endif /* IRVideoAnnotaterController_hpp */
