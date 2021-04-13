//
//  FFTPreferenceUI.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 23/10/2018.
//

#ifndef FFTPreferenceUI_h
#define FFTPreferenceUI_h

class FFTPreferenceUI : public Component
{
public:
    FFTPreferenceUI(String title)
    {
        addAndMakeVisible(this->LabelTitle);
        this->LabelTitle.setText(title, dontSendNotification);
        this->LabelTitle.setColour(Label::textColourId, Colours::black);
        this->LabelTitle.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->LabelFileName);
        this->LabelFileName.setText("File name : ", dontSendNotification);
        this->LabelFileName.setColour(Label::textColourId, Colours::black);
        this->LabelFileName.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->FileName);
        this->FileName.setText("", dontSendNotification);
        this->FileName.setColour(Label::textColourId, Colours::black);
        this->FileName.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->LabelFFTSize);
        this->LabelFFTSize.setText("Window size : ", dontSendNotification);
        this->LabelFFTSize.setColour(Label::textColourId, Colours::black);
        this->LabelFFTSize.setJustificationType(Justification::left);
        
        makeFFTSizeMenu();
        
        addAndMakeVisible(this->LabelFFTCustom);
        this->LabelFFTCustom.setText("Custom : ", dontSendNotification);
        this->LabelFFTCustom.setColour(Label::textColourId, Colours::black);
        this->LabelFFTCustom.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->FFTSizeInput);
        this->FFTSizeInput.setText("0", dontSendNotification);
        this->FFTSizeInput.setEditable(true);
        this->FFTSizeInput.setColour(Label::textColourId, Colours::black);
        this->FFTSizeInput.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->LabelHopSize);
        this->LabelHopSize.setText("Hop size : ", dontSendNotification);
        this->LabelHopSize.setColour(Label::textColourId, Colours::black);
        this->LabelHopSize.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->HopSizeInput);
        this->HopSizeInput.setText("512", dontSendNotification);
        this->HopSizeInput.setEditable(true);
        this->HopSizeInput.setColour(Label::textColourId, Colours::black);
        this->HopSizeInput.setColour(Label::textWhenEditingColourId, Colours::black);
        
        addAndMakeVisible(this->LabelFrameIndex);
        this->LabelFrameIndex.setText("Frame Index : ", dontSendNotification);
        this->LabelFrameIndex.setColour(Label::textColourId, Colours::black);
        this->LabelFrameIndex.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->LabelMaxFrameIndex);
        this->LabelMaxFrameIndex.setText(" of   0", dontSendNotification);
        this->LabelMaxFrameIndex.setColour(Label::textColourId, Colours::black);
        this->LabelMaxFrameIndex.setJustificationType(Justification::left);
        
        
        addAndMakeVisible(this->FrameIndexInput);
        this->FrameIndexInput.setText("0", dontSendNotification);
        this->FrameIndexInput.setEditable(true);
        this->FrameIndexInput.setColour(Label::textColourId, Colours::black);
        this->FrameIndexInput.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->LabelFrameSec);
        this->LabelFrameSec.setText("Frame Sec. : ", dontSendNotification);
        this->LabelFrameSec.setColour(Label::textColourId, Colours::black);
        this->LabelFrameSec.setJustificationType(Justification::left);
        
        addAndMakeVisible(this->LabelFrameSecNum);
        this->LabelFrameSecNum.setText("0.0", dontSendNotification);
        this->LabelFrameSecNum.setColour(Label::textColourId, Colours::black);
        this->LabelFrameSecNum.setJustificationType(Justification::left);

        this->HopSizeInput.setJustificationType(Justification::left);
    }
    
    ~FFTPreferenceUI()
    {
        
    }
    
    //===============================================================
    
    void resized() override
    {
        // margin 10
        this->LabelTitle.setBounds          (20, 10, 300, 30);
        
        this->LabelFileName.setBounds       (10, 50, 100, 30);
        this->FileName.setBounds            (110, 50, 100, 30);

        this->LabelFFTSize.setBounds        (10, 90, 100, 30);
        this->FFTSizeMenu.setBounds         (110, 90, 120, 30);
        this->LabelFFTCustom.setBounds      (240, 90, 60, 30);
        this->FFTSizeInput.setBounds        (300, 90, 80, 30);
        
        this->LabelHopSize.setBounds        (10, 130, 100, 30);
        this->HopSizeInput.setBounds        (110, 130, 100, 30);
        
        this->LabelFrameIndex.setBounds     (10, 170, 100, 30);
        this->FrameIndexInput.setBounds     (110, 170, 80, 30);
        this->LabelMaxFrameIndex.setBounds  (200, 170, 100, 30);

        this->LabelFrameSec.setBounds       (10, 210, 100, 30);
        this->LabelFrameSecNum.setBounds    (110, 210, 100, 30);

    }
    // --------------------------------------------------------------
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::white);
        g.setColour(Colours::black);
        g.drawLine(0,42.5,getWidth(),42.5);
    }
    // --------------------------------------------------------------
    //===============================================================
    void makeFFTSizeMenu()
    {
        addAndMakeVisible(this->FFTSizeMenu);
        
        this->FFTSizeMenu.setColour(ComboBox::backgroundColourId, SYSTEMCOLOUR.fundamental);
        this->FFTSizeMenu.setColour(ComboBox::outlineColourId, SYSTEMCOLOUR.contents);
        this->FFTSizeMenu.setColour(ComboBox::focusedOutlineColourId, SYSTEMCOLOUR.contents);
        
        int index = 1;
        int minSize = 512;
        for(int i=0;i<8;i++){
            this->FFTSizeMenu.addItem(String(minSize), index);
            minSize *= 2;
            index ++;
        }
        this->FFTSizeMenu.addItem("custom", index);
        
        this->FFTSizeMenu.onChange = [this] { FFTSizeMenuChanged(); };
        int defaultIndex = 4;
        this->FFTSizeMenu.setSelectedId(defaultIndex);
    }
    // --------------------------------------------------------------
    // --------------------------------------------------------------
    // --------------------------------------------------------------
    //===============================================================
    void FFTSizeMenuChanged()
    {
        
    }
    // --------------------------------------------------------------
    // --------------------------------------------------------------
    // --------------------------------------------------------------


private:
    
    Label LabelTitle;
    
    Label LabelFileName;
    Label FileName;
    
    Label LabelFFTSize;
    ComboBox FFTSizeMenu;
    Label LabelFFTCustom;
    Label FFTSizeInput;
    
    Label LabelHopSize;
    Label HopSizeInput;
    
    Label LabelFrameIndex; // showing the position of the spectrum
    Label FrameIndexInput;
    Label LabelMaxFrameIndex;
    
    Label LabelFrameSec; // showing the position of the spectrum in sec.
    Label LabelFrameSecNum;
    
    ComboBox windowTypeMenu;
    
    
    
    // system colour
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTPreferenceUI)
};

#endif /* FFTPreferenceUI_h */
