//
//  ImageMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 12/08/2019.
//

#ifndef ImageMenuComponent_hpp
#define ImageMenuComponent_hpp


#include "ObjectMenuComponent.hpp"
#include "Benchmark.h"
class ImageMenuComponent : public ObjectMenuComponent
{
public:
    ImageMenuComponent(IRStr* str,Rectangle<int> frameRect);
    ~ImageMenuComponent();
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageMenuComponent)
    
};

#endif /* ImageMenuComponent_hpp */
