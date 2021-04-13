//
//  IRNodeComponentAnnotation.cpp
//  IRiMaS
//
//  Created by Keitaro on 19/02/2020.
//

#include "IRNodeComponent.hpp"


void IRNodeComponent::setMediaResolution(int w, int h)
{
    this->mediaResolution.setX(w);
    this->mediaResolution.setY(h);
}

void IRNodeComponent::setMediaObjectSize(int w, int h)
{
    this->mediaObjectSize.setX(w);
    this->mediaObjectSize.setY(h);
    
    this->resolutionRatioToMedia.setX((float)this->mediaObjectSize.getX() /
                                      (float)this->mediaResolution.getX());
    this->resolutionRatioToMedia.setY((float)this->mediaObjectSize.getY() /
                                      (float)this->mediaResolution.getY());
}
