//
//  KeAnimationComponent.h
//  NewProject
//
//  Created by Keitaro on 03/12/2018.
//

#ifndef KeAnimationComponent_h
#define KeAnimationComponent_h

class KeAnimationComponent : public Timer
{
    
public:
    
    KeAnimationComponent()
    {
        
    }
    
    
    void setFps(int fps)
    {
        jassert (fps > 0 && fps < 1000);
        this->fps = fps;
    }
    
    void startAnimation()
    {
        if(!isTimerRunning())
            startTimerHz(this->fps);
    }
    
    void stopAnimation()
    {
        if(isTimerRunning()) stopTimer();
    }
    virtual void updateAnimationFrame() = 0;
    
    
private:
    
    void timerCallback() override
    {
        updateAnimationFrame();
    }
    
    int fps;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KeAnimationComponent)
    
};

class KMoveTo
{
public:
    KMoveTo()
    {
        
    }
    ~KMoveTo()
    {
        
    }
    
    void setSpeed(float speed) { this->speed = speed; }
    void animation()
    {
        this->current = (this->dest - this->prev) * this->speed +
        this->prev;
        
        this->prev = this->current;
    }
    
    void setValue(float dest) { this->dest = dest; }
    float getValue() const { return this->current; }
    
private:
    float dest = 0;
    float prev = 0;
    float current = 0;
    
    float speed = 0.2;
    
};


#endif /* KeAnimationComponent_h */
