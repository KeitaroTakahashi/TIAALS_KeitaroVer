
#ifndef IRTextEditorObjectPreference_h
#define IRTextEditorObjectPreference_h

#include "IRPreferenceObject.hpp"
#include "FontGUI.hpp"

class IRTextEditorObjectPreference : public IRPreferenceObject
{
    
public:
    
    IRTextEditorObjectPreference(String title, Rectangle<int> frameRect, IRStr* str);
    ~IRTextEditorObjectPreference();
    
    void resized() override;
    
    void initialize();
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    FontGUI* getFontGUI();
    
    
private:
    
    // FontGUI* fontGUI;
    std::unique_ptr<FontGUI> fontGUI;
    
    // system colour
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRTextEditorObjectPreference)
    
};




#endif /* IRTextEditorObjectPreference_h */





