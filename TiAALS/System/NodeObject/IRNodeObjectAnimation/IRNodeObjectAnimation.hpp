//
//  IRNodeObjectAnimation.hpp
//  IRiMaS
//
//  Created by Keitaro on 13/03/2020.
//

#ifndef IRNodeObjectAnimation_hpp
#define IRNodeObjectAnimation_hpp

#include "IRNodeComponent.hpp"

class IRNodeObjectAnimation
{
public:
    enum IRNodeObjectAnimationStatus
    {
        NONE,
        SHOW,
        HIDE,
        MOVESTART,
        MOVESTOP
        
    };
    
    
    IRNodeObjectAnimation(IRNodeComponent* obj);
    virtual ~IRNodeObjectAnimation();
    // ============================================================
    
    void actionStart();
    void actionEnd();
    // action
    void showObject();
    void hideObject();
    void moveStart();
    void moveStop();
    // ============================================================
    // ============================================================
    // ============================================================

    void setBeginTimeCode(float newBeginTimeCode);
    void setEndTimeCode(float newEndTimeCode);
    float getBeginTimeCode() const { return this->beginTime; }
    float getEndTimeCode() const { return this->endTime; }
    
    bool tryTrigerAnimation(float currentTime);
    bool isAnimated() const { return this->animated; }
    
    // this is not used unless you want to force this object aniated or non-animated otherwise, animated status is generally controlled by setCurrentTimeCode
    void setAnimated(bool flag) { this->animated = flag; }
    
    void setAnimationActive(bool flag) { this->animationActive = flag; }
    bool isAnimationActive() const { return this->animationActive; }
    
    void setCurrentTimeCode(float currentTime);
    
    // ============================================================
    IRNodeObjectAnimationStatus getStatus() const { return this->status; }
    // ============================================================

    // request to update Animation
    virtual void StatusUpdated(){};
private:
    
    IRNodeComponent* obj;
    // ============================================================

    IRNodeObjectAnimationStatus status = NONE;
    // ============================================================
    // ### ANIMATION EVENT ####
    // Time Code
    float beginTime = 0;
    float endTime = 0;
    // ============================================================
    // Animation
    int beginPos = 0;
    int endPos = 0;
    // ============================================================
    // current Time
    float currentTimeCode = 0;
    
    bool animated = false;
    bool animationActive = true;
    // ============================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRNodeObjectAnimation)
};

#endif /* IRNodeObjectAnimation_hpp */
