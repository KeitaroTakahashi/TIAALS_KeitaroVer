//
//  IRSequencerWorkspace.hpp
//  IRiMaS
//
//  Created by Keitaro on 11/05/2020.
//

#ifndef IRSequencerWorkspace_hpp
#define IRSequencerWorkspace_hpp

#include "IRWorkspaceComponent.hpp"

class IRSequencerWorkspace : public IRWorkspaceComponent
{
public:
    IRSequencerWorkspace(IRStr* str);
    ~IRSequencerWorkspace();
};

#endif /* IRSequencerWorkspace_hpp */
