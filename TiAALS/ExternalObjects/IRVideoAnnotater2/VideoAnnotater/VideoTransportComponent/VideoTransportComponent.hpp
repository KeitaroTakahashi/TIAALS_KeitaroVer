//
//  VideoTransportComponent.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 25/03/2021.
//

#ifndef VideoTransportComponent_hpp
#define VideoTransportComponent_hpp

#include "IRImageButton.hpp"
#include "TimeCode.h"
#include "VideoSegmentTimeSlider.h"
#include "VideoAnnotaterDelegate.hpp"

class VideoTransportComponent : public Component,
public IRStrComponent,
public VideoAnnotaterDelegate,
public ChangeBroadcaster,
private Slider::Listener
{
public:
    enum VideoTransportStatus
    {
        OpenVideoFile,
        OpenAnnotationFile,
        SaveAnnotationFile,
        addEventButtonClicked,
        deleteEventButtonClicked,
        play,
        stop,
        playPositionChanged,
        videoSegmentChanged,
        videoSegmentMinChanged,
        videoSegmentMaxChanged,
        NONE
    };
    
    VideoTransportComponent(IRStr* str, VideoAnnotaterBase* base);
        
        
    ~VideoTransportComponent();
        
        
    // ==================================================
        
    virtual void paint(Graphics& g) override;
    virtual void resized() override;

    // ==================================================
        
    void addEventButtonClickedAction();
    void deleteEventButtonClickedAction();
        
    // ==================================================

    void openVideoButtonClicked();
        
        
    void openAnnotationButtonClicked();
        
        
    void saveAnnotationButtonClicked();
        
    // ==================================================
    void closeEventMenu() {}
    // ==================================================
        
    void setVideoLengthInSec(float videoLengthInSec);
    void setCurrentPlayingPosition(double pos);
    void setCurrentPlayingPositionLabel(double pos); // label only
    double getCurrentPlayingPosition() const { return this->timeCodeSlider.getValue(); }
    void setVideoRange(float begin, float end);

    // ==================================================
    VideoTransportStatus getStatus() const { return this->status; }
    float getPlayPosition() { return this->timeCode.getTimeCodeInSec(); }
    // ==================================================

    private:
    // ==================================================
    VideoTransportStatus status = NONE;
    float videoLengthInSec = 0;
    // ==================================================
    void createButton(IRImageButton* button, IRIconBank::IRIconImage img);
        
    // ==================================================

    //TextButton openVideoButton;
    TextButton openAnnotationButton;
    TextButton saveAnnotationButton;
    IRImageButton addEventButton;
    IRImageButton deleteEventButton;

    //controller
    IRImageButton playButton;
    void playButtonClickedAction()
    {
        
        playVideo(); // delegate
        
        this->status = play;
        sendChangeMessage();
    }
    IRImageButton stopButton;
    void stopButtonClickedAction()
    {
        stopVideo(); // delegate
        
        this->status = stop;
        sendChangeMessage();
    }
    
    

    // ==================================================
    TimeCode timeCode;
    void timeCodeChanged();
        
    // ==================================================
        
    Slider timeCodeSlider;
    void sliderValueChanged (Slider *slider) override;
        
    // ==================================================
        
    VideoSegmentTimeSlider videoSegmentSlider;

    void videoSegmentChangedAction();
    void videoSegmentMinChangedAction();
    void videoSegmentMaxChangedAction();
        
        
    public:
        // use the following functions when you want to sync any methods called when min or max value of video segments are modified.
        std::function<void()> videoSegmentMinChangedCallback;
        std::function<void()> videoSegmentMaxChangedCallback;
        
        std::vector<float> getSegmentValue()
        {
            return this->videoSegmentSlider.getSegmentValue();
        }
        
        // ==================================================
        
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VideoTransportComponent)
};

#endif /* VideoTransportComponent_hpp */
