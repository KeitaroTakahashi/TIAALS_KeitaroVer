//
//  ObjectMenuIconArea.h
//  IRiMaS
//
//  Created by Keitaro on 19/11/2019.
//

#ifndef ObjectMenuIconArea_h
#define ObjectMenuIconArea_h

#include "IRStrComponent.hpp"

class ObjectMenuIconArea : public Component,
public IRStrComponent
{
public:
    ObjectMenuIconArea(IRStr* str, int buttonSize, int leftMarge) : IRStrComponent(str),
    buttonSize(buttonSize),
    leftMarge(leftMarge),
    workspaceSlideButton(str, str->ICONBANK->icon_toNavigator, "Workspace Slide", buttonSize),
    textButton(str, str->ICONBANK->icon_text, "Texts", buttonSize),
    imageButton(str, str->ICONBANK->icon_image, "Graphics", buttonSize),
    audioButton(str, str->ICONBANK->icon_wav, "Audio", buttonSize),
    chartButton(str, str->ICONBANK->icon_chart, "Charts", buttonSize),
    playerButton(str, str->ICONBANK->icon_play, "Players", buttonSize),
    objectButton(str, str->ICONBANK->icon_object, "Objects", buttonSize)
    {
        addButtons();
    }
    
    ~ObjectMenuIconArea()
    {
        
    }
    // ==================================================
    
    void resized() override
    {
        //top
        int x = 10;
        int y = 10;
        int s = this->buttonSize;
        int yMarge = 10;
        
        int t_d = 5;
        
        this->workspaceSlideButton.setBounds(x, y, getWidth() - x, s);
        
        y += s + yMarge;

        this->textButton.setBounds(x, y, getWidth() - x, s);
        //this->textLabel.setBounds(x + s + t_d, y + 8, 80, 24);
        
        y += s + yMarge;
        this->imageButton.setBounds(x, y, getWidth() - x, s);
        //this->imageLabel.setBounds(x + s + t_d, y + 8, 80, 24);

        
        y += s + yMarge;
        this->audioButton.setBounds(x, y, getWidth() - x, s);
        //this->audioLabel.setBounds(x + s + t_d, y + 8, 80, 24);
        
        y += s + yMarge;
        this->chartButton.setBounds(x, y, getWidth() - x, s);
       // this->chartLabel.setBounds(x + s + t_d, y + 8, 80, 24);
        
        y += s + yMarge;
        this->playerButton.setBounds(x, y, getWidth() - x, s);
        //this->playerLabel.setBounds(x + s + t_d, y + 8, 80, 24);
        
        y += s + yMarge;
        this->objectButton.setBounds(x, y, getWidth() - x, s);
        //this->objectLabel.setBounds(x + s + t_d, y + 8, 80, 24);
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
           
        g.setColour(getStr()->SYSTEMCOLOUR.contents);
           //int y = this->topMarge + this->buttonSize * 2 + yMarge * 2;
           //g.drawLine(0, 0, getWidth(), 0, 2);
           
           //y = getHeight() - this->buttomSpace;
           //g.drawLine(0, y, getWidth(), y, 2);
        
        
        //g.drawLine(0, 0, getWidth(), 0, 2);
        paintSelectedItem(g);
    }

    void paintSelectedItem(Graphics& g)
    {
        if(this->selectedButtonType != NONE)
        {
            g.setColour(getStr()->SYSTEMCOLOUR.contents);
            //int index = (int)this->selectedButtonType;
            int x = this->leftMarge / 2;
            //int y = this->topMarge + index * (this->buttonSize + yMarge*2) - yMarge/2;
            int y = getButtonFromType().getBounds().getY() - 5;
            
            // width should be bigger to hide the right side rounded corner
            int w = getWidth() * 1.2;
            g.fillRoundedRectangle(x, y, w, this->buttonSize + 5, 5);
        }
    }
    // ==================================================
    // ==================================================
    // ==================================================
    // ==================================================

    std::function<void()> workspaceSlideActionCallback;
    std::function<void()> textActionCallback;
    std::function<void()> imageActionCallback;
    std::function<void()> audioActionCallback;
    std::function<void()> chartActionCallback;
    std::function<void()> playerActionCallback;
    std::function<void()> objectActionCallback;

private:
    // ==================================================
    
    void addButtons()
    {
        addAndMakeVisible(&this->workspaceSlideButton);
        this->workspaceSlideButton.onClick = [this] { workspaceSlideAction(); };
        addAndMakeVisible(&this->textButton);
        this->textButton.onClick = [this]{ textAction(); };
        addAndMakeVisible(&this->imageButton);
        this->imageButton.onClick = [this]{ imageAction(); };
        addAndMakeVisible(&this->audioButton);
        this->audioButton.onClick = [this]{ audioAction(); };
        addAndMakeVisible(&this->chartButton);
        this->chartButton.onClick = [this]{ chartAction(); };
        addAndMakeVisible(&this->playerButton);
        this->playerButton.onClick = [this]{ playerAction(); };
        addAndMakeVisible(&this->objectButton);
        this->objectButton.onClick = [this]{ objectAction(); };
    }

    
    void replaceCurrentMenu(ObjectMenuComponent* obj)
    {
        
    }
    
    // ==================================================
    
    void workspaceSlideAction()
    {
        if(this->workspaceSlideActionCallback != nullptr)
            this->workspaceSlideActionCallback();
    }
    
    void textAction()
    {
        if(this->textActionCallback != nullptr) this->textActionCallback();
    }
    void imageAction()
    {
        if(this->imageActionCallback != nullptr) this->imageActionCallback();
    }
    void audioAction()
    {
        if(this->audioActionCallback != nullptr) this->audioActionCallback();
    }
    void chartAction()
    {
        if(this->chartActionCallback != nullptr) this->chartActionCallback();
    }
    void playerAction()
    {
        if(this->playerActionCallback != nullptr) this->playerActionCallback();
    }
    void objectAction()
    {
        if(this->objectActionCallback != nullptr) this->objectActionCallback();
    }
    // ==================================================
    ObjectMenuComponent* currentMenu = nullptr;

    // ==================================================
    objectCategory selectedButtonType = NONE;

    // ==================================================
    // marge
    int buttonSize = 20;
    int leftMarge = 10;
    // ==================================================

    IRImageButton& getButtonFromType()
    {
        switch(this->selectedButtonType)
        {
            case WORKSPACESLIDE:
                return this->workspaceSlideButton.getButton();
                break;
            case TEXTMENU:
                return this->textButton.getButton();
                break;
            case IMAGEMENU:
                return this->imageButton.getButton();
                break;
            case AUDIOMENU:
                return this->audioButton.getButton();
                break;
            case CHARTMENU:
                return this->chartButton.getButton();
                break;
            case PLAYERMENU:
                return this->playerButton.getButton();
                break;
            case OBJECTMENU:
                return this->objectButton.getButton();
                break;
            default:
                return this->textButton.getButton();
                break;
        }
    }
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
            if(getStr()->SYSTEMCOLOUR.isWhiteBased) button.setImage(img.small_black);
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

    ObjectButton workspaceSlideButton;
    ObjectButton textButton;
    ObjectButton imageButton;
    ObjectButton audioButton;
    ObjectButton chartButton;
    ObjectButton playerButton;
    ObjectButton objectButton;

  
    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObjectMenuIconArea)

};



#endif /* ObjectMenuIconArea_h */
