//
//  audioMixer.h
//  MixerAudioSource_Study
//
//  Created by Keitaro on 12/08/2018.
//


#ifndef audioMixer_h
#define audioMixer_h

#include <stdio.h>
#include <iostream>

#include "JuceHeader.h"
// #include "juce_audio_utils/juce_audio_utils.h"

// ===========================================================================
// ATTENTION!
// This Class should be used as a singleton!
// Do not make two or more audio engine in a program.
// ===========================================================================
class AudioEngine
{
public:
    AudioEngine() {}
    ~AudioEngine() {}
    
    AudioSource &getAudioSource()
    {
        return this->mixer;
    }
    
    void addAudioSource(AudioSource *source)
    {
        this->mixer.addInputSource(source, false);
    }
    
    void removeSource(AudioSource *source)
    {
        this->mixer.removeInputSource(source);
    }
    
private:
    MixerAudioSource mixer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};


#endif /* audioMixer_h */
