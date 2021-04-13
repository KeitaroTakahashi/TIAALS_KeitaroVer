
#ifndef PreferenceWindow_hpp
#define PreferenceWindow_hpp


#include "JuceHeader.h"
#include "IRPreferenceSpace.hpp"

class PreferenceWindow : public DocumentWindow,
                         public IRComponents,
                         public ChangeListener
{
    
public:
    
    PreferenceWindow(String name);
    ~PreferenceWindow();
    
    void changeListenerCallback(ChangeBroadcaster* source) override;
    
    void closeButtonPressed() override;
    
    IRPreferenceSpace* getPreferenceSpace();
    
private:
    std::unique_ptr<IRPreferenceSpace> preferenceSpace;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PreferenceWindow)
};





#endif /* PreferenceWindow_hpp */




