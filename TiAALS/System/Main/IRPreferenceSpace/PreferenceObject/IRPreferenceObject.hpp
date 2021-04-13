
#ifndef IRPreferenceObject_hpp
#define IRPreferenceObject_hpp


#include "JuceHeader.h"
#include "IRComponents.hpp"
#include "IRStrComponent.hpp"

class IRPreferenceObject : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener
{
    
public:
    
    IRPreferenceObject(String title, Rectangle<int> frameRect, IRStr* str);
    ~IRPreferenceObject();
    
    virtual void resized() override;
    virtual void paint(Graphics& g) override;
    
    virtual void changeListenerCallback(ChangeBroadcaster* source) override;
    
private:
    Rectangle<int> frameRect;
};



#endif /* IRPreferenceObject_hpp */




