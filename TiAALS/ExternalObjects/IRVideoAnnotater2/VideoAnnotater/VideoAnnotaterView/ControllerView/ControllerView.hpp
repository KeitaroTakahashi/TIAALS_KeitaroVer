//
//  ControllerView.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#ifndef ControllerView_hpp
#define ControllerView_hpp

#include "VideoAnnotaterWindowController.hpp"

class ControllerView : public Component,
public IRStrComponent,
public ChangeListener
{
public:
    ControllerView(IRStr* str);
    ~ControllerView();
    // ==================================================
    
    void setController(IRObjectController* ctl);
    void removeController();

    // ==================================================

private:
    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================
    
    void changeListenerCallback(ChangeBroadcaster* source) override; // JUCE oriented

    // ==================================================
    
    //std::shared_ptr<VideoAnnotaterWindowController> controller;

    IRObjectController* controller = nullptr;
    
    void addController(IRObjectController* controller);
};

#endif /* ControllerView_hpp */
