//
//  IRTitleBar.hpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#ifndef IRTitleBar_hpp
#define IRTitleBar_hpp

#include "IRTitleBarComponent.hpp"
#include "IRWindowHeader.h"

class IRTitleBar : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener
{
public:
    //==================================================
    IRTitleBar(IRStr* str, String title);
    ~IRTitleBar();
    
    //==================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e)override;
    void mouseMove(const MouseEvent& e)override;
    void mouseDoubleClick(const MouseEvent& e) override;
    //==================================================

    std::function<void()> titleDoubleClickedCallback;
    
    //==================================================
    void checkResizableFromMouseDownPosition(juce::Point<int> pos);

  
    //==================================================
    
    IRWindowBarActionStatus getStatus() const { return this->status; }
    
    juce::Point<int> pos;
    juce::Point<int> currentPos;
    juce::Point<int> prevPos;
    
    //==================================================
    // acceccible from outside of this class
    IRTitleBarComponent comp;
    IRTitleBarProjectButtonArea* getProjectButtonComponent() { return comp.getProjectButtonComponent(); }
    IRTitleBarGridArea* getGridAreaComponent() { return comp.getGridAreaComponent(); }

    //==================================================

private:
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    //==================================================
    
    //==================================================

    IRWindowBarActionStatus status;
    bool isResizable = true;
public:
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRTitleBar)
};
#endif /* IRTitleBar_hpp */
