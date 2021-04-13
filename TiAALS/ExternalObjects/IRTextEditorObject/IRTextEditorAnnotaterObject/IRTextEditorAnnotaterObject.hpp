//
//  IRTextEditorAnnotaterObject.hpp
//  IRiMaS
//
//  Created by Keitaro on 19/02/2020.
//

#ifndef IRTextEditorAnnotaterObject_hpp
#define IRTextEditorAnnotaterObject_hpp

#include "IRTextEditorObject.hpp"

class IRTextEditorAnnotaterObject : public IRTextEditorObject
{
public:
    IRTextEditorAnnotaterObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRTextEditorAnnotaterObject();
    
    // ==================================================
    void onResized() override;
    void paint(Graphics& g) override;
    
    // ==================================================
    // use for annotator
    void setAnnotationBounds(Rectangle<int> bounds4This,
                             Rectangle<int> parentBounds);
    void setMediaResolution(int w, int h);
    
    // ==================================================

private:
    
    juce::Point<int> mediaResolution;

    // ==================================================

    // ==================================================

};

#endif /* IRTextEditorAnnotaterObject_hpp */
