//
//  IRWorkspaceListViewer.h
//  IRIMAS2020July
//
//  Created by Keitaro on 09/08/2020.
//

#ifndef IRWorkspaceListViewer_h
#define IRWorkspaceListViewer_h

#include "IRWorkspace2.hpp"

class IRWorkspaceListViewer : public Component,
public IRStrComponent
{
public:
    IRWorkspaceListViewer(IRStr* str) :
    IRStrComponent(str)
    {
        
    }
    
    ~IRWorkspaceListViewer()
    {
        
    }
    
    void setWorkspaceList(std::vector<IRWorkspace*>* workspaces)
    {
        this->workspaces = workspaces;
    }
    
    void showListView()
    {
        

        for(auto w : *this->workspaces)
        {
            
        }
    }
    
    // =========================
    
private:
    void resized() override
    {
        for(auto w : *this->workspaces)
        {
            
        }
    }
    
    void paint(Graphics &g) override
    {
        
    }
    // =========================
    std::vector<IRWorkspace*>* workspaces;

    // =========================
    // =========================
    // =========================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRWorkspaceListViewer)

};
#endif /* IRWorkspaceListViewer_h */
