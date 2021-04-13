//
//  IRWorkspaceController.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 12/03/2021.
//

#ifndef IRWorkspaceController_hpp
#define IRWorkspaceController_hpp

#include "IRObjectController.hpp"
#include "IRWorkspaceControllerUI.h"

class IRWorkspaceController : public IRObjectController,
public ChangeBroadcaster
{
public:
    
    enum IRWorkspaceControllerStatus
    {
        NONE,
        TITLE,
        ASPECT_RATIO,
        BOUNDS
    };
    
    IRWorkspaceController(IRStr* str);
    ~IRWorkspaceController();
    
    void aspectRatioChangedAction(Rectangle<int> aspect);
    void titleChangedAction(String title);
    
    int getSelectedAspectRatioId() const { return this->UI->getSelectedAspectRatioId(); }
    IRWorkspaceControllerStatus getStatus() const { return this->status; }
    
    String getTitle() const;
    Rectangle<int> getInitialBounds() const;
    void setInitialBounds(int x, int y, int w, int h);
    void setInitialBounds(Rectangle<int> bounds);
    Rectangle<float> getAspectRatio() const { return this->UI->getAspectRatio(); }
    void setAspectRatio(Rectangle<float> ratio) { this->UI->setAspectRatio(ratio); }
    
private:
    
    void ControllerResized() override;
    void paint(Graphics& g) override;
    
    
    void controllerChangeListenerCallback (ChangeBroadcaster* source) override;
    
    void UIChangeListener();
    
    // --------------------------------------------------
    std::unique_ptr<IRWorkspaceControllerUI> UI;
    
    IRWorkspaceControllerStatus status = NONE;
    // --------------------------------------------------
    // --------------------------------------------------

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRWorkspaceController)

};

#endif /* IRWorkspaceController_hpp */
