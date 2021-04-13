//
//  IRWorkspace.hpp
//  IRiMaS
//
//  Created by Keitaro on 18/09/2019.
//

#ifndef IRWorkspace_hpp
#define IRWorkspace_hpp

#include "IRWorkspaceComponent.hpp"


class IRWorkspace : public IRWorkspaceComponent
{
    
public:
    IRWorkspace(String title, Rectangle<int> draggableMargin, IRStr* str, int index = 0);
    ~IRWorkspace();
    
    // =============================================
    // use this instead of juce oriented paint method
    void onPaint(Graphics& g) override;
    
    // =============================================

private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRWorkspace)

};


#endif /* IRWorkspace_hpp */
