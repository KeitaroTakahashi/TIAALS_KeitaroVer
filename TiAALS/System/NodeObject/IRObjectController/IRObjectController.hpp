//
//  IRObjectController.hpp
//  IRiMaS
//
//  Created by Keitaro on 02/10/2019.
//

#ifndef IRObjectController_hpp
#define IRObjectController_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRSwitchButton.h"
#include "ObjectArranger.hpp"

class IRObjectController : public Component,
public IRStrComponent,
public ChangeListener,
private IRSquareButton::Listener
{
public:
    IRObjectController(String title, IRStr* str);
    ~IRObjectController();
    
    // Do not use resized() function but use ControllerResized() instead.
private:
    void resized() override;
public:
    virtual void ControllerResized() = 0;
    
    // show your controller in it
    virtual void mainControllerSelected() {}
    virtual void arrangeControllerSelected() {};
    
    
    // ==================================================
    // Arrange Controller
    // basic controller manages XY position, size, z-order, and enclose functions for versatile IRNodeObject
    
    void createAndAddArrangeController();
    
    void setArrangeController(ArrangeController* controller);
    ArrangeController* getArrangeController() { return this->arrangeController.get(); }
    void setArrangeControllerVisible(bool shouldBeVisible);
    bool hasArrangeController() const { return this->hasArrangeControllerFlag; }
    
    // ==================================================
private:
    void changeListenerCallback (ChangeBroadcaster* source) override;
public:
    virtual void controllerChangeListenerCallback(ChangeBroadcaster* source) {};
    
private:
    Label LabelTitle;
    IRSwitchButton switchButton;
    void buttonClicked(IRSquareButton* clickedButton) override;
    // ==================================================

    
    std::shared_ptr<ArrangeController> arrangeController;
    bool hasArrangeControllerFlag = false;

   // ==================================================

    // ==================================================

};

#endif /* IRObjectController_hpp */
