//
//  PreferenceGUI.h
//  IRiMaS
//
//  Created by Keitaro on 17/10/2019.
//

#ifndef PreferenceGUI_h
#define PreferenceGUI_h

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"
#include "IRColourButton.h"


class PreferenceGUI : public Component,
public IRStrComponent
{
public:
    PreferenceGUI(IRStr* str) : IRStrComponent(str)
    {
        this->colourLabel.setText("Colour", dontSendNotification);
        addAndMakeVisible(&this->colourLabel);
        
        createColourButtons();
        
    }
    
    ~PreferenceGUI()
    {
        deleteColourButtons();
    }
    
    // ============================================================
    void resized() override
    {
        int x = 10;
        int y = 0;
        int xIncrement = 50;
        int yIncrement = 40;
        int yBigIncrement = 50;
        
        this->colourLabel.setBounds(x, y, getWidth() - 20, 30);
        y += yIncrement;
        
        int yIndex = 1;
        int num4Line = 8;
        int w_x = xIncrement * (num4Line - 1);
        for(auto c : this->colourButtons)
        {
            x += xIncrement;
            
            int cal = floor(yIndex / num4Line);
            
            c->setBounds(x - (w_x * cal), y + (yBigIncrement * cal), 40, 40);
            
            yIndex ++;
        }
        
    }
    
    void paint(Graphics& g) override
    {
        
    }
    // ============================================================

    void createButton(IRImageButton* button, Image img)
    {
        button->setImage(img);
        
        //button->setDrawCircle(false);
        addAndMakeVisible(button);
    }
    
    // ============================================================
    void darkMagentaClicked()
    {
        
    }
    // ============================================================
    
    void createColourButtons()
    {
        deleteColourButtons();
        this->colourButtons.push_back(new IRColourButton(IR::darkMagentaSet()));
        this->colourButtons.push_back(new IRColourButton(IR::darkGreenSet()));
        this->colourButtons.push_back(new IRColourButton(IR::darkBlueSet()));
        this->colourButtons.push_back(new IRColourButton(IR::darkBrownSet()));
        this->colourButtons.push_back(new IRColourButton(IR::blackSet()));
        this->colourButtons.push_back(new IRColourButton(IR::darkGraySet()));
        this->colourButtons.push_back(new IRColourButton(IR::silverSet()));

        this->colourButtons.push_back(new IRColourButton(IR::bronzeSet()));
        this->colourButtons.push_back(new IRColourButton(IR::IRPink()));
        this->colourButtons.push_back(new IRColourButton(IR::greenSet()));

        this->colourButtons.push_back(new IRColourButton(IR::IRLightBlue()));
        this->colourButtons.push_back(new IRColourButton(IR::IRLightBrown()));
        this->colourButtons.push_back(new IRColourButton(IR::IRLightPink()));

        
        
        for(auto c : this->colourButtons)
        {
            addAndMakeVisible(c);
            c->onClick = [this](IRColourButton* button){ colourButtonClicked(button); };
        }

    }
    
    void deleteColourButtons()
    {
        for(auto c : this->colourButtons)
        {
            delete c;
        }
        this->colourButtons.clear();
    }
    
    void colourButtonClicked(IRColourButton* button)
    {
        //change colour pattern
        setUIColour(button->getColourPattern());
    }
    // ============================================================

private:
    
    
    
    // ============================================================
    
    Label colourLabel;
    // colour
    IRImageButton darkMagenta; // ok
    IRImageButton darkBlue; // ok
    IRImageButton darkGreen;

    
    IRImageButton lightPurple;
    IRImageButton pink;
    IRImageButton yellowBrown;
    IRImageButton brown;
    IRImageButton darkBrown;
    IRImageButton darkYellowBrown;



    IRImageButton lightGreen;

    IRImageButton gray;
    IRImageButton black;

    IRImageButton darkGray;
    IRImageButton darkYellow;
    IRImageButton blue;


    std::vector<IRColourButton*> colourButtons;
    
    // ============================================================

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreferenceGUI)

};

#endif /* PreferenceGUI_h */
