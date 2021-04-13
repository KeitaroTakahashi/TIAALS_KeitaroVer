//
//  waveformController.h
//  IRiMaS
//
//  Created by Keitaro on 29/06/2020.
//

#ifndef waveformController_h
#define waveformController_h

#include "JuceHeader.h"
#include "AudioObjectController.h"

class waveformController : public Component,
public IRStrComponent,
public ChangeBroadcaster
{
public:
    
    enum IRWaveformController2Status
    {
        OpenAudioFile,
        PlayWhole,
        Stop,
        Pause,
        NONE
        
    };
    
    waveformController(IRStr *str) :
    IRStrComponent(str),
    audioController(str)
    {
 
        addAndMakeVisible(&this->audioController);
    }
    
    ~waveformController()
    {
        
    }
    
    void resized() override
    {
        int y = 10;
        int yBigIncrement = 40;

        this->audioController.setBounds(0, y, getWidth(), 300);
    }
    
    IRWaveformController2Status getStatus() const { return this->status; }

    void addChangeListenerToAudioController(ChangeListener* listener)
    {
        this->audioController.addChangeListener(listener);
    }
    
    AudioObjectController* getAudioController(){ return &this->audioController; }
private:
    
    AudioObjectController audioController;


    IRWaveformController2Status status;
    
};

#endif /* waveformController_h */
