//
//  VideoAnnotaterBase.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#ifndef VideoAnnotaterBase_hpp
#define VideoAnnotaterBase_hpp

#include <JuceHeader.h>

class VideoAnnotaterBase
{
public:
    VideoAnnotaterBase();
    virtual ~VideoAnnotaterBase();
    
    // ==================================================
    // Annotation
    virtual void eventModifiedAction(Component* modifiedEvent) {};
    virtual void eventSelectedAction(Component* selectedEvent) {};
    virtual void newEventCreatedAction(Component* selectedEvent) {};
    virtual void eventTimeCodeChangedAction(Component* changedEvent) {};
    virtual void updateAnnotation() {};
    virtual void showEventPosition(Component* event) {};
    virtual void eventActivationChanged(Component* changedEvent) {};

    // ==================================================
    // Video Player
    virtual void playVideo() {};
    virtual void stopVideo() {};
    virtual void pauseVideo() {};
    
    virtual void videoSegmentChanged(float begin, float end) {};
    virtual void playPositionUpdated(float sec) {};
    
    // ==================================================

    void setVideoSize(juce::Point<int> newVideoSize) { this->videoSize = newVideoSize; }
    juce::Point<int> getVideoSize() const { return this->videoSize; }
    
    void setCurrentVideoPosition(double currentPosition);
    std::function<void(double)> currentVideoPositionChangedCallback = nullptr;
    double getCurrentVideoPosition() const { return this->currentPosition; }
    // ==================================================


    private:
    // ==================================================
    juce::Point<int> videoSize;
    double currentPosition = 0;

};

#endif /* VideoAnnotaterBase_hpp */
