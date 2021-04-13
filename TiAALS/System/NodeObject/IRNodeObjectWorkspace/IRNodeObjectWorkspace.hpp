//
//  IRNodeObjectWorkspace.hpp
//  IRiMaS
//
//  Created by Keitaro on 10/03/2020.
//

#ifndef IRNodeObjectWorkspace_hpp
#define IRNodeObjectWorkspace_hpp

#include "IRWorkspaceComponent.hpp"

class IRNodeObjectWorkspace : public IRWorkspaceComponent
{
public:
    IRNodeObjectWorkspace(String title, Rectangle<int> draggableMargin, IRStr* str);
    ~IRNodeObjectWorkspace();
    // ==================================================

    // ==================================================

    void setFixObjectSizeRatioWithOriginalSize(bool flag, Rectangle<float> originalSize);
    
    // ==================================================
    // Object creator
    void bindObjectOnWorkspace(IRNodeObject* nodeObj);
    
    void removeObjectOnWorkspace(IRNodeObject* nodeObj);
    // ==================================================
    // ==================================================
    // ==================================================

private:
    
    // ==================================================
    // ==================================================
    // ==================================================

};

#endif /* IRNodeObjectWorkspace_hpp */
