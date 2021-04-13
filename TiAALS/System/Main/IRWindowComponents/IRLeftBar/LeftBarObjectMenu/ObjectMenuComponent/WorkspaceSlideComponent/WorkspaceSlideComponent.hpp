//
//  WorkspaceSlideComponent.hpp
//  IRIMAS2020July - App
//
//  Created by Keitaro on 14/09/2020.
//

#ifndef WorkspaceSlideComponent_hpp
#define WorkspaceSlideComponent_hpp

#include "ObjectMenuComponent.hpp"
#include "LeftBarSlideMenu.hpp"
#include "KeAnimationComponent.h"
#include "IRThread.h"


class WorkspaceSlideComponent :
public ObjectMenuComponent,
private KeAnimationComponent,
private IRThread
{
public:
    WorkspaceSlideComponent(IRStr* str,Rectangle<int> frameRect);
    ~WorkspaceSlideComponent();
    // ==================================================
    
    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================
    
    void addNewWorkspaceSlide(IRWorkspace* space);

    // ==================================================
    
    void updateWorkspaceThumbnail();
    
    void createThumbnail();
    
    // ==================================================

    std::function<void(IRWorkspace*)> workspaceSelectedCallback;
    std::function<void(IRWorkspace*)> workspaceDeleteCallback;

private:
    // ==================================================
    
    void itemSelected(IRObjectFactory2::t_object* obj) override;
    void itemReleased(IRObjectFactory2::t_object* obj) override;
    
    // delete selected slide
    void menuCtlButtonClicked() override;
    
    // ==================================================
    
    std::shared_ptr<LeftBarSlideMenu> slideMenu;
    
    void workspaceSelectedAction(IRWorkspace* space);
    void workspaceDeleteAction(IRWorkspace* space);

    // ==================================================
    // thread
    
    void task() override;

    uint32 startTime;
    int threadStopDuration = 500;
    
    // use animation to stop thread
    void updateAnimationFrame() override;
    bool completedFlag = false;

    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WorkspaceSlideComponent)
    
};
#endif /* WorkspaceSlideComponent_hpp */
