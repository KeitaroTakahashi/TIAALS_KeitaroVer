//
//  IRTextEditorController.hpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef IRTextEditorController_hpp
#define IRTextEditorController_hpp

#include "IRObjectController.hpp"
#include "FontController.h"
#include "ObjectArranger.hpp"

class IRTextEditorController : public IRObjectController,
public ChangeBroadcaster
{
public:
    
    IRTextEditorController(IRStr* str);
    ~IRTextEditorController();

    void ControllerResized() override;
    void paint(Graphics& g) override;
    
        
    FontController* getFontController();

    // called by IRObjectController
    void mainControllerSelected() override;
    void arrangeControllerSelected() override;
        
private:
    // FontGUI* fontGUI;
    std::unique_ptr<FontController> fontController;
    
    void controllerChangeListenerCallback (ChangeBroadcaster* source) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRTextEditorController)

};
#endif /* IRTextEditorController_hpp */
