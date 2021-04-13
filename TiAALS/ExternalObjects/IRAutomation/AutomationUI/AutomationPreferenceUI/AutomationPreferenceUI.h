//
//  AutomationPreferenceUI.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 23/10/2018.
//

#ifndef AutomationPreferenceUI_h
#define AutomationPreferenceUI_h
#include "IRStrComponent.hpp"

#include "AutomationPreference_OpenAudioUI.h"

class AutomationPreferenceUI : public Component,
public IRStrComponent
{
public:
    AutomationPreferenceUI(String title, IRStr* str) :
    IRStrComponent(str)
    {
        addAndMakeVisible(this->LabelTitle);
        this->LabelTitle.setText(title, dontSendNotification);
        this->LabelTitle.setColour(Label::textColourId, Colours::black);
        this->LabelTitle.setJustificationType(Justification::left);

        
        this->audioFileLabel.setText("Audio File", dontSendNotification);
        this->audioFileLabel.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);

        addAndMakeVisible(&this->audioFileLabel);
        
        // --------------------------------------------------
        this->audioFileList.setColour(ComboBox::backgroundColourId, SYSTEMCOLOUR.fundamental);
        this->audioFileList.setColour(ComboBox::outlineColourId, SYSTEMCOLOUR.contents);
        this->audioFileList.setColour(ComboBox::focusedOutlineColourId, SYSTEMCOLOUR.contents);
        this->audioFileList.setText("Assign audio file", dontSendNotification);
        this->audioFileList.addItem("test", this->audioFileList.getNumItems()+1);
        this->audioFileList.addItem("test2", this->audioFileList.getNumItems()+1);
        this->audioFileList.addItem("test3", this->audioFileList.getNumItems()+1);
        addAndMakeVisible(&this->audioFileList);
        // --------------------------------------------------

        
        this->descriptorLabel.setText("Descriptor", dontSendNotification);
        this->descriptorLabel.setColour(Label::textColourId, SYSTEMCOLOUR.titleText);
        addAndMakeVisible(&this->descriptorLabel);
        
        // --------------------------------------------------
        this->descriptorList.setColour(ComboBox::backgroundColourId, SYSTEMCOLOUR.fundamental);
        this->descriptorList.setColour(ComboBox::outlineColourId, SYSTEMCOLOUR.contents);
        this->descriptorList.setColour(ComboBox::focusedOutlineColourId, SYSTEMCOLOUR.contents);
        this->descriptorList.setText("Assign Descriptor", dontSendNotification);
        this->descriptorList.addItem("test", this->descriptorList.getNumItems()+1);
        this->descriptorList.addItem("test2", this->descriptorList.getNumItems()+1);
        this->descriptorList.addItem("test3", this->descriptorList.getNumItems()+1);
        addAndMakeVisible(&this->descriptorList);
        // --------------------------------------------------
        
        this->openAudioUI = std::make_shared<AutomationPreferenceOpenAudioUI>(getStr());
        addAndMakeVisible(this->openAudioUI.get());

    }
    
    ~AutomationPreferenceUI()
    {
        
    }
    
    //===============================================================
    
    void resized() override
    {
        int marginX = 10;
        
        // margin 10
        this->LabelTitle.setBounds          (20, 10, 300, 30);
        
        this->audioFileLabel.setBounds      (20, 50, 150, 30);
        this->audioFileList.setBounds       (20, 80, 150, 30);
        
        this->descriptorLabel.setBounds     (170 + marginX, 50, 150, 30);
        this->descriptorList.setBounds      (170 + marginX, 80, 150, 30);

        this->openAudioUI->setBounds         (0, 200, getWidth(), 200);
    }
    
    // --------------------------------------------------------------
    void paint(Graphics& g) override
    {
        g.fillAll(SYSTEMCOLOUR.contents.brighter());
        g.setColour(Colours::black);
        g.drawLine(0,42.5,getWidth(),42.5);
        
        g.drawLine(0,130, getWidth(), 130);
    }
    // --------------------------------------------------------------
    AutomationPreferenceOpenAudioUI* getOpenAudioUI() const { return this->openAudioUI.get(); }
private:
    
    Label LabelTitle;
    
    
    Label audioFileLabel;
    ComboBox audioFileList;
    
    Label descriptorLabel;
    ComboBox descriptorList;
    
    std::shared_ptr<AutomationPreferenceOpenAudioUI> openAudioUI;
    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

};



#endif /* AutomationPreferenceUI_h */
