//
//  IRLeftBar.hpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#ifndef IRLeftBar_hpp
#define IRLeftBar_hpp


#include "JuceHeader.h"
#include "IRWindowHeader.h"
#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"
#include "LeftBarObjectMenu.hpp"
#include "LeftBarSlideMenu.hpp"
#include "ObjectSlideSwitchSpace.h"

class IRLeftBar : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
public KeyListener,
private KeAnimationComponent
{
public:
    IRLeftBar(IRStr* str);
    ~IRLeftBar();
    //==================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e)override;
    void mouseMove(const MouseEvent& e)override;

    //==================================================
    
    void checkResizableFromMouseDownPosition(juce::Point<int> pos);
    
    void setMovable(bool flag) { this->isMovable = flag; }
    //==================================================

    
    //==================================================

    void closeObjectMenu();
    //==================================================
    void addNewWorkspaceSlide(IRWorkspace* space);
    
    void workspaceSelectedAction(IRWorkspace* space);
    std::function<void(IRWorkspace*)> workspaceSelectedCallback;
    void workspaceDeleteAction(IRWorkspace* space);
    std::function<void(IRWorkspace*)> workspaceDeleteCallback;
    
    //==================================================

    bool reloadThumbnails();

    //==================================================

    IRWindowBarActionStatus getStatus() const { return this->status; }
    
    juce::Point<int> pos;
    juce::Point<int> currentPos;
    juce::Point<int> prevPos;
    
    //==================================================
    
    // @param1 : notify the action to objectSlideSwitchButton or not
    void toNavigatorAction(bool notify = false);
    void toObjectMenuAction(bool notify = false);
    
    //==================================================   
   // Key commands
    void deleteKeyPressed();
    void commandNKeyPressed();
    
    void upKeyPressed();
    void downKeyPressed();
private:
 
    //==================================================
    void addButtons();

    void createButton(IRImageButton* button, IRIconBank::IRIconImage img);
    //==================================================
    void changeListenerCallback (ChangeBroadcaster* source) override;

    //==================================================

    IRWindowBarActionStatus status;
    bool isResizable = true;
    
    // true enables to make the window movable when dragging this area
    bool isMovable = false;
    
    //==================================================

    std::shared_ptr<LeftBarObjectMenu> objectMenuComponent;
    std::shared_ptr<LeftBarSlideMenu> slideMenuComponent;

    objectCategory currentMenuType = objectCategory::NONE;
    objectCategory previousMenuType = objectCategory::NONE;
    // ==================================================
    void updateAnimationFrame() override {};
    // ==================================================
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override;

    //==================================================
    
    //std::shared_ptr<ObjectSlideSwitchSpace> objectSlideSwitchButton;
    
    TextButton addNewSlideButton;
    TextButton deleteSlideButton;
    //==================================================
    
    //==================================================

    // layout
    int buttonSize = 34;
    
    int topMarge = 0;
    int switchSpace = 50;
    int menuSpace = 150; // 150
    int buttomSpace = 130; // 130
    int yMarge = 6; // better to be even
    int leftMarge = 10;
    int rightMarge = 10; // 85
    int slideMenuButtomMargin = 50;
    
    int maxWidth = 0;
    int preferenceMaxWidth = 450;
    int ordinaryWidth = 0;
    
    // ==================================================

    void attachObjectMenu();
    void removeObjectMenu();
    void attachPreferenceMenu();
    void removePreferenceMenu();

    //==================================================
    
    //IRIconBank& ImageBank = singleton<IRIconBank>::get_instance();
    //IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    //==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRLeftBar)
    
};
#endif /* IRLeftBar_hpp */
