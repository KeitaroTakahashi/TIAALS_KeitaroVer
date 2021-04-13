//
//  ObjectSlideSwitchSpace.h
//  IRiMaS
//
//  Created by Keitaro on 20/11/2019.
//

#ifndef ObjectSlideSwitchSpace_h
#define ObjectSlideSwitchSpace_h
#include "IRWorkspaceComponent.hpp"

class ObjectSlideSwitchSpace : public Component,
public IRStrComponent
{
public:
    ObjectSlideSwitchSpace(IRStr* str, int buttonSize) :
    IRStrComponent(str),
    buttonSize(buttonSize),
    toNavigatorButton(str, str->ICONBANK->icon_toNavigator, "to Slides", buttonSize),
    toObjectMenuButton(str, str->ICONBANK->icon_toObjectMenu, "to Objects", buttonSize)
    {
        this->toNavigatorButton.onClick = [this] { toNavigatorButtonAction(); };
        this->toObjectMenuButton.onClick = [this] { toObjectMenuButtonAction(); };

    }
    
    ~ObjectSlideSwitchSpace()
    {
        
    }
    // ==================================================
    // ==================================================

    void resized() override
    {
        int s = this->buttonSize;
        int y = 10;
        int x = 10;
        this->toNavigatorButton.setBounds (x, y, getWidth(), s);
        this->toObjectMenuButton.setBounds (x, y, getWidth(), s);
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
        std::cout << "ObjectSlideSwitchSpace paint\n";

    }
    // ==================================================

    std::function<void()> toNavigatorButtonClicked;
    void toNavigatorButtonAction()
    {
        
        // first update screenshot of the current workspac
        auto w = getStr()->TopWorkspace;
        if(w != nullptr)
        {
            auto ws = static_cast<IRWorkspaceComponent*>(w);
            //exportScreenshot(ws->getIndex());
        }
        
        switchToObjectMenuButton();
        if(this->toNavigatorButtonClicked != nullptr)
            this->toNavigatorButtonClicked();
    }
    void switchToNavigatorButton()
    {
        removeChildComponent(&this->toObjectMenuButton);
        addAndMakeVisible(&this->toNavigatorButton);
    }
    std::function<void()> toObjectMenuButtonClicked;
    void toObjectMenuButtonAction()
    {
        switchToNavigatorButton();
        if(this->toObjectMenuButtonClicked != nullptr)
            this->toObjectMenuButtonClicked();
    }
    void switchToObjectMenuButton()
    {
        removeChildComponent(&this->toNavigatorButton);
        addAndMakeVisible(&this->toObjectMenuButton);
    }
    
    // ==================================================
    
    int buttonSize = 0;
    // ==================================================
    // object button
    
    class ObjectButton : public Component,
    public IRStrComponent
    {
    public:
        ObjectButton(IRStr* str,
                     IRIconBank::IRIconImage img,
                     String title,
                     int buttonSize) :
        IRStrComponent(str),
        title(title),
        buttonSize(buttonSize)
        {
            createButton(img);
        }
        
        ~ObjectButton() {}
        // --------------------------------------------------
        void resized() override
        {
            button.setBounds(0, 0, buttonSize, buttonSize);
        }
        
        void paint(Graphics& g) override
        {
            g.setColour(getStr()->SYSTEMCOLOUR.text);
            //g.drawText(title, buttonSize + 10, 8, 80, 24, Justification::left);
        }
        
        // --------------------------------------------------
        void createButton(IRIconBank::IRIconImage img)
        {
            if(getStr()->SYSTEMCOLOUR.isWhiteBased) button.setImage(img.black);
            else button.setImage(img.small_white);
            addAndMakeVisible(button);
            
            button.addMouseListener(this, false);
        }
        
        void mouseDown(const MouseEvent& e) override
        {
            if(onClick != nullptr) onClick();
            button.mouseDownVisual();
        }
        
        void mouseUp(const MouseEvent& e) override
        {
            button.mouseUpVisual();
        }
        
        std::function<void()> onClick;
        
        IRImageButton& getButton() { return button; }
        // --------------------------------------------------
        String title;
        IRImageButton button;
        int buttonSize = 0;
        
    };
    // ==================================================
    
    ObjectButton toNavigatorButton;
    ObjectButton toObjectMenuButton;
    
    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObjectSlideSwitchSpace)

    
};

#endif /* ObjectSlideSwitchSpace_h */
