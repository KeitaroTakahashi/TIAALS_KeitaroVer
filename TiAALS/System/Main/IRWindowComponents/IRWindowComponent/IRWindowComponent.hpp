//
//  IRWindowComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#ifndef IRWindowComponent_hpp
#define IRWindowComponent_hpp

#include "IRMasterStr.h"
#include "IRTitleBar.hpp"
#include "IRLeftBar.hpp"
#include "IRRightBar.hpp"
#include "IRMainSpace.hpp"
#include "IRSaveLoadSystem.hpp"
#include "IRProjectOwnerBase.h"
#include "json11.hpp"

class IRWindowComponent : public IRProjectOwnerBase,
public ChangeListener,
public KeyListener,
private IRMainSpace::Listener
{
public:
    IRWindowComponent(String projectName,
                      Rectangle<int> frameRect);
    ~IRWindowComponent();
    
    // ==================================================
    
    void paint(Graphics& g) override;
    void resized() override;
    void setComponentsHeight(int barHeight, int mainHeight);
    void initializeUI();
    // ==================================================
    // MOUSE EVENT
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    void mouseDown(const MouseEvent& e)override;
    void mouseMove(const MouseEvent& e)override;

    // ==================================================
public:
    void openProject();
    void closeProject(DocumentWindow* closingWindow);
    void createNewProject();
    void loadProjectFromSavedData(t_json saveData);
    void loadArrangeControllerSaveData(IRNodeObject* obj, t_json arrangeCtl);
    // ----- save action
    void saveProject();
    void saveAsProject();
    
    void OpenDialogToSaveProject();
    json11::Json saveAction(String projectPath, String projectTitle);
    String projectPath;
    String projectTitle;
    void setProjectTitle(String title);
    // -----
    
    // ==================================================
    // AudioApp Component
    AudioSource& getMixer() { return this->mixer.getAudioSource(); }
    
    // ==================================================
    
    //void updateWorkspaceScreenshot(IRHeavyWeightComponent* component, int index);
    //void exportScreenshotCompletedAction();
    // ==================================================
    // IRWorkspace
    void createNewWorkspace();
    void createNewWorkspace(int sortIndex);

    //std::vector<IRWorkspace* > getWorkspaces() const { return this->workspaces; }
    //IRWorkspace* getTopWorkspace() const { return this->topWorkspace; }
    
    bool isEditMode() const { return this->isEditModeFlag; }
    void setEditMode(bool flag);
    
    // ==================================================
    // for the window size change
    juce::Point<int> pos;
    juce::Point<int> currentPos;
    juce::Point<int> prevPos;
    
    // ==================================================
    // to inform IRProjectWIndow and IRiMaSMainComponent the behavior of the project
    std::function<void(juce::Point<int>)> windowMoveAction;
    std::function<void()> closeProjectCallback;
    std::function<void()> newProjectCallback;
    std::function<void()> openProjectCallback;
    std::function<void()> exportCallback;

    bool isResizable = false;
    int resizableMargin = 20;
    
private:
    // ==================================================
    // SYSTEM
    void initialize();
    void createComponents();
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    // SAVE AND LOAD
    IRSaveLoadSystem saveLoadClass;
    json11::Json saveData;
    
    //AudioAppComponent
    AudioEngine mixer;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;
    
    
    // AudioAppComponent
    void audioSetup();
    void closeAudioSetup();
    
    // ==================================================
    // PROJECT BUTTON ACTION
    void closeButtonClicked();
    void closeProject();
    void titleDoubleClicked();
    
    void editModeButtonClicked();
    
    void newSlideButtonClicked();
    void newProjectButtonClicked();
    void saveButtonClicked();
    void saveasButtonClicked();
    void openButtonClicked();
    void exportButtonClicked();
    
    void GridLabelChanged(int val);
    void GuideLabelChanged(int val);

    
    // ==================================================

    // CREATE COMPONENTS
    void createBarComponent();
    void createLeftComponent();
    
    // called from IRLeftBar
    void workspaceSelected(IRWorkspace* space);
    void deleteWorkSpace(IRWorkspace* space);
    //initialize after loading savedata
    void initProjectAfterLoading();
    
    void exportTopWorkspaceToImage();
    // ==================================================

    // Key Event
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override;
    void modifierKeysChanged(const ModifierKeys &mod) override;

    bool isShiftPressed = false;
    bool isCommandPressed = false;
    bool isControlPressed = false;
    bool isAltPressed = false;
    bool isOptionPressed = false;
    
    void DeleteKeyPressed();
    void CommandEPressed();
    void CommandAPressed();
    void CommandSPressed(); // save
    
    void giveKeyFocusOnTopWorkspace();
    
    bool CommandShiftNumber(const KeyPress& key);
    
    // ==================================================
   
    
    // ==================================================
    // Project
    String projectName;
    Rectangle<int> frameRect;
    
    std::shared_ptr<IRMasterStr> ir_str;
    
    std::shared_ptr<IRIconBank> iconBank;

    std::shared_ptr<IRMainSpace> mainSpace;
    std::shared_ptr<IRTitleBar> bar;
    std::shared_ptr<IRLeftBar> leftBar;
    std::shared_ptr<IRRightBar> rightBar;
    
    //IRMainSpace Listener
    void nodeObjectSelectionChange(IRNodeObject* obj) override;
    void nodeObjectGetFocused(IRNodeObject* obj) override;
    void nothingSelected() override;
    void newWorkspaceCreated(IRWorkspace* space) override;
    void workspaceEditModeChanged(IRWorkspace* changedSpace) override;
    
    // ==================================================

    void updateAppearance() override;

    juce::Point<int> previousSize;
    // ==================================================

    bool isEditModeFlag = true;
    
    // ==================================================
    
    // store window size before changing it.
    juce::Point<int> prevSize;
    // ==================================================
   
    // ==================================================

    //IRObjectFactory2& factory = singleton<IRObjectFactory2>::get_instance();

    // ==================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRWindowComponent)
    
};
#endif /* IRWindowComponent_hpp */
