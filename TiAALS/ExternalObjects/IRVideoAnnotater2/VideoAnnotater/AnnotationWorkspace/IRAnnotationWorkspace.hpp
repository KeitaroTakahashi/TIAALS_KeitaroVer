//
//  IRAnnotationWorkspace.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 13/04/2021.
//

#ifndef IRAnnotationWorkspace_hpp
#define IRAnnotationWorkspace_hpp

#include "IRWorkspaceComponent.hpp"
#include "IRVideoAnnotationObjectsHeader.h"
#include "IRObjectCreater.hpp"

class IRAnnotationWorkspace : public IRWorkspaceComponent
{
public:
    IRAnnotationWorkspace(String title,
                            Rectangle<int> draggableMargin,
                            IRStr* str,
                          int index = 0);
    
    ~IRAnnotationWorkspace();
    
    // --------------------------------------------------
    
    void loadThisFromSaveData(json11::Json saveData) override;
    // --------------------------------------------------
private:
    
    IRNodeObject* createObjectFromId(String id);
    IRNodeObject* createTextObjectFromId();
    IRNodeObject* createShapeObjectFromId();
    IRNodeObject* createImageObjectFromId();

};

#endif /* IRAnnotationWorkspace_hpp */
