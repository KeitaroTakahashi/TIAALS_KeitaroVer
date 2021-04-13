//
//  PlayerMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef PlayerMenuComponent_hpp
#define PlayerMenuComponent_hpp

#include "ObjectMenuComponent.hpp"

class PlayerMenuComponent : public ObjectMenuComponent
{
public:
    PlayerMenuComponent(IRStr* str, Rectangle<int> frameRect);
    ~PlayerMenuComponent();
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerMenuComponent)
    
};
#endif /* PlayerMenuComponent_hpp */
