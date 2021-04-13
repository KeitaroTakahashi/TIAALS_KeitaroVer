//
//  IRAutomationObjectPreference.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 23/10/2018.
//

#ifndef IRAutomationObjectPreference_h
#define IRAutomationObjectPreference_h

#include "IRPreferenceObject.hpp"
#include "AutomationPreferenceUI.h"

class IRAutomationObjectPreference : public IRPreferenceObject
{
public:
    IRAutomationObjectPreference(String title, Rectangle<int> frameRect, IRStr* str) :
    IRPreferenceObject(title,frameRect, str)
    {
        this->UI = new AutomationPreferenceUI(title, str);
        addAndMakeVisible(this->UI);
        
       
    }
    
    ~IRAutomationObjectPreference()
    {
        delete this->UI;
    }
    
    //===============================================================
    void resized() override
    {
        IRPreferenceObject::resized();
        this->UI->setBounds(0,0,getWidth(), getHeight());
        
        
    }
    
    //===============================================================
    //Listener
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        
    }
    
    AutomationPreferenceUI* getUI() { return this->UI; }
    
    
private:
    
    AutomationPreferenceUI* UI;
    
    
    
    // system colour
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRAutomationObjectPreference)
};

#endif /* IRAutomationObjectPreference_h */
