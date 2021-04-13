
#ifndef IRLabelObjectPreference_h
#define IRLabelObjectPreference_h


#include "IRPreferenceObject.hpp"
#include "FontGUI.hpp"
#include "ColourLib.h"
#include "singletonClass.hpp"




class IRLabelObjectPreference : public IRPreferenceObject
{
    
public:
    
    IRLabelObjectPreference(String title, Rectangle<int> frameRect, IRStr* str);
    ~IRLabelObjectPreference();

    void resized() override;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    FontGUI* getFontGUI();

    
private:

    // FontGUI* fontGUI;
    std::unique_ptr<FontGUI> fontGUI;
    
    // system colour
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRLabelObjectPreference)
};




#endif /* IRLabelObjectPreference_h */





