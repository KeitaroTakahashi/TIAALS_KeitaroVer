//
//  IRWorkspaceComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 18/09/2019.
//

#ifndef IRWorkspaceComponent_hpp
#define IRWorkspaceComponent_hpp


#include <map>
#include "IRStr.h"

#include "IRNodeObject.hpp"
#include "AudioEngine.h"
#include "IRNodeObjectSelector.hpp"
#include "IRSaveLoadSystem.hpp"
#include "KLib.h"
#include "Benchmark.h"
#include "KTextLoader.h"
#include "IRWorkspaceCover.hpp"
#include "IRWorkspaceController.hpp"
#include "ComponentExportToImage.h"

class IRWorkspaceComponent : public Component,
public AudioSource,
public IRComponents,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
public IRNodeObject::Listener,
public KeyListener
{
    
public:
    
    IRWorkspaceComponent(String title,
                         Rectangle<int> draggableMargin,
                         IRStr* str,
                         int index = 0);
    ~IRWorkspaceComponent();
    
    // ==================================================

public:
    
    // paint Graphics called by paint() private method
    virtual void onPaint(Graphics& g) {}
    virtual void onResized() {}
    
    
    void callResize();
    // ==================================================
    
    virtual void copyAllDataToWorkspace(IRWorkspaceComponent* newWorkspace);
    // ==================================================

    bool isDrawGrids() const { return this->isdrawGridsFlag; }
    void enableDrawGrids(bool flag);
    void setGridsBackgroundAlpha(float alpha) { this->gridsBackgroundAlpha = alpha; };
    void setGridInterval(int thinGrid, int thickGrid);
    
    // ==================================================
    void setFixObjectSizeRatio(bool flag, Rectangle<float> initialBounds);
    void setPreviousBounds(Rectangle<float> previousBounds);
    bool isPreviousBoundsAlreadyGiven() const;
    
    // ==================================================
    // delete all objects and initialize all status of the workspace
    void initializeWorkspace();
    
    void copyWorkspace(IRWorkspaceComponent* space);
    
    void copyObjectListAndCreateObjects(Array<IRNodeObject* > list);

    // ==================================================

    void fullScreenMode(bool isFullScreen);
    void setFullScreenMode(bool isFullScreen) { this->isFullScreenModeFlag = isFullScreen; }
    bool isFullScreenMode() const { return this->isFullScreenModeFlag; }
    
    // ==================================================
    // return visiblebounds transformed by AffineTransform method
    Rectangle<int> getTransformedVisibleArea();
    Rectangle<int> getOriginalVisibleArea();
    // ==================================================

    //ASK ACTION
    //if enabled, workspace will ask user's approval before it operates the process.
    void setAskBeforeDeleteObjectByKeyCommand(bool flag, String message);
    void setAskBeforeCopyObjectByKeyCommand(bool flag, String message);
    void setAskBeforePasteObjectByKeyCommand(bool flag, String message);
    void setAskBeforeDuplicateByKeyCommand(bool flag, String message);
    void setPreventCreateObjectByKeyCommand(bool flag, String message);
    // ==================================================

protected:
    bool isFullScreenModeFlag = false;
    
    bool isAskBeforeDeleteObjectByKeyCommand = false;
    bool isAskBeforeCopyObjectByKeyCommand = false;
    bool isAskBeforePasteObjectByKeyCommand = false;
    bool isAskBeforeDuplicateByKeyCommand = false;

    bool isAskBeforeCreateObjectByKeyCommand = false;
    bool isPreventCreateObjectByKeyCommand = false;
    
    String deleteObjectMessage;
    String copyObjectMessage;
    String pasteObjectMessage;
    String duplicateObjectMessage;
    String preventCreateObjectMessage;
private:
    void paint (Graphics& g) override;
    
    void drawShadows(Graphics& g);
   // void drawGrids(Graphics& g);
    
    // ==================================================

    void resized() override;
    void resizeNodeObjectsRelativeToWorkspaceSizeChange();
    
    void setBounds(Rectangle<int> rectangle) { Component::setBounds(rectangle); }
    void setBounds(int x, int y, int w, int h) { Component::setBounds(x,y,w,h); }

    void zoom(const MouseEvent& e, float zoomFactor);
    void zoomBasedOn(Rectangle<int>baseBound);
    
    void zoomByAffineTransform(const MouseEvent& e, float zoomFactor);
    void zoomByTraditionalWay(const MouseEvent& e, float zoomFactor);
    
    Point<int> offsetPos;
    Rectangle<int>offsetBounds;
    // ==================================================

    String getTitle() { return this->title; }
    
    // interaction
    void mouseDown(const MouseEvent& e) override; // JUCE oriented
    void mouseMove(const MouseEvent& e) override; // JUCE oriented
    void mouseUp(const MouseEvent& e)override; // JUCE oriented
    void mouseDrag(const MouseEvent& e) override; // JUCE oriented
    void mouseDoubleClick(const MouseEvent& e) override; // JUCE oriented
    //void mouseMagnify(const MouseEvent& e, float scaleFactor) override; // JUCE oriented
    void modifierKeysChanged(const ModifierKeys &mod) override; // JUCE oriented
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override; // JUCE oriented
    
    void commandCAction();
    void commandVAction();
    void commandDAction();
    void commandDeleteAction();
    
    
    virtual void command1Pressed();
    virtual void command2Pressed();
    virtual void command3Pressed();
    virtual void command4Pressed() {}
    virtual void command5Pressed() {}
    virtual void command6Pressed() {}
    virtual void command7Pressed() {}
    virtual void command8Pressed() {}
    virtual void command9Pressed() {}

    
    
    
public:
    
    void setMouseMagnify(const MouseEvent& e, float scaleFactor);
    void setMouseWheelMove(const MouseEvent& e, const MouseWheelDetails& w);
    
    void registerKeyListener(KeyListener* key);
    void registerMouseListener(MouseListener* mouse);
    
    virtual void IRChangeListenerCallback(ChangeBroadcaster* source) {}
    
private:
    //Listener
    void changeListenerCallback(ChangeBroadcaster* source) override; // JUCE oriented
    
    // AudioAppComponent
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    virtual void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    virtual void releaseResources() override;
    
    // ==================================================
    // APPEARANCE
public:
    void setBackgroundColour(Colour colour);
private:
    Colour backgroundColour = Colours::white;
public:

    AudioSource& getMixer();
    
    // IRNodeObject Listener
    void dragoutNodeObjectFromParent(IRNodeObject* obj) override;
    void dropoutNodeObjectFromParent(IRNodeObject* obj) override;
    void editModeChangedInNodeObject(bool editMode) override;
    
    void saveProject() override;
    void saveAsProject() override;
    void closeProject() override;
    void createNewProject() override;
    void openProject() override;
    void openFileInspecter() override;
    //void openPreferenceWindow() override;
    
    // get to know when NodeObject is modified e.g. loading new file.
    
    // use nodeObjectModifiedAction for child class
    void nodeObjectModifiedNotification(IRNodeObject* obj) override;
    
    void nodeObjectSelectionChange(IRNodeObject* obj) override;
    void nodeObjectGetFocused(IRNodeObject* obj) override;
    void nodeObjectMoveToFront(IRNodeObject* obj) override;
    void nodeObjectMoveToBack(IRNodeObject* obj) override;
    
    void nodeObjectWantsDeleted(IRNodeObject* obj) override;
    void reorderZIndex() override;

    // object control
    void copySelectedObjects();
    void pasteSelectedObjects();
    void duplicateSelectedObjects();
    void deleteSelectedObjects();
    
    void deselectAllObjects();
protected:
    virtual void nodeObjectModifiedAction(IRNodeObject* obj) {};

    
public:

    // ==================================================

    // object management
    void createObject(IRNodeObject* obj, bool shouldSort = true);
    // void createObject(std::string objName);
    void copyObject(IRNodeObject *obj, bool clearCopied);
    void pasteObject(IRNodeObject *obj, bool addToSelected);
    void duplicateObject(IRNodeObject *obj);
    void deleteObject(IRNodeObject *obj);
    void deleteAllObjects();

    // ==================================================
 

    // ==================================================

    //resizing
    void setResizing(bool flag) { this->isResizingFlag = flag; }
    bool isResizing() const { return this->isResizingFlag; }
    
    // should be called before resized
    void setDraggableMarginWithInThisComponent();
    void setDraggableMargin(Rectangle<int> newMargin);
    void setMovableMargin(Rectangle<int> newMargin);
    void setCenterMargin(Rectangle<int> newMargin);
    
private:
    // original bounds which is a fundamental bounds used for zoom
    void setOriginalBounds(Rectangle<int> originalBounds);
    
public:
    // ZOOM ratio
    //  setZoomRatio updates zoom ratio and also call adJustObjectsToZoomRatio
    
    void adJustObjectsToZoomRatio();
    void adJustObjectsToWHZoomRatio();
    // direction forward = true or backward = false
    // backward is set for the case that objects are sticked on the workspace
    void adJustObjectsDirection(bool direction = true);
    
    float getZoomRatio() const { return this->zoomRatio; }
    void setZoomRatio(float zoomRatio);
    void setZoomRatio(float x, float y, float zoomRatio);
    // zoom only width, if height = 0 then keeps the previous height
    void setWidthZoomRatio(float zoomRatio, float height = 0);

    //void setExpandRatio(float expandRatio);
    
    void setZoomable(bool width, bool height);
    void setZoomableByMouseWheel(bool flag);

    void setWidthZoomableTraditionalWay(bool w);
    bool isWidthZoomableTraditionalWay() const { return this->widthZoomableTraditionalWay; }

    // ==================================================

    // ==================================================

    // save load
    json11::Json makeSaveDataOfThis();
    // if you use this method in your nodeobject using IRWorkspaceComponent, then
    // desugn loadThisFromSaveData by yourselves. Refer to IRAnnotationW
    virtual void loadThisFromSaveData(json11::Json saveData);
    // ==================================================

    //flag
    bool isEditMode() const;
    void setEditMode(bool flag, bool notification = false);
    virtual void editModeChangedAction() {}
    
    bool isActive() const { return this->isActiveFlag; }
    void setActive(bool flag);

    // ==================================================

    // getter
    Array<IRNodeObject*> getObjectList();
    Image getSnap();
    // ==================================================
    
    
    // ==================================================

    // ==================================================

    //##### Time Code Animation ######
public:
    
    void resetAnimatedObjectList();
    void enableTimeCodeAnimation(bool flag);
    bool isTimeCodeAnimationEnabled() const { return this->timeCodeAnimationEnable; }
    
    void setCurrentTimeCode(float currentTime);
    
    // update animation with already set current Time
    void updateCurrentAnimation();
    // update animation with currentTime
    void updateCurrentAnimation(float currentTime);
    
private:
    bool timeCodeAnimationEnable = false;
    // store objects currently animated by IRNodeObjectAnimation such as VideoAnnotater
    Array<IRNodeObject* > currentlyAnimatedObjects;
    
    void addCurrentlyAnimatedObjectList(IRNodeObject* obj);
    void removeFromCurrentlyAnmatedObjectList(IRNodeObject* obj);
    
    void startAnimated(IRNodeObject* obj);
    void endAnimated(IRNodeObject* obj);
    
    float currentTime = 0;
    // ==================================================
    // ==================================================
public:

    //Listener
    class Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void nodeObjectSelectionChange(IRNodeObject* obj) {};
        virtual void nodeObjectGetFocused(IRNodeObject* obj) {};
        
        virtual void nodeObjectCreated(IRNodeObject* obj) {};
        virtual void nodeObjectCopied(IRNodeObject* obj) {};
        virtual void nodeObjectPasted(IRNodeObject* obj) {};
        virtual void nodeObjectWillDeleted(IRNodeObject* obj) {};

        
        virtual void nothingSelected() {};
        
        virtual void editModeChanged(IRWorkspaceComponent* changedSpace) = 0;
        
        
    };
    
    ListenerList<Listener> listeners;
    
    virtual void addListener(Listener* newListener);
    virtual void removeListener(Listener* listener);
    
    void callNodeObjectSelectionChange(IRNodeObject* obj);
    void callNodeObjectGetFocused(IRNodeObject* obj);
    void callEditModeChanged();
    void callNothingSelected();
    
    void callNodeObjectCreated(IRNodeObject* obj);
    void callNodeObjectCopied(IRNodeObject* obj);
    void callNodeObjectPasted(IRNodeObject* obj);
    void callNodeObjectWillDeleted(IRNodeObject* obj);


    // Callback
    std::function<void()> requestWorkspaceListUpdate;
    std::function<void()> requestNewProject;
    std::function<void()> requestSaveProject;
    std::function<void()> requestSaveAsProject;
    std::function<void()> requestCloseProject;
    std::function<void()> requestOpenProject;
    std::function<void()> requestOpenFileInspecter;
    //std::function<void()> requestOpenPreferenceWindow;

    std::function<void()> notifyEditModeChanged;

    std::function<void(IRNodeObject*)> notifyNodeObjectModification;
    
    

    
private:
    // ==================================================

    String name = "";
    String title = "";
    
    IRStr* ir_str;
    
    Rectangle<int> draggableMargin = Rectangle<int>(0,0,0,0);
    Rectangle<int> movableMargin = Rectangle<int>(0,0,0,0);
    Rectangle<int> centerMargin = Rectangle<int>(0,0,0,0);
    bool hasCenterMargin = false;
    
    Rectangle<float> aspectRatio;
    
    // resizing...
    bool isResizingFlag = false;

    // ==================================================
    //store the original bound size
    Rectangle<float> initialBounds;
    
    void setInitialBounds(Rectangle<float> initialBounds) {
        std::cout << "setInitialBounds\n";
        this->initialBounds = initialBounds; }
    
public:
    Rectangle<float> getInitialBounds() const { return this->initialBounds; }
    Rectangle<int> getOriginalBounds() const { return this->originalBounds; }
    
    Rectangle<int> getVisibleArea() const;
    // ==================================================
private:
   
    float grid_thickness = 1.0;
    float grid_thickness2 = 0.5;
    
    float gridsBackgroundAlpha = 0.1;
    // ==================================================

    // Objects
    Array<IRNodeObject* > objects;
protected:
    Array<IRNodeObject* > getObjects() const { return this->objects; }
private:
    // ==================================================
    // SELECTOR
    std::shared_ptr<IRNodeObjectSelector> selector;
    bool selectorEnableFlag = true;
public:
    void enableSelector(bool flag) { this->selectorEnableFlag = flag; }
    bool isSelectorEnabled() const { return this->selectorEnableFlag; }
    // ==================================================
private:
    Array<IRNodeObject* > copiedObjects;
    
    AudioEngine mixer;
    
    // dummy object for drag drop action
    Array<IRNodeObject* > dummy;
    
    // IRObjectPtr for Global values between objects binded in Workspace
    std::map<String, IRObjectPtr> p_obj;
    
    
    // parent node object has role of fundamental object in the annotation mode
    IRNodeObject* parentNodeObject = nullptr;
    bool hasParentNodeObjectFlag = false;
    void bringParentNodeObjectToFront();
    void bringParentNodeObjectToBack();
public:
    bool hasParentNodeObject() const { return this->hasParentNodeObjectFlag; }
    void setParentNodeObject(IRNodeObject* newParentNodeObject);
    void removeParentNodeObject();
    // ==================================================
private:
    // cover with grids
    //std::shared_ptr<IRWorkspaceCover> cover;
    void createCover();
    void bringCoverToFront();
    void bringCoverToBack();
    void setCoverEditMode(bool editMode);
    
public:
    // grid interval for IRWorkspaceCover
    void setGridValue(int grid);
    // restrict the moving amount of any objects attached on the worksapce
    void setGuidValue(int guid);
    // ==================================================
    
    int getIndex() const { return this->index; }
    void setIndex(int index) { this->index = index; }
private:

    bool isMultiSelectMode = false;
    bool isPointAlreadySelected = false;
    bool isNewSelectedObjectFound = false;
    
    bool isShiftPressed = false;
    bool isCommandPressed = false;
    bool isControlPressed = false;
    bool isAltPressed = false;
    bool isOptionPressed = false;
    
    bool isdrawGridsFlag = false;
    
    bool isTopWorkspaceFlag = false;
    
    int guideValue = 1;
    
    // ==================================================
    // temporal editmode
    bool temporalPresentationMode = false;
    bool previousMode = false;
public:
    
    void enableTemporalPresentationMode();
    void recoverFromTemporarlPresentationMode();
    bool isTemporalPresentationMode() const { return this->temporalPresentationMode; }
    
    void setTopWorkspace(bool flag)
    {
        this->isTopWorkspaceFlag = flag;
        
        //recoverBounds();
        
        setActive(flag);
    }
    bool isTopWorkspace() const { return this->isTopWorkspaceFlag; }
    
    virtual Component* getController() { return this->controller.get(); }
    
    void recoverBounds();
    
    
    // EXPORT AS IMAGE
    void exportThisToPNG();
    
private:
    // ==================================================

    // identify this workspace, this number must be unique among other workspaces at the same level.
    int index = 0;

    juce::Point<int> currentMousePosition {0, 0};
    
    // workspace status
    bool editModeFlag = true;
    
    //resize object position
    bool isFixObjectSizeRatio = true;
    
    // for example, topWorkspace = true
    bool isActiveFlag = false;
    
    Rectangle<float> previousBounds;

    // snapshot
    Image snap;
    // ==================================================
    
    float zoomRatio = 1.0;
    
    AffineTransform previousTransform;
  
    
    bool widthZoomable = true;
    bool heightZoomable = true;
    bool zoomableByMouseWheel = true;
    
    bool widthZoomableTraditionalWay = false;
    
    void wheelByAffineTransform(float newX, float newY);
    void wheelByBounds(float newX, float newY);

    
    Rectangle<int> originalBounds;
    float originalAspect = 1.0; // h / w
    
    float zoomedWidth = 0.0;
    
    // minimum workspace size
    Rectangle<int> minSize;
    // ==================================================
    std::shared_ptr<IRWorkspaceController> controller;
    
    void controllerChanged();
    
    void titleChangedAction();
    void aspectRatioChangedAction();
    
public:
    void setUserDefinedRatio(Rectangle<float> ratio);
    void setBoundsAndCalculateRatio(Rectangle<int> localBounds);
    
    void setMinSize(int w, int h) { this->minSize = Rectangle<int>(0,0,w,h); }

private:
    // Window for the preference
    //PreferenceWindow* preferenceWindow;
    // ==================================================

    // Object list menu
    //ObjectListMenu* objectMenuComponent;
    //std::unique_ptr<ObjectMenuWindow> objMenuwindow;
    // ==================================================

    
    //Z-order of the objects
    std::vector<IRNodeObject* > ObjectZorder;
    void insertObjectAtTopZOrder(IRNodeObject* obj);
    void insertObjectAtEndZOrder(IRNodeObject* obj);
    void removeObjectFromZOrder(IRNodeObject* obj);
    
    // ==================================================

    Image loadImage(String url);
    
// ==================================================

// ==================================================
    //benchmark
    StopWatch bench;
    StopWatch bench2;
    StopWatch bench3;
    StopWatch bench4;

    // ==================================================
    
    float angle = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRWorkspaceComponent)
        
};


#endif /* IRWorkspaceComponent_hpp */
