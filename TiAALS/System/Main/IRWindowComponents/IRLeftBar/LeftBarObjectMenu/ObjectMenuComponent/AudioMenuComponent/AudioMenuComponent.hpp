//
//  AudioMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef AudioMenuComponent_hpp
#define AudioMenuComponent_hpp
#include "ObjectMenuComponent.hpp"

class AudioMenuComponent : public ObjectMenuComponent
{
public:
    AudioMenuComponent(IRStr* str, Rectangle<int> frameRect);
    ~AudioMenuComponent();
    // ==================================================
    
    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================
    // ==================================================
    
private:
    // ==================================================
    
    void itemSelected(IRObjectFactory2::t_object* obj) override;
    
    // ==================================================
    
    // ==================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioMenuComponent)
    
};
#endif /* AudioMenuComponent_hpp */
