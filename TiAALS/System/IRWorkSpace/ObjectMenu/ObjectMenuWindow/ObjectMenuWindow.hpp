
#ifndef ObjectMenuWindow_hpp
#define ObjectMenuWindow_hpp

#include "JuceHeader.h"

#include "ObjectListMenu.hpp"




class ObjectMenuWindow : public DocumentWindow
{
    
public:
    
    ObjectMenuWindow(String name, Rectangle<int> frameRect, ObjectListMenu* menu);
    ~ObjectMenuWindow();
    
private:
    
    // setup systme colour
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ObjectMenuWindow)
};




#endif /* ObjectMenuWindow_hpp */
