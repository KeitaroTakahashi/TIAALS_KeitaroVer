//
//  WorkspaceView.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#ifndef WorkspaceView_hpp
#define WorkspaceView_hpp

#include "IRStrComponent.hpp"
#include "WorkspaceWorkspace.hpp"

class WorkspaceView : public Component,
public IRStrComponent,
public VideoAnnotaterDelegate,
public ChangeListener,
private IRWorkspaceComponent::Listener
{
public:
    WorkspaceView(IRStr* str, VideoAnnotaterBase* base);
    ~WorkspaceView();
    // ==================================================
    void setVideoLength(double length);
    void setPlayPosition(double pos);
    // ==================================================
    // ---------------------------------------------
    void nothingSelected() override;
    std::function<void()> nothingSelectedAction = nullptr;
    
    void nodeObjectGetFocused(IRNodeObject* obj) override;
    std::function<void(IRNodeObject*)> nodeObjectGetFocusedAction = nullptr;
    
    WorkspaceWorkspace* getWorkspace() { return this->workspace.get(); }
    
    void setInitialBoundsOfWorkspace(Rectangle<int> initialBounds);
    // ---------------------------------------------
private:
    
    void resized() override;
    void paint(Graphics& g) override;
    
    // ==================================================

    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& w) override;
    void mouseMagnify(const MouseEvent& e, float scaleFactor) override;

    // ==================================================
    
    void changeListenerCallback(ChangeBroadcaster* source) override; // JUCE oriented
    void editModeChanged(IRWorkspaceComponent* changedSpace) override;

    // ==================================================
    std::shared_ptr<WorkspaceWorkspace> workspace;
    


    
};
#endif /* WorkspaceView_hpp */
