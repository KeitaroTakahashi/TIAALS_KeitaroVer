//
//  NodeComponent.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 20/08/2018.
//

#ifndef NodeComponent_hpp
#define NodeComponent_hpp


#include "JuceHeader.h"
#include "json11.hpp"
#include "IRFoundation.h"
#include "IRObjectBase.hpp"
#include "IRObjectResizer.hpp"
#include "IRStrComponent.hpp"
#include "IRSaveLoadSystem.hpp"
#include "IRNodeObjectStatusStruct.h"
//#include "IRLinkFoundation.hpp"
#include "Benchmark.h"
#include "IRResizeSquare2.h"

enum IRNodeComponentSetUp
{
    // resizing
    IREnableResizableFlag,
    IREnableWidthResizingFlag,
    IREnableHeightResizingFlag,
    // selecting
    IREnableSelectableFlag,
    
    //drag
    IREnableMovableFlag,
    
    //copy
    IREnableCopiableFlag,
    
    //delete
    IREnableDeletableFlag,
    
    IRNodeComponentSetUpUndefined
};


enum IRNodeComponentStatus
{
    EditModeStatus, // global status for workspace
    LinkModeStatus,

    LinkedStatus,
    
    SelectableStatus,
    CopiableStatus,
    DeletableStatus,
    MovableStatus,

    ResizableStatus,
    HeightResizableStatus,
    WidthResizableStatus,
    //WillResizeStatus,
    //HasResizedStatus,
    
    IRNodeComponentStatusUndefined
};

// ===========================================================================
// IRNodeComponent
// fundamental system of the IRNodeObject
// ===========================================================================

class IRNodeComponent : //public Component,
                        public IRObjectBase,
                        public IRObjectResizer,
                        public IRStrComponent,
                        public ChangeBroadcaster,
                        public ChangeListener
{
public:
    IRNodeComponent(Component *parent,
                    String name,
                    IRStr* str,
                    IRBoundType boundType);
    ~IRNodeComponent();
    
    // ==================================================

public:

    void setPreferenceWindow(PreferenceWindow* preferenceWindow);
    PreferenceWindow* getPreferenceWindow();
    // ==================================================
    // paint
    virtual void paint(Graphics& g) override;
    // ==================================================

    // managing child components binded on the NodeObject
    // this method operates following
    // # addMouseListner -> status changed by Edit mode of workspace
    // # setInterceptsMouseClicks -> status changed by Edit mode of workspace
    void childComponentManager(Component* comp);
    // ==================================================

    // Audio Source Management
    // Use addAudioComponent() to add any AudioSource made in the NodeObject
    // This method adds a given AudioSource to a mixer which connects to the global mixer to the audio output.
    void addAudioComponent(AudioSource *source);
    void removeAudioComponent(AudioSource *source);
    // Workspace uses this method to get AudioSources added in this NodeObject
    MixerAudioSource* getAudioSource() const;
    // check if any AudioSources are added in this NodeObject.
    bool isContainAudioSource() const;
    
    // ==================================================

    // interaction
    // # these JUCE oriented methods are not intended to be overriden in the IRNodeObject
    // # override mouseXXXEvent() methods instead.
private:
    void mouseDown(const MouseEvent& e) override; // JUCE oriented
    void mouseMove(const MouseEvent& e) override; // JUCE oriented
    void mouseUp(const MouseEvent& e)override; // JUCE oriented
    void mouseDoubleClick(const MouseEvent& e) override; // JUCE oriented
    void mouseDrag(const MouseEvent& e) override; // JUCE oriented
    void mouseEnter(const MouseEvent& e) override;
    void mouseExit(const MouseEvent& e) override;
    void mouseMagnify(const MouseEvent& e, float scaleFactor) override;

public:
    
    virtual void mouseUpCompleted(const MouseEvent& e) {};
    // # controlling Node Object
    void mouseDownNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
    void mouseMoveNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
    void mouseDoubleClickNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
    void mouseUpNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes
    void mouseDragNodeEvent(const MouseEvent& e); // make another method to avoid spaghetti codes


    // resizing method
    // this is virtual method so that you can adjust its behavior to your NodeObject
    virtual void resizeThisComponentEvent(const MouseEvent& e) override;

    juce::Point<float> getResizingArea() const;
    void setResizingArea(juce::Point<float> area);

    // ===========================================================================
    // Events for override
    // # add any codes here
    // ===========================================================================
    
    virtual void mouseDownEvent(const MouseEvent& e);
    virtual void mouseMoveEvent(const MouseEvent& e);
    virtual void mouseDoubleClickEvent(const MouseEvent& e);
    virtual void mouseUpEvent(const MouseEvent& e);
    virtual void mouseDragEvent(const MouseEvent& e);
    
    virtual void mouseEnterEvent(const MouseEvent& e);
    virtual void mouseExitEvent(const MouseEvent& e);
    virtual void mouseMagnifyEvent(const MouseEvent& e, float scaleFactor);

    void moveThisComponentEvent(const MouseEvent& e); // process of moving this Component
    
    // ===========================================================================
    // CALL BACK FUNCTIONS
    // to inform any changes to the registered object
    // advanced call back functions should be written in the IRNodeObject class not here.
    // ===========================================================================
    // change status call back for its childs class
    virtual void statusChangedWrapper(IRNodeComponentStatus status);
    // this method is used as a override function
    virtual void statusChangedCallback(IRNodeComponentStatus status);
    // callback informing
    std::function<void(IRNodeComponentStatus)> statusChangeCompleted;
    
    //called when this object is focused which means this is clicked.
    virtual void thisObjectGetFocused() {};
    
    // when file manager of this Object is updated, then all objects of IRUIFoundation
    // will share the file manger automatically.
    void updateFileManager(IRFileManager& fileManager);
    // callback informing fileManager changes
    std::function<void(IRFileManager*)> fileManagerUpdated;
    IRFileManager* getFileManager() { return FILEMANAGER; }

    void showThisObject(bool flag);
    // ---------------------------------------------

    // return a flag shows whether this Component is being selected or not. Default is false.
    bool isSelected() const; // FD - THIS HAS NO IMPLEMENTATION
    void setSelected(bool flag);
    virtual void selectedChangeEvent() {}; // for IRNodeObject
    // return a flag shows whether the belonging workspace is on edit mode or not.
    bool isEditMode() const;
    virtual void editModeChangedEvent() {}; // for IRNodeObject
    
    // if edit mode is true, this object does not receive any Mouse/Keyboard events
    // if false, this object receive Mouse/Keyboard events
    void setEditMode(bool flag);
    
    bool isCopied() const;
    bool isCopiable() const;
    
    bool isMouseListenerFlag() const;
    void setMouseListenerFlag(bool flag);
    
    
    // activate
    bool isActive() const { return this->isActiveFlag; }
    void setActive(bool active);
    
    //hide and show
    void hide(bool flag);

    //unique ID
    void setUniqueID(String id);
    void setUniqueID(std::string id);

    String getUniqueID() const;

public:
    
    // ==================================================

    // called when this object is moved to Front of all other objects
    virtual void moveToFrontEvent(bool registerZindex) {}
    virtual void moveToBackEvent() {}
public:
    void bringToFront(bool registerZIndex = true);
    void bringToBack();

    // ==================================================
    // ### ANNOTATION ### //
    
    // in annotation mdoe, you first need to give a resolution of the media where this object is binded.
    // the bounds of this object is calculated according to the ratio ralative to the resolution and the actual size of the media object.
public:
    void setMediaResolution(int w, int h);
    void setMediaObjectSize(int w, int h);
    juce::Point<int> getMediaResolution() const { return this->mediaResolution; }
    juce::Point<float> getResolutionRatioToMedia() const { return this->resolutionRatioToMedia; }
private:
    juce::Point<int> mediaResolution;
    juce::Point<int> mediaObjectSize;
    juce::Point<float> resolutionRatioToMedia;
    // ===========================================================================
public:
    
    // object menu appreas by ctl click
    std::unique_ptr<PopupMenu> menu;
    // system defined popup menu events
    void defaultPopupMenuEvents();
    // user defined popup menu events
    virtual void popupMenuEvents();
    
    // object name 
    String name;

    // parent
    Component* parent = nullptr;
    
    // ============================================================
    // ==================================================
    // for algorithm
    
    // sorting...
    int sortIndex = 0;

protected:
        UserSettingStr *USERSETTING;
        IR::IRColours *SYSTEMCOLOUR;
        IRIconBank    *ICONBANK;
        IRFileManager *FILEMANAGER;
    
    
    // ============================================================
    // IRNodeObject ONLY
protected:
    virtual void ObjectPositionChanged4IRNodeObject(int x, int y) {}
    virtual void ObjectBoundsChanged4IRNodeObject(Rectangle<int> bounds) {}
    // ============================================================

private:
    
    void aboutToMoveAction() override;
    
    
    // unique id to identify this object
    String uniqueID;
    
    // save data
    t_json saveData;
    
    // mixer for audio
    std::shared_ptr<MixerAudioSource> mixer;
    // if this object contains any AudioSource
    bool containAudioSourceFlag = false;
    
   
    
    // Object appearance setup
    /*
    float minWidth = 10;
    float minHeight = 10;
    
    float maxWidth = 3000;
    float maxHeight = 3000;
    */
    
    // for resize event
    float previousWidth = 0;
    float previousHeight = 0;
    float previousX = 0;
    float previousY = 0;
    
    IRResizeSquare2::MovableDirection resizeDirection = IRResizeSquare2::MovableDirection::None;

    // Interaction
    //ComponentBoundsConstrainer constrainer;
    bool draggingFlag = false;
    
protected:
    
    virtual void resizingStartAction(){};
    virtual void resizingAction() {};
    virtual void resizingCompletedAction(){};
private:
 
    void setResizingStartFunc() override;
    void setResizingCompletedFunc() override;
    
    //copy related flag
    bool isCopiableFlag = true;
    bool copiedFlag = false;
    
    bool isDeletableFlag = true;
    
    bool isSelectable = true;
    bool selectedFlag = false;
    
    bool mouseListenerFlag = false;

    juce::Point<float> resizingArea;
    
    Rectangle<float> initialBounds;
    
    // default activate.
    // when deactivate, this object is hidden by moving to bihind the workspace (this is how to avoid using setVisible() causing latency)
    // used for annotater
    bool isActiveFlag = true;

    // =======================================================
    // INITIAL BOUNDS used for fixing the position and size of this object relative to the workspace
    // =======================================================

private:
    void resizingSquareDraggedAction(MouseEvent e) override;

private:
    
    // global mode
    bool editModeFlag = true;
    PreferenceWindow* preferenceWindow;

        
    Rectangle<float> relativeBoundsToParent;
    
    // for save data, Corresponding to the all parameters in ArrangeController
    IRNodeObjectStatusStr statusStr;
public:
    IRNodeObjectStatusStr* getStatusStr() { return &this->statusStr; }

    // ==================================================
    
protected:
    virtual void changeListenerCallback (ChangeBroadcaster* source) override {}


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRNodeComponent)
};



#endif /* NodeComponent_hpp */




