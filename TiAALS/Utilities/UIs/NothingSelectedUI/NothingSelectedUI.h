//
//  NothingSelectedUI.h
//  IRiMaS
//
//  Created by Keitaro on 03/03/2020.
//

#ifndef NothingSelectedUI_h
#define NothingSelectedUI_h

#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"

class NothingSelectedUI : public Component,
public IRStrComponent
{
public:
    NothingSelectedUI(IRStr* str) : IRStrComponent(str)
    {
        addAndMakeVisible(this->title);
        this->title.setText("Select an object to format", dontSendNotification);
        this->title.setColour(Label::textColourId, getStr()->SYSTEMCOLOUR.text);
        this->title.setJustificationType(Justification::centred);
        
        createButton(&this->objectIcon, getStr()->ICONBANK->icon_object_type1);
        addAndMakeVisible(&this->objectIcon);

    }
    
    ~NothingSelectedUI()
    {
        
    }
    
    void resized() override
    {
        int yMargin = 60;
        int w = 200;
        int h = 60;
        
        this->title.setSize(w, h);
        this->title.setCentrePosition(getWidth()/2, getHeight()/2 + yMargin);
        
        
        this->objectIcon.setSize(100, 100);
        this->objectIcon.setCentrePosition(getWidth()/2, getHeight()/2 - 100 + yMargin);
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    }
    
private:
    
    Label title;
    IRImageButton objectIcon;
    
    void createButton(IRImageButton* button, IRIconBank::IRIconImage img)
    {
        if(getStr()->SYSTEMCOLOUR.isWhiteBased)
            button->setImage(img.black);
        else  button->setImage(img.white);
        addAndMakeVisible(button);
    }
};
#endif /* NothingSelectedUI_h */
