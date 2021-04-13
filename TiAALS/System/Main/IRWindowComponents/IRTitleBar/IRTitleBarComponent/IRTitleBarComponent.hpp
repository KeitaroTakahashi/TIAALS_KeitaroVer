//
//  IRTitleBarComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 01/10/2019.
//

#ifndef IRTitleBarComponent_hpp
#define IRTitleBarComponent_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"
#include "EditModeButton.h"
#include "IRTitleBarProjectButtonArea.h"
#include "IRTitleBarGridArea.h"

class IRTitleBarComponent : public Component,
public IRStrComponent,
public ChangeBroadcaster
{
public:
    
    enum SelectedButtonType
    {
        rightBar,
        leftBar,
        NONE
    };
    
    IRTitleBarComponent(IRStr* str, String title);
    ~IRTitleBarComponent();
    
    //==================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //==================================================

    void setTitle(String newTitle);
    
    //==================================================
    SelectedButtonType getSelectedButtonType() const { return this->selectedButtonType; }
    //==================================================
    // callback
    
    std::function<void(bool)> rightBarButtonCallback;
    std::function<void()> closeButtonCallback;
    std::function<void()> editModeButtonCallback;
    
    std::function<void()> newSlideButtonCallback;
    std::function<void()> newProjectButtonCallback;
    std::function<void()> saveButtonCallback;
    std::function<void()> saveasButtonCallback;
    std::function<void()> openButtonCallback;


    std::function<void()> repaintedCallback;



    bool getLeftBarButtonSelected() const { return this->leftBarButton.isSelected(); }
    
    void setEditMode(bool flag);
    //==================================================

    //==================================================

    IRTitleBarProjectButtonArea* getProjectButtonComponent() { return this->projectButtonComponent.get(); }
    IRTitleBarGridArea* getGridAreaComponent() { return this->gridAreaComponent.get(); }
    
private:
    //==================================================

    void createButton(IRImageButton* button, IRIconBank::IRIconImage img);
    void createGridAreaComponent();
    //==================================================
    void paintSelectedItem(Graphics& g);
    //==================================================
    String title;
    Label titleLabel;
    //==================================================
    // used for preventing special effect by the openGL rendere delay
    int fixedHeight = 0;
        
    //==================================================

    std::shared_ptr<IRTitleBarProjectButtonArea> projectButtonComponent;
    std::shared_ptr<IRTitleBarGridArea> gridAreaComponent;
    
    SelectedButtonType selectedButtonType = NONE;
    
     juce::Point<int> buttonSize;
    int marginX = 20;

    IRImageButton leftBarButton;
    Label leftBarLabel;
    IRImageButton rightBarButton;
    Label rightBarLabel;
    void rightBarButtonAction();
    
    EditModeButton editModeButton;
    Label editModeLabel;
    void editModeButtonAction();
    
    //==================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRTitleBarComponent)

};
#endif /* IRTitleBarComponent_hpp */
