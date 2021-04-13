//
//  PreferenceMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef PreferenceMenuComponent_hpp
#define PreferenceMenuComponent_hpp


#include "ObjectMenuComponent.hpp"
#include "PreferenceGUI.h"

class PreferenceMenuComponent : public ObjectMenuComponent
{
public:
    PreferenceMenuComponent(IRStr* str, Rectangle<int>frameRect);
    ~PreferenceMenuComponent();
    // ==================================================
    
    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================
    // ==================================================
    
private:
    // ==================================================
    
    void itemSelected(IRObjectFactory2::t_object* obj) override;
    
    // ==================================================
    
    PreferenceGUI gui;

    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreferenceMenuComponent)

};
#endif /* PreferenceMenuComponent_hpp */
