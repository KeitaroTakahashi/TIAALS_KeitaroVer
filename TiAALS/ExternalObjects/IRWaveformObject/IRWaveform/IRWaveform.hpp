
#ifndef IRWaveform_hpp
#define IRWaveform_hpp

#include "IRFoundation.h"
#include "IRUIAudioFoundation.hpp"
#include "IRAudioReader.hpp"
#include "IRSoundPlayer.h"
#include "KeAnimationComponent.h"


class IRWaveform : public IRUIAudioFoundation,
                   private ChangeListener,
                   public ChangeBroadcaster,
public IRAudio::Listener,
public KeAnimationComponent
{
    
public:
    
    enum IRWaveformStatus
    {
        DRAGOUT,
        DROPOUT,
        EDITMODECHANGE,
        PROJECTSAVE,
        zoomInfoShared,
        currentPlayedFrameShared,
        viewPosShared,
        NONE
        
    };
    
    enum IRWaveformPlayerStatus
    {
       // player
        PLAYING,
        PAUSED,
        STOPPED,
        END_REACHED,
        PLAYPOSITION_SLAVED, // this represents the status that this object does not actually play any audio data, but its playing position cursor moves because its linked audiio object is playing the audio data.
        NOACTION
    };
    
    IRWaveform(IRNodeObject* parent, IRStr* str);
    ~IRWaveform();
    
    bool openFile();
    bool openFile(String path);

    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    // called when file import completed, and before re-drawn the waveform thumbnail
    virtual void fileImportCompletedAction() {};
    void getFilePtr(File file);
    void makeThumbnail(String path);
    
    virtual void resized() override;
    void paint(Graphics& g) override;
    
    void setStart(double ms);
    double getStart() const;
    void setDisplayDuration(double ms);
    double getDisplayDuration() const;
    double getTotalLength() const;
    void setChannelIndex(int channelIndex);
    void setZoomFactor(double zoomFactor);
    double getZoomFactor() const;
    double getSampleRate() const;
    bool isWaveformPainted() const;
    
    // ==================================================
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    virtual void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    virtual void releaseResources() override;
    // ==================================================

    void play();
    void play(int start, int duration, int offset, bool looping);
    void stop();
    void pausing();
    bool isPlaying() const;
    
    SoundPlayerClass* getPlayer() const;

    String getPath() const { return this->path; }
    
    DataAllocationManager<IRAudio>* audioData = nullptr;

    //IRAudio audioFile;
    std::shared_ptr<SoundPlayerClass> player;
    
    // ==================================================
    void createPlayingLine(int64 currentFrame);

    void updatePlayingLine();

   
    // ==================================================
    //sharedInfo
    
    void setZoomInfo(juce::Point<float> zoom) {
        this->zoomInfo = zoom;
        if(this->audioData != nullptr)
        {
            auto data = this->audioData->getData();
            data->setZoomInfo(this->zoomInfo);
        }
    }
    
    void setZoomInfo(float w, float h) {
        this->zoomInfo = juce::Point<float>(w, h);
        setZoomInfo(this->zoomInfo);
    }
    
    void linkZoomInfo(Component* comp);
    void linkViewPosition(Component* comp);
    
    juce::Point<float> getZoomInfo() const { return this->zoomInfo; }
    
    void setCurrentPlayedFrame(int64 frame) { this->currentPlayedFrame = frame; }
    int64 getCurrentPlayedFrame() const { return this->currentPlayedFrame; }
    
    void linkCurrentPlayedFrame(Component* comp);
    
    void setVisiblePos(juce::Point<int>pos) { this->visiblePos = pos; }
    juce::Point<int> getVisiblePos() const { return this->visiblePos; }
    
    // called by IRAudio
    void zoomInOutOperatedFromComponent(IRAudio* obj) override;
    void audioPlayOperatedFromComponent(IRAudio* obj) override;
    void viewPortPositionFromComponent(IRAudio* obj) override;

    IRWaveformStatus getStatus() const { return this->status; }
    IRWaveformStatus status = NONE;
    
    IRWaveformPlayerStatus segmentPlayerStatus = NOACTION;
    IRWaveformPlayerStatus getSegmentPlayerStatus() const { return this->segmentPlayerStatus; }

    // ==================================================
    
    void deinitializeAudioData();

private:
    
    File file;
    String path;
    IRNodeObject* parent;
    TextButton openButton;

    bool drawWaveform = false;
    
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;
    
    // parameters
    // the beginning of the audio file in ms
    double start = 0.0;
    // the duration of the audio file in ms
    double duration = 0.0;
    int channelIndex = 0;
    double zoomFactor = 1.0;
    
    Rectangle<int> playingLine;
    
    // ---------------------------------------------------------------------------
    // file import  USE fileImportCompletedAction(); for override
    void fileImportCompleted();

    // ---------------------------------------------------------------------------
    // sharedInformation
    // current playing frame in samples
    // currentPlayedFrame counts from start value which represents the beginning of the audio file in ms
    int64 currentPlayedFrame = 0;
    juce::Point<int>visiblePos;
    juce::Point<float> zoomInfo;
    
    // ---------------------------------------------------------------------------
    
    void updateAnimationFrame() override;
    // ---------------------------------------------------------------------------
    std::string randomIDForPtr;
    
    // ---------------------------------------------------------------------------

    //thread lock
    CriticalSection callbackLock;

   

};


#endif /* IRWaveform_hpp */




