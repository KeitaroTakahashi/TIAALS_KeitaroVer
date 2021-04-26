//
//  WorkspaceView.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#include "WorkspaceView.hpp"


WorkspaceView::WorkspaceView(IRStr* str, VideoAnnotaterBase* base) : IRStrComponent(str),
VideoAnnotaterDelegate(base)
{
    
    Rectangle<int> r (0, 0, 1000, 1000);

    
    this->workspace.reset( new WorkspaceWorkspace("Workspace",
                                                  r,
                                                  str,
                                                  base) );
    this->workspace->addListener(this);
    addAndMakeVisible(this->workspace.get());
}

WorkspaceView::~WorkspaceView()
{
    this->workspace.reset();
}

// ==================================================

void WorkspaceView::changeListenerCallback(ChangeBroadcaster* source)
{
    
}

// ==================================================

void WorkspaceView::resized()
{
    //std::cout <<"WorkspaceView resized " << getWidth() << ", " << getHeight() << std::endl;
    //this->workspace->setUserDefinedRatio(Rectangle<float>(0, 0, (float)getWidth() / 100.0, (float)getHeight() / 100.0));
    //this->workspace->setMinSize(getWidth(), getHeight());
    
    auto b = this->workspace->getOriginalBounds();
    
    if(b.getWidth() == 0)
    {
        b = getLocalBounds();
        setInitialBoundsOfWorkspace(b);
    }
    
    //std::cout <<"WorkspaceView originalBounds " << b.getWidth() << ", " << b.getHeight() << std::endl;

    this->workspace->setMinSize(getWidth(), getHeight());

    float ratioW = (float)getWidth() / b.getWidth();
    std::cout << "ratioW = " << ratioW << std::endl;
    // height adjust
    this->workspace->setWidthZoomRatio(ratioW, getHeight());
}

void WorkspaceView::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.drawText("workspace view", getLocalBounds(), Justification::centred);
}
// ==================================================

void WorkspaceView::setVideoLength(double length)
{
    this->workspace->setVideoLength(length);
}
void WorkspaceView::setPlayPosition(double pos)
{
    this->workspace->setPlayPosition(pos);
}

// ---------------------------------------------

void WorkspaceView::nothingSelected()
{
    if(this->nothingSelectedAction != nullptr)
        this->nothingSelectedAction();
    
}

void WorkspaceView::nodeObjectGetFocused(IRNodeObject* obj)
{
    if(this->nodeObjectGetFocusedAction != nullptr)
        this->nodeObjectGetFocusedAction(obj);
}

void WorkspaceView::editModeChanged(IRWorkspaceComponent* changedSpace)
{
    
}
// ---------------------------------------------

void WorkspaceView::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& w)
{
    this->workspace->setMouseWheelMove(e, w);
}
void WorkspaceView::mouseMagnify(const MouseEvent& e, float scaleFactor)
{
    this->workspace->setMouseMagnify(e, scaleFactor);
}
// ---------------------------------------------

void WorkspaceView::setInitialBoundsOfWorkspace(Rectangle<int> initialBounds)
{
    
    //std::cout << "WorkspaceView::setInitialBoundsOfWorkspace " << initialBounds.getWidth() << ", " << initialBounds.getHeight() << std::endl;
    this->workspace->setUserDefinedRatio(Rectangle<float>(0, 0, (float)getWidth() / 100.0, (float)getHeight() / 100.0));
    this->workspace->setMinSize(getWidth(), getHeight());

}
