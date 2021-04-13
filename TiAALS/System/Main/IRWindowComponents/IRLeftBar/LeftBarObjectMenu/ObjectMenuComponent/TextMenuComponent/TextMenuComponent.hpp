//
//  TextMenuComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 12/08/2019.
//

#ifndef TextMenuComponent_hpp
#define TextMenuComponent_hpp
#include "ObjectMenuComponent.hpp"
#include "Benchmark.h"

class TextMenuComponent : public ObjectMenuComponent
{
public:
    TextMenuComponent(IRStr* str, Rectangle<int> frameRect);
    ~TextMenuComponent();
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextMenuComponent)

};

#endif /* TextMenuComponent_hpp */
