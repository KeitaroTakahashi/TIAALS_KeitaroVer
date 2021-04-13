//
//  VideoAnnotaterDelegate.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#include "VideoAnnotaterDelegate.hpp"


VideoAnnotaterDelegate::VideoAnnotaterDelegate(VideoAnnotaterBase* base) : base(base)
{
    
}
VideoAnnotaterDelegate::~VideoAnnotaterDelegate()
{
    
}

// ==================================================

void VideoAnnotaterDelegate::eventModifiedAction(Component* modifiedEvent)
{
    this->base->eventModifiedAction(modifiedEvent);
}

void VideoAnnotaterDelegate::eventSelectedAction(Component* selectedEvent)
{
    this->base->eventSelectedAction(selectedEvent);
}

void VideoAnnotaterDelegate::newEventCreatedAction(Component* createdEvent)
{
    this->base->newEventCreatedAction(createdEvent);
}

void VideoAnnotaterDelegate::eventTimeCodeChangedAction(Component* changedEvent)
{
    this->base->eventTimeCodeChangedAction(changedEvent);
}

void VideoAnnotaterDelegate::updateAnnotation()
{
    this->base->updateAnnotation();
}

void VideoAnnotaterDelegate::showEventPosition(Component* event)
{
    this->base->showEventPosition(event);
}

void VideoAnnotaterDelegate::eventActivationChanged(Component* changedEvent)
{
    this->base->eventActivationChanged(changedEvent);
}
// ==================================================

void VideoAnnotaterDelegate::setVideoSize(juce::Point<int> newVideoSize)
{
    this->base->setVideoSize( newVideoSize );
}

juce::Point<int> VideoAnnotaterDelegate::getVideoSize() const
{
    return this->base->getVideoSize();
}

// ==================================================

void VideoAnnotaterDelegate::setCurrentVideoPosition(double currentPosition)
{
    this->base->setCurrentVideoPosition(currentPosition);
    
    if(this->currentPositionChangedCallback != nullptr)
        this->currentPositionChangedCallback(currentPosition);
}
// ==================================================


void VideoAnnotaterDelegate::playVideo()
{
    this->base->playVideo();
}

void VideoAnnotaterDelegate::stopVideo()
{
    this->base->stopVideo();
}

void VideoAnnotaterDelegate::pauseVideo()
{
    this->base->pauseVideo();
}

void VideoAnnotaterDelegate::changeVideoSegment(float begin, float end)
{
    this->base->videoSegmentChanged(begin, end);
}
