//
//  IRAudioDeviceManager.hpp
//  IRiMaS
//
//  Created by Keitaro on 20/07/2020.
//

#ifndef IRAudioDeviceManager_hpp
#define IRAudioDeviceManager_hpp

#include "JuceHeader.h"

class IRAudioDeviceManager : public AudioAppComponent,
public ChangeListener,
private juce::Timer
{
public:
    IRAudioDeviceManager();
    ~IRAudioDeviceManager();
    // ==============================

private:
    // ==============================

    void paint (juce::Graphics& g) override;
    void resized() override;

    // ==============================
    void prepareToPlay (int, double) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    // ==============================

    void changeListenerCallback (juce::ChangeBroadcaster*) override;

    // ==============================
    
    static juce::String getListOfActiveBits (const juce::BigInteger& b);
    void timerCallback() override;
    void dumpDeviceInfo();
    void logMessage (const juce::String& m);

    // ==============================

    juce::Random random;

    AudioDeviceSelectorComponent audioSetupComp;
    Label cpuUsageLabel;
    Label cpuUsageText;
    TextEditor diagnosticsBox;
    
    // ==============================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRAudioDeviceManager)

    
};
#endif /* IRAudioDeviceManager_hpp */
