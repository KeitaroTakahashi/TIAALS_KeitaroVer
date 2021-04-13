//
//  IRNodeObjectWorkspaceManager.cpp
//  IRiMaS
//
//  Created by Keitaro on 12/03/2020.
//

#include "IRNodeObjectWorkspaceManager.hpp"


IRNodeObjectWorkspaceManager::IRNodeObjectWorkspaceManager(IRNodeObject* nodeObject, IRWorkspaceComponent* parentWorkspace, IRStr* str) :
nodeObject(nodeObject),
parentWorkspace(parentWorkspace)
{
    Rectangle<int> r (0,0,0,0);
    this->workspace.reset(new IRNodeObjectWorkspace("", r, str));
    this->workspace->addListener(this);
    this->workspace->addKeyListener(parentWorkspace);
}

IRNodeObjectWorkspaceManager::~IRNodeObjectWorkspaceManager()
{
    
}

void IRNodeObjectWorkspaceManager::setBounds(Rectangle<int> bounds)
{
    //this->workspace->setOriginalBounds(bounds);
}


void IRNodeObjectWorkspaceManager::addWorkspace()
{
    this->nodeObject->addAndMakeVisible(this->workspace.get());
}

void IRNodeObjectWorkspaceManager::removeWorkspace()
{
    this->nodeObject->removeChildComponent(this->workspace.get());
}

