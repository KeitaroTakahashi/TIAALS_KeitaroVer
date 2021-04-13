
#ifndef IRPreferenceSpace_hpp
#define IRPreferenceSpace_hpp


#include "JuceHeader.h"
#include "IRPreferenceObject.hpp"

class IRPreferenceSpace : public Component,
                          public IRComponents,
                          public ChangeBroadcaster,
                          public ChangeListener
{
public:
    IRPreferenceSpace(String title, Rectangle<int> frameRect);
    ~IRPreferenceSpace();
    
    void resized() override;
    void paint(Graphics& g) override;
    
    String getTitle();
    
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    void setPreferenceObj(IRPreferenceObject* preferenceObj);
    IRPreferenceObject* getPreferenceObj();

private:
    String title;
    bool isPreferenceObjAlreadySet { false };
    IRPreferenceObject* preferenceObj;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRPreferenceSpace)
};





#endif /* IRPreferenceSpace_hpp */




