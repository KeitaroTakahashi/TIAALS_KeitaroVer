//
//  IRNSViewManager.hpp
//  IRiMaS
//
//  Created by Keitaro on 31/10/2019.
//

#ifndef IRNSViewManager_hpp
#define IRNSViewManager_hpp

#include "JuceHeader.h"

class IRNSViewManager
{
public:
    IRNSViewManager()
    {
        
    }
    
    ~IRNSViewManager()
    {
        
    }
    
    // works only for macOS
    void bringOpenGLContextFront(juce::Component* owner, NSViewComponent* view);
    
};

#endif /* IRNSViewManager_hpp */
