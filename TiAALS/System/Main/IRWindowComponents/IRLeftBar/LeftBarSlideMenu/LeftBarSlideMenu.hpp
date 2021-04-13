//
//  LeftBarSlideMenu.hpp
//  IRiMaS
//
//  Created by Keitaro on 17/09/2019.
//

#ifndef LeftBarSlideMenu_hpp
#define LeftBarSlideMenu_hpp

#include "IRViewPort.hpp"
#include "SlideMenu.hpp"
#include "IRStrComponent.hpp"

class LeftBarSlideMenu : public IRViewPort,
public ChangeBroadcaster
{
public:
    LeftBarSlideMenu(IRStr* str);
    ~LeftBarSlideMenu();
    //==================================================

    void paint(Graphics& g) override;
    void resized() override;
    //==================================================
    void addNewWorkspaceSlide(IRWorkspace* space);
    //==================================================
    std::function<void(IRWorkspace*)> workspaceSelectedCallback;
    std::function<void(IRWorkspace*)> workspaceDeleteCallback;


    //==================================================
    void deleteSelectedWorkspaceSlide();
    
    void moveToLowerSlide();
    void moveToHigherSlide();
    //==================================================
    
    IRWorkspaceSlide* getSelectedSlide();
    
    //==================================================
    // update all workspace thumbnails regardless of their updated status.
    bool reloadThumbnails();

private:
    // callback from SlideMenu
    void slideMenuUpdatedAction();
    void slideHasSelectedAction(IRWorkspaceSlide* slide);
    
    void visibleAreaChangedAction(const Rectangle<int> &newVisibleArea) override;
    //==================================================

    class Component4ViewPort : public Component
    {
    public:
        Component4ViewPort(Component* main) : main(main)
        {
            addAndMakeVisible(main);
        }
        
        ~Component4ViewPort() {}
        
        void resized() override
        {
            this->main->setBounds(0, 0, getWidth(), getHeight());
        }
        
        
    private:
        Component* main;
        
    };
    
    //==================================================

    std::shared_ptr<Component4ViewPort> viewPort;
    
    std::shared_ptr<SlideMenu> slideMenu;
    //==================================================


    
    //==================================================
    int buttomMargin = 50;
    TextButton addNewSlideButton;
    TextButton deleteSlideButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeftBarSlideMenu)

};

#endif /* LeftBarSlideMenu_hpp */
