//
//  IRUIAudioFoundation.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 18/04/2019.
//

#ifndef IRUIAudioFoundation_hpp
#define IRUIAudioFoundation_hpp

#include "IRUIFoundation.hpp"

class IRUIAudioFoundation : public IRUIFoundation,
public AudioSource
{
public:
    IRUIAudioFoundation(IRNodeObject* nodeObject, IRStr* str);
    IRUIAudioFoundation(IRNodeObject* nodeObject, IRStr* str, AudioDeviceManager& dm);
    ~IRUIAudioFoundation();
    
    void init();
    
   
    // ==================================================
    // audio
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {}
    virtual void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override {}
    virtual void releaseResources() override {}
    
    /** A subclass should call this from their constructor, to set up the audio. */
    void setAudioChannels (int numInputChannels, int numOutputChannels, const XmlElement* const storedSettings = nullptr);

    void shutdownAudio();
    
    AudioDeviceManager& deviceManager;

    // --------------------------------------------------
private:
    //=============================================================================
    AudioDeviceManager defaultDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    bool usingCustomDeviceManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRUIAudioFoundation)

};

#endif /* IRUIAudioFoundation_hpp */
