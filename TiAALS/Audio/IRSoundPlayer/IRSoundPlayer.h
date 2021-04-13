//
//  IRSoundPlayer.h
//  IRiMaS
//
//  Created by Keitaro on 10/02/2020.
//

#ifndef IRSoundPlayer_h
#define IRSoundPlayer_h

//#include "IRAudio.hpp"

class SoundPlayerClass : public PositionableAudioSource,
                         public ChangeBroadcaster
{
    //============================================================
    
public:
    SoundPlayerClass() {}

    ~SoundPlayerClass() {}
    
    //------------------------------------------------------------
    virtual void prepareToPlay(int samplesPerBlockExpected, double newSampleRate) override
    {
        const ScopedLock sl (this->callbackLock); // lock thread
        this->inputStreamEOF = false;
        this->isPrepared = true;
    }
    
    virtual void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override
    {
        const ScopedLock sl (this->callbackLock); // lock thread
        
        if(this->buffer != nullptr && ! this->stopped)
        {
            bufferToFill.clearActiveBufferRegion();
            
            // get playSamples. Attention, this should not be the totalSamples of the audio data.
            const int bufferSize = this->playSamples;
            const int samplesNeeded = bufferToFill.numSamples;
            const int samplesToCpy = jmin (bufferSize - this->playPosition, samplesNeeded);
            
            // how many samples to be copied from the audio data over the time scheduling.
            int offsetLeft = 0;
            
            // check if there is any samples to play...
            if(samplesToCpy > 0)
            {
                int maxInChannels = this->buffer->getNumChannels();
                int maxOutChannels = bufferToFill.buffer->getNumChannels();
                //# Here, we fill each indicated channel of a bufferToFill.buffer.
                int channelCount = (int)this->outputChannels.size();
                // playing...
                // -------------------------------------------------
                    // here only copying channels that are given.
                    for(int i=0; i< channelCount; ++i)
                    {
                        int chan = this->outputChannels[i];
                        if(chan < maxOutChannels)
                        {
                            // calculate remaining offset
                            int left = this->offset - this->currentOffsetPosition;

                            if(left >= samplesNeeded)
                                bufferToFill.buffer->clear(bufferToFill.startSample, bufferToFill.numSamples);
                            else
                            {
                                if(left > 0) // 0 < offsetLeft < samplesToCpy
                                {
                                    bufferToFill.buffer->clear(bufferToFill.startSample, left);
                                    bufferToFill.buffer->copyFrom(chan,
                                                                  bufferToFill.startSample + left,
                                                                  *this->buffer,
                                                                  chan % maxInChannels,
                                                                  this->startPosition + this->playPosition, // copy from playPosition
                                                                  (samplesToCpy - left)); // copied samples
                                    
                                    offsetLeft = samplesToCpy - left;
                                }else{
                                    bufferToFill.buffer->copyFrom(chan,
                                                                  bufferToFill.startSample,
                                                                  *this->buffer,
                                                                  chan % maxInChannels,
                                                                  this->startPosition + this->playPosition, // copy from playPosition
                                                                  samplesToCpy); // copied samples
                                    
                                    offsetLeft = samplesToCpy;

                                    // make ramp if this process is just after pausing in order to avoid producing a clip noise.
                                    if(this->afterPausing)
                                    {
                                        bufferToFill.buffer->applyGainRamp(chan, bufferToFill.startSample, jmin(256, bufferToFill.numSamples), 0.0f, 1.0f);
                                        this->afterPausing = false;
                                    }
                                }
                            }
                        }
                    }
                
                    // playPosition increases only after the time scheduling over
                    this->playPosition += offsetLeft;
                    
                    // currentOffsetPosition increases from the beginning.
                    this->currentOffsetPosition += samplesNeeded;
                    
                    // if loop mode
                    if(this->looping) this->playPosition %= bufferSize;
                
                // if the next NextReadPosition is beyond a total length of the audio data
                // and looping mode is false, do the following process.
                // This process operated when the input stream of data runs out.
                    if(this->playPosition >= this->playSamples && ! this->looping)
                    {
                        this->playing = false;
                        this->inputStreamEOF = true;
                        //inform the status change
                        sendChangeMessage();
                    }
                
               
                // -------------------------------------------------

                if(! this->playing) // stopping...
                {
                    // make a short ramp to 0 if it does not reach to the end of the audio data in order to avoid producing a clip noise.
                    for(int i=0; i< channelCount; i++)
                    {
                        // again process only the given channels.
                        int chan = this->outputChannels[i];
                        if(chan < maxOutChannels)
                        {
                            // make ramp : very short fade out
                            bufferToFill.buffer->applyGainRamp(chan, bufferToFill.startSample, jmin(256, bufferToFill.numSamples), 1.0f, 0.0f);
                            
                            //if numSamples is larger than the ramp size, then do 0 padding over the ramp size.
                            if(bufferToFill.numSamples > 256)
                                bufferToFill.buffer->clear(bufferToFill.startSample + 256, bufferToFill.numSamples - 256);
                        }
                    }
                    
                    // stopped
                    this->stopped = true;
                }
            }
        }else
        {
            bufferToFill.clearActiveBufferRegion();
            //this->stopped = true;
            
        }
    }
    virtual void releaseResources() override {}
    
    //------------------------------------------------------------
    //controller
    // these controller will fire sendChangeMessage()
    
    void start()
    {
        if((! this->playing) && this->buffer != nullptr)
        {
            //lock this procee
            {
                const ScopedLock sl (this->callbackLock);
                this->playing = true;
                this->stopped = false;
                this->inputStreamEOF = false;
                
                if(this->pausing)
                {
                    this->afterPausing = true;
                    this->pausing = false;
                }
            }
            // inform the status change
            sendChangeMessage();
        }
    }
    
    void pause()
    {
        if(this->playing)
        {
            // lock this process
            {
                const ScopedLock sl (this->callbackLock);
                this->playing = false;
                this->pausing = true;
            }
            int n = 500;
            while (--n >= 0 && ! stopped)
                Thread::sleep(2);
            
            //inform the status change
            //sendChangeMessage();
        }
    }
    
    void stop()
    {
        if(this->playing)
        {
            // lock this process
            {
                const ScopedLock sl (this->callbackLock);
                this->playing = false;
                this->pausing = false;
                
                //reset for time scheduling
                this->currentOffsetPosition = 0;
                //setNextReadPosition(this->startPosition);
            }
            int n = 500;
            while (--n >= 0 && ! stopped)
                Thread::sleep(2);
            
            //inform the status change
            sendChangeMessage();
        }
    }
    
    //------------------------------------------------------------
    // ===========================================================
    // parameters
    // ===========================================================
    // -----------------------------------------------------------
    // set an AudioBuffer to be played
    void setAudioBuffer(AudioBuffer<float>* audioBuffer, bool ownership, double sampleRate, std::vector<int> outputChannels)
    {
        const ScopedLock sl (this->callbackLock);
        //here buffer is allocated
        this->buffer.set(audioBuffer, ownership);
        this->outputChannels = outputChannels;
        this->sampleRate = sampleRate;
        this->inputStreamEOF = false;
        
        //initialize playSamples with buffer samples
        this->playSamples = this->buffer->getNumSamples();
        
        std::cout << "SoundPlayerClass setAudioBuffer() : nChan = " << this->buffer->getNumChannels() << " : samples = " << this->buffer->getNumSamples() << std::endl;
        
        this->currentOffsetPosition = 0;
        this->playPosition = 0;
    }
    // -----------------------------------------------------------
    // @param1 startPosition in sample of audio data to be played
    // @param2 duration in sample of audio data to be played from startPosition
    // @param3 wait samples time of playing audio data
    // @param4 shouldLoop true = loop mode
    void setParameters(int startPosition, int playSamples, int offset, bool shouldLoop)
    {
        setNextReadPosition(startPosition);
        jassert(playSamples >= 0);
        this->playSamples = playSamples;
        this->looping = shouldLoop;
    }
    
    // startPosition = 0; playSamples = this->buffer->getNumSamples(); offset = 0; shouldLoop = false;
    void initializeParameters()
    {
        if(this->buffer != nullptr)
        {
            setNextReadPosition(0);
            this->playSamples = this->buffer->getNumSamples();

            jassert(this->playSamples >= 0);
            this->looping = false;
        }
    }
    // -----------------------------------------------------------
    // set outputChannels e.g. {0, 1} = 1 and 2 outputs
    void setOutputChannels(std::vector<int>outputChannels)
    {
        this->outputChannels = outputChannels;
    }
    // -----------------------------------------------------------
    // set position to play
    // Note this newPosition should not include "startPosition"
    void setNextReadPosition(int64 newPosition) override
    {
        // check if newPosition is larger than 0
        jassert(newPosition >= 0);
        
        if(this->looping && this->buffer != nullptr)
            newPosition = newPosition % static_cast<int64> (this->buffer->getNumSamples());
        
        this->startPosition = jmin (this->buffer->getNumSamples(), static_cast<int> (newPosition));
        this->playPosition = 0;
        this->currentOffsetPosition = 0;
    }
    // ------------------------------------------------------------
    //get next read position in audio data in sample
    int64 getNextReadPosition() const override { return static_cast<int>( this->startPosition + this->playPosition ); }
    
    int64 getStartPosition() const { return this->startPosition; }
    // ------------------------------------------------------------
    void setPlaySamples(int samples) { this->playSamples = samples; }
    int getPlaySamples() const { return this->playSamples; }
    // ------------------------------------------------------------
    //get total length of the audio data in sample
    int64 getTotalLength() const override { return static_cast<int64> (this->buffer->getNumSamples()); }
    // ------------------------------------------------------------
    //loop flag
    bool isLooping() const override { return this->looping; }
    void setLooping(bool shouldLoop) override { this->looping = shouldLoop; }
    // ------------------------------------------------------------
    // return true if the player has stopped because its input stream ran out of data
    bool hasStreamFinished() const noexcept { return this->inputStreamEOF; }
    bool isPlaying() const noexcept { return this->playing; }
    bool isPausing() const noexcept { return this->pausing; }
    // ------------------------------------------------------------
    //time scheduler. samples in audio processing time
    void setSchedulerInSample(double samples) { this->offset = samples; }
    void setSchedulerInSec(double second) { this->offset = second * this->sampleRate; }
    
    //============================================================
private:
    
    // holds a pointer to an object which can optionally be deleted when this pointer goes out of scope.
    OptionalScopedPointer<AudioBuffer<float>> buffer;
    
    // sample playing position
    int playPosition = 0;
    // parameter : duration to be played
    int playSamples = 0;
    // parameter : start position to be played
    int startPosition = 0;
    // channel
    int nChannel = 0;
    
    int offset = 0;
    // current reading position : offset + playPosition
    int currentOffsetPosition = 0;
    bool looping = false;
    std::vector<int> outputChannels;
    double sampleRate = 44100.0;
    
    //play status
    bool playing = false;
    bool stopped = true;
    bool pausing = false;
    bool afterPausing = false;
    bool inputStreamEOF = false;
    bool isPrepared = false;
    
    
    //other parameters
    float lastGrain = 1.0;
    float gain = 1.0;
    
    //thread lock
    CriticalSection callbackLock;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundPlayerClass)
};

//==========================================================================

#endif /* IRSoundPlayer_h */
