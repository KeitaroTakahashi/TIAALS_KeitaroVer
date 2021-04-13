//
//  IRImageViewerController.hpp
//  IRiMaS
//
//  Created by Keitaro on 03/10/2019.
//

#ifndef IRImageViewerController_hpp
#define IRImageViewerController_hpp

#include "IRObjectController.hpp"
#include "FontController.h"
#include "ImageController.h"

class IRImageViewerController : public IRObjectController,
public ChangeBroadcaster
{
public:
    
    enum ImageViewerControllerStatus
    {
        OpenImageFile,
        WidthChange,
        HeightChange,
        W_H_Sync,
        NONE
    };
    
    IRImageViewerController(IRStr* str);
    ~IRImageViewerController();

    void ControllerResized() override;
    void paint(Graphics& g) override;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    ImageController::ImageControllerStatus getStatus() const { return this->UI.getStatus(); }
    
    void setChangeListener(ChangeListener* listener) { this->UI.addChangeListener(listener); }
    
private:
    
    // called by IRObjectController
    void mainControllerSelected() override;
    void arrangeControllerSelected() override;

    Label LabelTitle;
    ImageController UI;

    ImageViewerControllerStatus status = NONE;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRImageViewerController)

};
#endif /* IRImageViewerController_hpp */
