//
//  AutomationController.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#ifndef AutomationController_hpp
#define AutomationController_hpp

#include "JuceHeader.h"

#include "IRStrComponent.hpp"

#include "IRIconBank.hpp"
#include "IRImageButton.hpp"
#include "IRImageMovableButton.hpp"
#include "AutomationVertex.hpp"
#include "IRImageLineButton.h"


class AutomationController : public Component,
public IRStrComponent
{
public:
    
   
    AutomationController(IRStr* str);
    ~AutomationController();
    
    void resized() override;
    void paint(Graphics& g) override;
    
    void setMovableStatus(IRAutomation::movableStatus status);
    
    
    void setZoomInEvent(std::function<void()> callBack);
    void setZoomOutEvent(std::function<void()> callBack);
    void setMovableEvent(std::function<void(IRAutomation::movableStatus)> callBack);
    void setCommentEvent(std::function<void()> callBack);
    void setBezierEvent(std::function<void(IRAutomation::lineStatus)> callBack);
    
    // ==================================================

    // ==================================================

private:
    
    // ==================================================

    IRIconBank& ImageBank = singleton<IRIconBank>::get_instance();

    IRImageButton zoomInButton;
    IRImageButton zoomOutButton;
    
    IRImageMovableButton movableButton;
    
    IRImageButton commentButton;
    
    IRImageLineButton bezierButton;

    // ==================================================

    
    void zoomInClicked();
    void zoomOutClicked();
    
    void commentClicked();
    void bezierClicked();
    
    
    bool isCommentOn = false;
    
    
    int buttonSize = 40;
    int buttonInterval = 5;
    
};

#endif /* AutomationController_hpp */
