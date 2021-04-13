//
//  IRWaveformController2.hpp
//  IRiMaS
//
//  Created by Keitaro on 10/10/2019.
//

#ifndef IRWaveformController2_hpp
#define IRWaveformController2_hpp
#include "IRObjectController.hpp"
#include "IRColourSelector.h"
#include "waveformController.h"

class IRWaveformController2 : public IRObjectController,
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
    
    
    IRWaveformController2(IRStr* str);
    ~IRWaveformController2();

    // ==================================================
    void ControllerResized() override;

    void paint(Graphics& g) override;
    
    // ==================================================
    
    // called by IRObjectController
    void mainControllerSelected() override;
    void arrangeControllerSelected() override;

    // ==================================================

    void setLoadedAudioFilePath(String path);
    // ==================================================

    IRWaveformController2Status getStatus() const { return this->status; }
    
    void addChangeListenerToAudioController(ChangeListener* listener);
    
    AudioObjectController* getAudioController() { return this->waveformCtl.getAudioController(); }
    
private:
    
    
    // ==================================================
    void controllerChangeListenerCallback(ChangeBroadcaster* source) override {};

    
    // ==================================================
    waveformController waveformCtl;
    void setWaveformControllerVisible(bool flag);
    
    IRWaveformController2Status status;
    
    Label LabelTitle;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRWaveformController2)

};
#endif /* IRWaveformController2_hpp */
