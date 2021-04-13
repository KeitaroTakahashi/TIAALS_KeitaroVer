
//
//  IRUIAudioFoundation.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 18/04/2019.
//

#include "IRUIAudioFoundation.hpp"

IRUIAudioFoundation::IRUIAudioFoundation(IRNodeObject* nodeObject, IRStr* str,  AudioDeviceManager& dm) :
IRUIFoundation(nodeObject, str),
deviceManager (dm),
usingCustomDeviceManager (true)
{
}

IRUIAudioFoundation::IRUIAudioFoundation(IRNodeObject* nodeObject, IRStr* str) :
IRUIFoundation(nodeObject, str),
deviceManager (defaultDeviceManager),
usingCustomDeviceManager (false)
{
}
// --------------------------------------------------
IRUIAudioFoundation::~IRUIAudioFoundation()
{
    
}
// --------------------------------------------------

// ==================================================
// JUCE CODES
void IRUIAudioFoundation::setAudioChannels (int numInputChannels, int numOutputChannels, const XmlElement* const xml)
{
    String audioError;
    
    if (usingCustomDeviceManager && xml == nullptr)
    {
        auto setup = deviceManager.getAudioDeviceSetup();
        
        if (setup.inputChannels.countNumberOfSetBits() != numInputChannels
            || setup.outputChannels.countNumberOfSetBits() != numOutputChannels)
        {
            setup.inputChannels.clear();
            setup.outputChannels.clear();
            
            setup.inputChannels.setRange (0, numInputChannels, true);
            setup.outputChannels.setRange (0, numOutputChannels, true);
            
            audioError = deviceManager.setAudioDeviceSetup (setup, false);
        }
    }
    else
    {
        audioError = deviceManager.initialise (numInputChannels, numOutputChannels, xml, true);
    }
    
    jassert (audioError.isEmpty());
    
    deviceManager.addAudioCallback (&audioSourcePlayer);
    audioSourcePlayer.setSource (this);
}
// --------------------------------------------------

void IRUIAudioFoundation::shutdownAudio()
{
    audioSourcePlayer.setSource (nullptr);
    deviceManager.removeAudioCallback (&audioSourcePlayer);
    
    // other audio callbacks may still be using the device
    if (! usingCustomDeviceManager)
        deviceManager.closeAudioDevice();
}
// JUCE CODES
// ==================================================
