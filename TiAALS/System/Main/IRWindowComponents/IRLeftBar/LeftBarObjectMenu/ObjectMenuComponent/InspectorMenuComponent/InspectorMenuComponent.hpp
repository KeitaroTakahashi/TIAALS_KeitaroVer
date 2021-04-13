//
//  InspectorMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef InspectorMenuComponent_hpp
#define InspectorMenuComponent_hpp

#include "ObjectMenuComponent.hpp"

class InspectorMenuComponent : public ObjectMenuComponent
{
public:
    InspectorMenuComponent(IRStr* str, Rectangle<int>frameRect);
    ~InspectorMenuComponent();
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InspectorMenuComponent)

};

#endif /* InspectorMenuComponent_hpp */
