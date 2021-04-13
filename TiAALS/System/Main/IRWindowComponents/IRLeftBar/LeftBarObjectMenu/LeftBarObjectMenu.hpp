//
//  LeftBarObjectMenu.hpp
//  IRiMaS
//
//  Created by Keitaro on 10/08/2019.
//

#ifndef LeftBarObjectMenu_hpp
#define LeftBarObjectMenu_hpp

#include "WorkspaceSlideComponent.hpp"
#include "TextMenuComponent.hpp"
#include "ImageMenuComponent.hpp"
#include "AudioMenuComponent.hpp"
#include "ChartMenuComponent.hpp"
#include "PlayerMenuComponent.hpp"
#include "ObjectsMenuComponent.hpp"
#include "InspectorMenuComponent.hpp"
#include "PreferenceMenuComponent.hpp"

#include "IRIconBank.hpp"
#include "ColourLib.h"
#include "IRImageButton.hpp"
#include "KeAnimationComponent.h"
#include "IRNodeObjectType.h"
#include "ObjectMenuIconArea.h"
#include "ObjectMenuSpaceArea.h"


class LeftBarObjectMenu : public Component,
public IRStrComponent,
public ChangeBroadcaster
{
public:
    
    LeftBarObjectMenu(IRStr* str, int buttonSize, int topMarge, int leftMarge, int yMarge, int menuSpace, int preferenceMenuSpace, int buttomSpace, Component* parent);
    ~LeftBarObjectMenu();
    
    // ==================================================

    void resized() override;
    void paint(Graphics& g) override;
    void paintSelectedItem(Graphics& g);
    // ==================================================

    void addButtons();
    void showExtraMenu(objectCategory type);
    
    objectCategory getSelectedButtonType() const { return this->selectedButtonType; }
    void resetSelection() { this->selectedButtonType = NONE; repaint(); }
    // ==================================================

    ObjectMenuComponent* getCurrentMenuComponent() { return this->currentMenu; }
    
    // ==================================================
    void toNavigatorAction();
    void toObjectMenuAction();
    
    void addNewWorkspaceSlide(IRWorkspace* space);
    
    std::function<void(IRWorkspace*)> workspaceSelectedCallback;
    std::function<void(IRWorkspace*)> workspaceDeleteCallback;



    // ==================================================

    bool isMenuOpened() const { return this->isOpened; }
    void setMenuOpened(bool flag) { this->isOpened = flag; }
    
    IRImageButton& getButtonFromType();
   

    // ==================================================
    void bindObjectMenuOnParent(ObjectMenuComponent* obj);
    void closeObjectMenu();
    
private:
    // ==================================================
    void createButton(IRImageButton* button, IRIconBank::IRIconImage img);
        
    void replaceCurrentMenu(ObjectMenuComponent* obj);
    
    void createObjectMenuAreaAndShow(ObjectMenuComponent* obj);
    
    void workspaceSelectedAction(IRWorkspace* space);
    
    void workspaceDeleteAction(IRWorkspace* space);

    void manageTemporalPresentationMode();
    // ==================================================
    
    void workspaceSlideAction();
    void textAction();
    void imageAction();
    void audioAction();
    void chartAction();
    void playerAction();
    void objectAction();
    
    void inspectorAction();
    void preferenceAction();
    
    // ==================================================
    int buttonSize = 20;
    objectCategory selectedButtonType = NONE;
    // ==================================================

    Label workspaceSlideLabel;
    
    Label textLabel;
    Label imageLabel;
    Label audioLabel;
    Label chartLabel;
    Label playerLabel;
    Label objectLabel;
    Label inspectorLabel;
    Label preferenceLabel;
    
    IRImageButton workspaceSlideButton;
    IRImageButton textButton;
    IRImageButton imageButton;
    IRImageButton audioButton;
    IRImageButton chartButton;
    IRImageButton playerButton;
    IRImageButton objectButton;

    IRImageButton inspectorButton;
    IRImageButton preferenceButton;
    // ==================================================
    std::shared_ptr<WorkspaceSlideComponent> workspaceMenu;
    
    std::shared_ptr<TextMenuComponent> textMenu;
    std::shared_ptr<ImageMenuComponent> imageMenu;
    std::shared_ptr<AudioMenuComponent> audioMenu;
    std::shared_ptr<ChartMenuComponent> chartMenu;
    std::shared_ptr<PlayerMenuComponent> playerMenu;
    std::shared_ptr<ObjectMenuComponent> objectMenu;
    
    std::shared_ptr<InspectorMenuComponent> inspectorMenu;
    std::shared_ptr<PreferenceMenuComponent> preferenceMenu;
    
    ObjectMenuComponent* currentMenu = nullptr;

    std::shared_ptr<ObjectMenuIconArea> objectMenuIconArea;
    std::shared_ptr<ObjectMenuSpaceArea> objectMenuSpaceArea;
    // ==================================================
    // marge
    
    int topMarge = 10;
    int switchSpace = 50;
    int menuSpace = 200;
    int preferenceMenuSpace = 450;
    int buttomSpace = 110;
    
    int yMarge = 5;
    int leftMarge = 10;
    // ==================================================

    bool isOpened = false; // if menu area is visible or not

    // ==================================================
    
    bool objectMenuSpaceAreaBringToFrontFlag = false;
    
    // ==================================================


    Component* parent = nullptr;
    
    Rectangle<int> menuSpaceRect;
    // ==================================================

    IRIconBank& ImageBank = singleton<IRIconBank>::get_instance();
    //IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeftBarObjectMenu)

    
};


#endif /* LeftBarObjectMenu_hpp */
