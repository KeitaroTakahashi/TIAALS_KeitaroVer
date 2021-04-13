//
//  ObjectMenuSpaceArea.h
//  IRiMaS
//
//  Created by Keitaro on 20/11/2019.
//

#ifndef ObjectMenuSpaceArea_h
#define ObjectMenuSpaceArea_h
#include "IRStrComponent.hpp"
#include "ObjectMenuComponent.hpp"

class ObjectMenuSpaceArea : public Component,
public IRStrComponent
{
public:
    ObjectMenuSpaceArea(IRStr * str) : IRStrComponent(str)
    {
        this->deleteSelectedSlideButton.setButtonText("Delete slide");
        this->deleteSelectedSlideButton.onClick = [this]{ deleteSelectedSlideButtonClicked(); };
        addAndMakeVisible(this->deleteSelectedSlideButton);
    }
    
    ~ObjectMenuSpaceArea()
    {
        removeMenuComponent();
    }
    // ==================================================

    void resized() override
    {
        if(this->menuObj != nullptr)
            this->menuObj->setBounds(0, 0, getWidth(), getHeight() - 40);
                
        this->deleteSelectedSlideButton.setBounds(5, getHeight() - 35, getWidth()-10, 30);
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    }
    // ==================================================

    void setMenuComponent(ObjectMenuComponent* obj)
    {
        if(this->menuObj != nullptr)
            removeChildComponent(this->menuObj);
        
        this->menuObj = obj;
        addAndMakeVisible(this->menuObj);
        resized();

    }
    
    void deleteSelectedSlideButtonClicked()
    {
        this->menuObj->menuCtlButtonAction();
    }
    
    void removeMenuComponent()
    {
        if(this->menuObj != nullptr)
            removeChildComponent(this->menuObj);
        
        this->menuObj = nullptr;
        resized();

    }
    // ==================================================

    void setHidden(bool flag) { this->isHiddenFlag = flag; }
    bool isHidden() const { return this->isHiddenFlag; }
    
    
    // ==================================================

private:
    ObjectMenuComponent* menuObj = nullptr;
    
    int buttonSpaceHeight = 100;
    TextButton deleteSelectedSlideButton;
    
    // ==================================================

    bool isHiddenFlag = true;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ObjectMenuSpaceArea)

};
#endif /* ObjectMenuSpaceArea_h */
