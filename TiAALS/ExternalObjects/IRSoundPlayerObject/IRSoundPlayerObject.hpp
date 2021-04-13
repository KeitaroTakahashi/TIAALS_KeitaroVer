
#ifndef IRAudioPlayerObject_hpp
#define IRAudioPlayerObject_hpp

#include "IRAudioReader.hpp"
#include "SoundPlayer_ThreadSafe.h"
#include "IRNodeObject.hpp"




class IRSoundPlayerObject : public IRNodeObject
{
    
public:
    
    IRSoundPlayerObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRSoundPlayerObject();

    IRNodeObject* copyThisObject() override;
    
    void onResized() override;
    void paint(Graphics& g) override;
    
    AudioPlayer_threadSafe* getAudioSource();
    
    
private:
    
    AudioPlayer_threadSafe *player;
    // std::shared_ptr<AudioPlayer_threadSafe> player;
    
};




#endif /* IRAudioPlayerObject_hpp */



