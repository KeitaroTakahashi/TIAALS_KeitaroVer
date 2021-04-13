//
//  AutomationPreference_OpenAudioUI.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 24/05/2019.
//

#ifndef AutomationPreference_OpenAudioUI_h
#define AutomationPreference_OpenAudioUI_h

#include "IRStrComponent.hpp"

class AutomationPreferenceOpenAudioUI : public Component,
public IRStrComponent,
public ChangeBroadcaster
{
public:
    
    enum AutomationpreferenceOpenAudioUIStatus
    {
        OpenAudioButtonClicked,
        DescriptorMenuChanged

    };
    
    AutomationPreferenceOpenAudioUI(IRStr* str) :
    IRStrComponent(str)
    {
        
        this->openAudioButton.setButtonText("open audio file");
        this->openAudioButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.fundamental);
        addAndMakeVisible(&this->openAudioButton);
        
        this->loadedAudioFileURL.setText("empty", dontSendNotification);
        addAndMakeVisible(&this->loadedAudioFileURL);
        
        // --------------------------------------------------
        this->descriptorList.setColour(ComboBox::backgroundColourId, SYSTEMCOLOUR.fundamental);
        this->descriptorList.setColour(ComboBox::outlineColourId, SYSTEMCOLOUR.contents);
        this->descriptorList.setColour(ComboBox::focusedOutlineColourId, SYSTEMCOLOUR.contents);
        this->descriptorList.onChange = [this] { hasDescriptorMenuSelectedChanged(); };
        this->descriptorList.setText("Assign Descriptor", dontSendNotification);
        addAndMakeVisible(&this->descriptorList);
        // --------------------------------------------------
    }
    
    ~AutomationPreferenceOpenAudioUI()
    {
        
    }
    //===============================================================
    void resized() override
    {
        int marginY = 10;
        int marginX = 10;
        
        this->openAudioButton.setBounds     (20, marginY, 150, 30);
        this->loadedAudioFileURL.setBounds  (20, marginY + 30, getWidth() - (marginX * 2), 30);
        
        this->descriptorList.setBounds      (180, marginY, 150, 30);
        
    }
    
    void paint(Graphics& g) override
    {
        
    }
    
    //===============================================================
    
    void setOpenAudioButtonCallback(std::function<void()>callback)
    {
        this->openAudioButton.onClick = callback;
    }
    //===============================================================
    
    void setAudioFileURL(String url)
    {
        this->loadedAudioFileURL.setText(url, dontSendNotification);
    }
    
    void clearDescriptorMenu() { this->descriptorList.clear(); }
    
    void addDescriptorMenu(String descriptorName)
    {
        this->descriptorList.addItem(descriptorName, this->descriptorList.getNumItems()+1);
    }
    
    void setSelectedDescriptorItem(int index)
    {
        this->descriptorList.setSelectedItemIndex (index, dontSendNotification);
    }
    //===============================================================

    void hasDescriptorMenuSelectedChanged()
    {
        const int selectedId = this->descriptorList.getSelectedItemIndex();

        FFTDescriptor descriptor = static_cast<FFTDescriptor>(selectedId);
        
        this->selectedDescriptor = descriptor;
        
        this->status = DescriptorMenuChanged;
        sendChangeMessage();
    }
    
    FFTDescriptor getSelectedDescriptor() const { return this->selectedDescriptor; }
    
    AutomationpreferenceOpenAudioUIStatus getStatus() const { return this->status; }

private:
    //===============================================================

    TextButton openAudioButton;
    Label loadedAudioFileURL;
    
    ComboBox descriptorList;

    FFTDescriptor selectedDescriptor = FFTDescriptor::FFT_NONE;
    AutomationpreferenceOpenAudioUIStatus status;
    
    //===============================================================
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

};

#endif /* AutomationPreference_OpenAudioUI_h */
