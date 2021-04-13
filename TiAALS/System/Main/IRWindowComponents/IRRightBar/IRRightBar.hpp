//
//  IRRightBar.hpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#ifndef IRRightBar_hpp
#define IRRightBar_hpp

#include "JuceHeader.h"
#include "IRWindowHeader.h"
#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"
#include "IRMainSpace.hpp"
#include "NothingSelectedUI.h"


class IRRightBar : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
private KeAnimationComponent,
public IRMainSpace::Listener
{
public:
    IRRightBar(IRStr* str);
    ~IRRightBar();
    //==================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==================================================
    
    void openSpaceAction(bool flag);
    
    void setInitialPos(juce::Point<int> pos) { this->initialPos = pos; }
    
    //==================================================
    void addComponentAndMakeVisible(Component& comp);
    //==================================================

    void showNothingSelectedUI();
    
    void showWorkspaceController(Component* comp);
    
private:
     //==================================================

    std::shared_ptr<NothingSelectedUI> nothingSelectedUI;
    //==================================================

    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    void updateAnimationFrame() override;
    
    // ==================================================
    //IRWorkspace
    // getting to know when the selection status of a NodeObject has been changed.
    // This function is called when an object is either selected or unselected.
    // this function is, for instance, used to update the Object Controller in the IRRightBar
    // IRWorkspace and this class is connected in IRWindowComponent
    void nodeObjectSelectionChange(IRNodeObject* obj) override;
    void nodeObjectGetFocused(IRNodeObject* obj) override;

    //==================================================
    // layout
    int buttonSize = 40;
    int space = 270;
    
    juce::Point<int> initialPos;
     
    //==================================================
    bool openSpace = false;
    bool isOpened = false;
    int openSpeed = 24;
    //==================================================
    // actual component
    Component* comp = nullptr;
    
    void removeComponents();
    //==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRRightBar)

};

#endif /* IRRightBar_hpp */
