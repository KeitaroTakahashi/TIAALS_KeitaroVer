//
//  IRViewPort.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 21/05/2019.
//

#ifndef IRViewPort_hpp
#define IRViewPort_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
class IRViewPort : public Viewport,
public IRStrComponent
{
public:
    IRViewPort(IRStr* str);
    ~IRViewPort();
    // ==================================================

    std::function<void(Rectangle<int>)> visibleAreaChangedCallback;
    std::function<void()> viewedComponentChangedCallback;
    
    virtual void visibleAreaChangedAction(const Rectangle< int > &newVisibleArea) {}

private:
   
    // ==================================================

    // ==================================================

    // ==================================================

    
    void visibleAreaChanged (const Rectangle< int > &newVisibleArea) override;
    void viewedComponentChanged (Component *newComponent) override;
    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

};

#endif /* IRViewPort_hpp */
