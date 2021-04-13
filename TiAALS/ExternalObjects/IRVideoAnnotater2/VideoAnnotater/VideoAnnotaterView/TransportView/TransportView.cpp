//
//  TransportView.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#include "TransportView.hpp"

TransportView::TransportView(IRStr* str) : IRStrComponent(str)
{
    
}

TransportView::~TransportView()
{
    
}

// ==================================================

void TransportView::changeListenerCallback(ChangeBroadcaster* source)
{
    
}
// ==================================================

void TransportView::resized()
{
    if(this->transport != nullptr)
    {
        this->transport->setBounds(getLocalBounds());
    }
}

void TransportView::paint(Graphics& g)
{
    g.fillAll(Colours::grey);
    g.drawText("transport view", getLocalBounds(), Justification::centred);
}
// ==================================================

void TransportView::setVideoTransport(VideoTransportComponent* transport)
{
    this->transport = transport;
    
    addAndMakeVisible(this->transport);
    resized();
}
