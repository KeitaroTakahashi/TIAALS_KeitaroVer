//
//  SlideMenu.hpp
//  IRiMaS
//
//  Created by Keitaro on 17/09/2019.
//

#ifndef SlideMenu_hpp
#define SlideMenu_hpp

#include "IRWorkspaceSlide.hpp"

class SlideMenu : public Component,
public IRStrComponent
{
public:
    SlideMenu(IRStr* str);
    ~SlideMenu();
    // ==================================================

    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================

    void addSlide(IRWorkspace* space);
    void slideSelectedAction(IRWorkspaceSlide* slide);
    void slideSwitchedAction(IRWorkspaceSlide* slide);
    
    void moveToLowerSlide();
    void moveToHigherSlide();
    // ==================================================
    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    // ==================================================

    void addNewWorkspaceSlide(IRWorkspace* space);
    IRWorkspace* deleteSelectedWorkspaceSlide();
    // ==================================================
    
    void moveSelectedSlide(const MouseEvent& e);
    bool isSlideMovedToItsNeighbor(IRWorkspaceSlide* slide);
    // ==================================================

    std::function<void()> slideMenuUpdated;
    std::function<void(IRWorkspaceSlide*)> slideHasSelected;

    
    // ==================================================
    IRWorkspaceSlide* getSelectedSlide();
    
    
    // ==================================================
    // reload all thumbnails regardless of the updated status
    bool reloadThumbnails();
    

private:
    // ==================================================

    std::vector<IRWorkspaceSlide* > slides;
    IRWorkspaceSlide* selectedSlide;
    // ==================================================
    void updateSpace();
    // ==================================================
    juce::Point<int> mouseDownPos;
    juce::Point<int> previousMousePos;
    juce::Point<int> mouseDownWithinTarget;
    // ==================================================

    int yMargin = 10;
    int xMargin = 10;
    // ==================================================

    int sceneHeight = 60;
    int itemHeight = 80;
    
    // ==================================================
    enum slideSwitchStatus
    {
        previous,
        next,
        none
    };
    slideSwitchStatus yHittest(Rectangle<int>a, Rectangle<int> b);
    
    void sortByIndex();
    // ==================================================
    

   

};


#endif /* SlideMenu_hpp */
