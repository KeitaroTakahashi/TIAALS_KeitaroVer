
#ifndef IRMultiPurposeObject_hpp
#define IRMultiPurposeObject_hpp

#include "JuceHeader.h"

#include "IRNodeObject.hpp"

class IRMultiPurposeObject : public IRNodeObject
{
    
public:
    IRMultiPurposeObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRMultiPurposeObject();
    
    IRNodeObject* copyContents(IRNodeObject* object) override;
    
    void onResized() override;
    void paint(Graphics& g) override;
    
    void setBoundsInRatio(float x, float y, float w, float h);
    
    Rectangle<float> getBoundsInRatio() const;
    
    void renewBounds();

    bool isBoundsRatio() const;
    void setBoundsRatio(bool flag);
    
    void mouseDownEvent(const MouseEvent& e) override;
    void mouseUpEvent(const MouseEvent& e) override;
    
    void statusChangedWrapper(IRNodeComponentStatus status) override;
    
private:
    
    // for audio parametter
    double start = 0.0;
    double duration = 0.0;
    
    int startSample = 0;
    int durationSample = 0;
    
    bool boundsRatioFlag = false;
    
    // ratio to its parent
    float xRatio = 0.0;
    float yRatio = 0.0;
    float wRatio = 0.0;
    float hRatio = 0.0;

};


#endif /* IRMultiPurposeObject_hpp */




