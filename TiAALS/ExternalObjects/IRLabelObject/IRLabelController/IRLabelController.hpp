//
//  IRLabelController.hpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef IRLabelController_hpp
#define IRLabelController_hpp

#include "IRObjectController.hpp"
#include "FontController.h"

class IRLabelController : public IRObjectController,
public ChangeBroadcaster
{
public:
    
    IRLabelController(IRStr* str);
    ~IRLabelController();

    void ControllerResized() override;
    void paint(Graphics& g) override;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
        
    FontController* getFontController();

        
private:

    Label LabelTitle;
    
        // FontGUI* fontGUI;
    std::unique_ptr<FontController> fontController;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRLabelController)

};

#endif /* IRLabelController_hpp */
