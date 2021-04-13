//
//  IRAudioPlayer.hpp
//  IRiMaS
//
//  Created by Keitaro on 13/12/2019.
//

#ifndef IRAudioPlayer_hpp
#define IRAudioPlayer_hpp

#include "IRNodeObject.hpp"
#include "IRAudio.hpp"

class IRAudioPlayer : public PositionableAudioSource,
                      public ChangeBroadcaster
{
public:
    IRAudioPlayer();
    ~IRAudioPlayer();
    // ==================================================
    // ==================================================
    // ==================================================

    // ==================================================
private:
    
    // ==================================================
    // ==================================================
    // ==================================================
    // ==================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRAudioPlayer)

};
#endif /* IRAudioPlayer_hpp */
