//
//  TransportView.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#ifndef TransportView_hpp
#define TransportView_hpp

#include "IRStrComponent.hpp"
#include "VideoTransportComponent.hpp"

class TransportView : public Component,
public IRStrComponent,
public ChangeListener
{
public:
    TransportView(IRStr* str);
    ~TransportView();
    // ==================================================
    // ==================================================

    void setVideoTransport(VideoTransportComponent* transport);
private:
    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================
    
    void changeListenerCallback(ChangeBroadcaster* source) override; // JUCE oriented

    // ==================================================
    VideoTransportComponent* transport;


    
};
#endif /* TransportView_hpp */
