//
//  VideoAnnotaterDelegate.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#ifndef VideoAnnotaterDelegate_hpp
#define VideoAnnotaterDelegate_hpp

#include "VideoAnnotaterBase.hpp"

class VideoAnnotaterDelegate
{
public:
    VideoAnnotaterDelegate(VideoAnnotaterBase* base);
    ~VideoAnnotaterDelegate();

    // ==================================================

    void eventModifiedAction(Component* modifiedEvent);
    void eventSelectedAction(Component* selectedEvent);
    void newEventCreatedAction(Component* createdEvent);
    void eventTimeCodeChangedAction(Component* changedEvent);
    void updateAnnotation();
    void showEventPosition(Component* event);
    void eventActivationChanged(Component* changedEvent);
    // ==================================================
    void playVideo();
    void stopVideo();
    void pauseVideo();
    
    void changeVideoSegment(float begin, float end);
    
    // ==================================================

    void setVideoSize(juce::Point<int> newVideoSize);

    juce::Point<int> getVideoSize() const;
    
    void setCurrentVideoPosition(double currentPosition);
    std::function<void(double)> currentPositionChangedCallback = nullptr;
    
    double getCurrentVideoPosition() const { return this->base->getCurrentVideoPosition(); }

    // ==================================================

    VideoAnnotaterBase* getBase() { return this->base; }
    private:
    // ==================================================

    VideoAnnotaterBase* base = nullptr;
    
    double currentPosition = 0;

    // ==================================================
};

#endif /* VideoAnnotaterDelegate_hpp */
