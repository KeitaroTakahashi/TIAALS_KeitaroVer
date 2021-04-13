//
//  IRNodeObjectWorkspaceManager.hpp
//  IRiMaS
//
//  Created by Keitaro on 12/03/2020.
//

#ifndef IRNodeObjectWorkspaceManager_hpp
#define IRNodeObjectWorkspaceManager_hpp

#include "IRNodeObjectWorkspace.hpp"
#include "IRNodeObject.hpp"

class IRNodeObjectWorkspaceManager :
private IRWorkspaceComponent::Listener
{
public:
    IRNodeObjectWorkspaceManager(IRNodeObject* nodeObject, IRWorkspaceComponent* parentWorkspace, IRStr* str);
    ~IRNodeObjectWorkspaceManager();
    
    void setBounds(Rectangle<int> bounds);
    
    void addWorkspace();
    void removeWorkspace();
    
    void addNodeObject(IRNodeObject* nodeObject);
    
private:
    std::shared_ptr<IRNodeObjectWorkspace> workspace;
    
    IRNodeComponent* nodeObject;
    
    IRWorkspaceComponent* parentWorkspace;
};

#endif /* IRNodeObjectWorkspaceManager_hpp */
