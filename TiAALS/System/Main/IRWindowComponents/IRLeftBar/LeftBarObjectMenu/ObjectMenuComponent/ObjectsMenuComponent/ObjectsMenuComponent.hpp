//
//  ObjectsMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#ifndef ObjectsMenuComponent_hpp
#define ObjectsMenuComponent_hpp

#include "ObjectMenuComponent.hpp"

class ObjectsMenuComponent : public ObjectMenuComponent
{
public:
    ObjectsMenuComponent(IRStr* str, Rectangle<int> frameRect);
    ~ObjectsMenuComponent();
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObjectsMenuComponent)
    
};
#endif /* ObjectsMenuComponent_hpp */
