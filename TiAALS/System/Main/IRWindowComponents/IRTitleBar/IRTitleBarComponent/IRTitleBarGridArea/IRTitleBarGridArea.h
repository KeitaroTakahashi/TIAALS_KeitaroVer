//
//  IRTitleBarGridArea.h
//  IRIMAS2020July
//
//  Created by Keitaro on 22/07/2020.
//

#ifndef IRTitleBarGridArea_h
#define IRTitleBarGridArea_h

#include "JuceHeader.h"
#include "IRStrComponent.hpp"

class IRTitleBarGridArea : public Component,
public IRStrComponent,
public ChangeBroadcaster,
private Label::Listener
{
public:
    
    enum IRTitleBarGridAreaStatus
    {
        Grid_Changed,
        Guide_Changed
    };
    
    IRTitleBarGridArea(IRStr* str) :
    IRStrComponent(str)
    {
        setOpaque(false);

        createUI();
        
    }
    
    ~IRTitleBarGridArea()
    {
        
    }

    // ==================================================

    void resized() override
    {
        int h = 20;
        int w = 40;
        int x = 0;
        int y = 5;
        int xMargin = 10;
        
        this->GridPtInput.setBounds(x, y + h, w, h);
        this->pxLabel.    setBounds(x + w, y + h, 25, h);

        this->GridLabel.setBounds(x, getHeight() - y - h, w, h);
        
        
        x += w + 20 + xMargin;
        
        this->GuidePtInput.setBounds(x, y + h, w, h);
        this->pxLabel2.    setBounds(x + w, y + h, 25, h);

        this->GuideLabel.setBounds(x, getHeight() - y - h, w, h);
        
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::transparentBlack);
    }

    // ==================================================
    
    std::function<void(int)> GridLabelChangedCallback;
    std::function<void(int)> GuideLabelChangedCallback;

    
    // ==================================================

    // ==================================================
    
private:
    
    void createUI()
    {
        createLabel(this->GridLabel, "Grid");
        createLabel(this->GridPtInput, "10");
        this->GridPtInput.setColour(Label::outlineColourId, getStr()->SYSTEMCOLOUR.text);
        this->GridPtInput.setEditable(true);
        
        createLabel(this->pxLabel, "px");
        
        createLabel(this->GuideLabel, "Guide");
        createLabel(this->GuidePtInput, "5");
        this->GuidePtInput.setColour(Label::outlineColourId, getStr()->SYSTEMCOLOUR.text);
        this->GuidePtInput.setEditable(true);
        
        createLabel(this->pxLabel2, "px");

    }
    
    void createLabel(Label &label, String text)
    {
        label.setText(text, dontSendNotification);
        addAndMakeVisible(&label);
        label.setJustificationType(Justification::centred);
        label.setFont(getStr()->SYSTEMCOLOUR.h5);
        
        label.addListener(this);
    }
    
    // ==================================================

    void labelTextChanged (Label* labelThatHasChanged) override
    {
        std::string val = labelThatHasChanged->getText().toStdString();
        // check if the input value is digit integer number and otherw
        
        // default -1 means free
        int resultValue = -1;
        try
        {
            int v = std::stoi(val);
            if(v <= 0)
            {
                labelThatHasChanged->setText("free", dontSendNotification);
            }else{
                labelThatHasChanged->setText(String(val), dontSendNotification);
                resultValue = v;
            }
        }
        catch (const std::invalid_argument &e)
        {
            labelThatHasChanged->setText("free", dontSendNotification);
        }
        
        
        if(labelThatHasChanged == &this->GridPtInput)
        {
            this->status = Grid_Changed;
            sendChangeMessage();
            
            if(this->GridLabelChangedCallback != nullptr)
                this->GridLabelChangedCallback(resultValue);
        }else if(labelThatHasChanged == &this->GuidePtInput)
        {
            this->status = Guide_Changed;
            sendChangeMessage();
            if(this->GuideLabelChangedCallback != nullptr)
                this->GuideLabelChangedCallback(resultValue);
            
        }
    }
    // ==================================================

    IRTitleBarGridAreaStatus getStatus() const { return this->status; }
    
    // ==================================================

    // Grid interval
    Label GridLabel;
    Label GridPtInput;
    Label pxLabel;
    
    // Guide interval
    Label GuideLabel;
    Label GuidePtInput;
    Label pxLabel2;

    
    IRTitleBarGridAreaStatus status;
    // ==================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRTitleBarGridArea)

};

#endif /* IRTitleBarGridArea_h */
