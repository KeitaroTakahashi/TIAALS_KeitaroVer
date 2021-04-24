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
    
    virtual void loadThisFromSaveData(json11::Json saveData) override;
    // --------------------------------------------------
    
    IRNodeObject* createObjectFromId(String id, IRWorkspaceComponent* parent);

private:
    
    IRNodeObject* createTextObjectFromId(IRWorkspaceComponent* parent);
    IRNodeObject* createShapeObjectFromId(IRWorkspaceComponent* parent);
    IRNodeObject* createImageObjectFromId(IRWorkspaceComponent* parent);

};

#endif /* IRAnnotationWorkspace_hpp */
