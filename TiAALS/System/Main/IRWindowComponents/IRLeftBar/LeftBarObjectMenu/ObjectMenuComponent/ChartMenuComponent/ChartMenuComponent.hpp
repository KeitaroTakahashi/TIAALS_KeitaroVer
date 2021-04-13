//
//  ChartMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef ChartMenuComponent_hpp
#define ChartMenuComponent_hpp

#include "ObjectMenuComponent.hpp"

class ChartMenuComponent : public ObjectMenuComponent
{
public:
    ChartMenuComponent(IRStr* str, Rectangle<int> frameRect);
    ~ChartMenuComponent();
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChartMenuComponent)
    
};
#endif /* ChartMenuComponent_hpp */
