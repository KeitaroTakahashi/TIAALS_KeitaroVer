//
//  IRSimpleController.hpp
//  IRiMaS
//
//  Created by Keitaro on 23/07/2019.
//

#ifndef IRSimpleController_hpp
#define IRSimpleController_hpp

#include "JuceHeader.h"

#include "IRIconBank.hpp"
#include "IRImageButton.hpp"
#include "IRImageMovableButton.hpp"
#include "AutomationVertex.hpp"
#include "IRImageLineButton.h"
#include "ColourLib.h"

class IRSimpleController : public Component
{
public:
    IRSimpleController();
    ~IRSimpleController();
    
    void setup(bool isZoomIn,
               bool isZoomOut,
               bool isMovable,
               bool isComment,
               bool isBezier);
    
    void addAllComponent();
    
    void resized() override;
    void paint(Graphics& g) override;
    
    void setMovableStatus(IRAutomation::movableStatus status);
    
    void setZoomInEvent(std::function<void()> callBack);
    void setZoomOutEvent(std::function<void()> callBack);
    void setMovableEvent(std::function<void(IRAutomation::movableStatus)> callBack);
    void setCommentEvent(std::function<void()> callBack);
    void setBezierEvent(std::function<void(IRAutomation::lineStatus)> callBack);
    
private:
    IRIconBank& ImageBank = singleton<IRIconBank>::get_instance();
    
    IRImageButton zoomInButton;
    IRImageButton zoomOutButton;
    
    IRImageMovableButton movableButton;
    
    IRImageButton commentButton;
    
    IRImageLineButton bezierButton;
    
    // ==================================================
    bool isZoomIn = false;
    bool isZoomOut = false;
    bool isMovable = false;
    bool isComment = false;
    bool isBezier = false;
    
    // ==================================================

    
    void zoomInClicked();
    void zoomOutClicked();
    
    void commentClicked();
    void bezierClicked();
    
    
    bool isCommentOn = false;
    
    
    int buttonSize = 40;
    int buttonInterval = 5;
    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
};

#endif /* IRSimpleController_hpp */
