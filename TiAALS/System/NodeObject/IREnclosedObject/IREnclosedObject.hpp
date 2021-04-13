//
//  IREnclosedObject.hpp
//  IRiMaS
//
//  Created by Keitaro on 23/02/2020.
//

#ifndef IREnclosedObject_hpp
#define IREnclosedObject_hpp

#include "EncloseButton.h"

class IREnclosedObject : public Component
{
public:
    IREnclosedObject();
    ~IREnclosedObject();
    
    // ==================================================

    void resized() override;
    void paint(Graphics& g) override;
    
    // ==================================================
    void setColour(Colour colour);
    Colour getColour() const;
    // ==================================================


    void mouseDown(const MouseEvent& e) override;
    std::function<void()> onClick;
    
    // ==================================================

private:
    
    // ==================================================
    Colour bodyColour;
    // ==================================================

    
};
#endif /* IREnclosedObject_hpp */
