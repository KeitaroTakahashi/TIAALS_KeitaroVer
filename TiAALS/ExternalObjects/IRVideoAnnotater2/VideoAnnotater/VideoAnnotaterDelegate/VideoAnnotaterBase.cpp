//
//  VideoAnnotaterBase.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#include "VideoAnnotaterBase.hpp"

VideoAnnotaterBase::VideoAnnotaterBase()
{
    
}

VideoAnnotaterBase::~VideoAnnotaterBase()
{
    
}


void VideoAnnotaterBase::setCurrentVideoPosition(double currentPosition)
{
    this->currentPosition = currentPosition;
    
    playPositionUpdated(currentPosition);
    
    if(this->currentVideoPositionChangedCallback != nullptr)
        this->currentVideoPositionChangedCallback(currentPosition);
}
