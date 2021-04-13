//
//  IRProjectOwnerBase.h
//  IRiMaS
//
//  Created by Keitaro on 24/10/2019.
//

#ifndef IRProjectOwnerBase_h
#define IRProjectOwnerBase_h

class IRProjectOwnerBase : public Component,
public AudioSource
{
    
public:
    IRProjectOwnerBase()
    {
        
    }
    
    ~IRProjectOwnerBase() {}
    // ==================================================

    
    
    virtual void updateAppearance() {}
    
    // ==================================================
    
    virtual void prepareToPlay (int samplesPerBlockExpected,
                                double sampleRate) override {};
    virtual void releaseResources() override {};

    virtual void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override {};

    // ==================================================

    // define the minimum size of the window
    int minWidth = 800;
    int minHeight = 700;
    
    int barHeight = 70;
    int leftBarWidth = 55;
    int mainComponentHeight = 400;
};

#endif /* IRProjectOwnerBase_h */
