
#ifndef NodeObject_hpp
#define NodeObject_hpp

#include "JuceHeader.h"

#include "IRNodeComponent.hpp"
#include "IRFileManager.hpp"
#include "IRNodeObjectType.h"
#include "IRPreferenceObject.hpp"
#include "IRObjectController.hpp"
#include "IREnclosedObject.hpp"


#include "ObjectArranger.hpp"

class IRNodeObject : public IRNodeComponent
{
    
public:
    // ==================================================

    enum IRNodeObjectStatus
    {
        ORDINARY,
        ENCLOSE
    };
    // ==================================================

    IRNodeObject(Component* parent,
                 String name,
                 IRStr* str,
                 IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRNodeObject();
    // ==================================================

    // something should be painted on the workspace.
    // @param1 Graphics from the workspace
    // @param2 frame rect of the workspace
    virtual void paintOnWorkspace(Graphics& g, Component* workspace) {};
    // paint oparated by parent
    void initialPaintOnWorkspace(Graphics& g, Component* workspace);
    
    // ==================================================

    // use this to initialize nodeObject
    virtual void initialiseSetup(String text, Colour colour){};
    // ==================================================

    IRNodeObject* copyThis(); //copy constructor
    virtual IRNodeObject* copyThisObject(); // called by copyThis() user defeined copy method
    
    
    virtual IRNodeObject* copyContents(IRNodeObject* object); // copy constructor with contents
    virtual IRNodeObject* copyDragDropContents(IRNodeObject* object); // copy draged and dropped contents
    
    // send request to workspace to delete this object
    bool deleteThis();
    // ==================================================

    virtual t_json saveThisToSaveData();
    virtual void loadThisFromSaveData(t_json saveData);
    
    t_json saveAnnotationData();
    // ==================================================
    // Controller
    // to controll position of this project etc.
    void setArrangeController(ArrangeController* controller);
    void copyArrangeController(IRNodeObject* copiedObject);
    virtual void arrangeControllerChangedNotify() {};
    ArrangeController* getArrangeController() { return this->arrangeController; }
    
    t_json getArrangeControllerSaveData();
    // ==================================================

    virtual void IRChangeListenerCallback(ChangeBroadcaster* source);
    // ==================================================


    // mouse events for its child class
    virtual void mouseDownEvent(const MouseEvent& e) override;
    virtual void mouseUpEvent(const MouseEvent& e) override;
    virtual void mouseMoveEvent(const MouseEvent& e) override;
    virtual void mouseDoubleClickEvent(const MouseEvent& e) override;
    virtual void mouseDragEvent(const MouseEvent& e) override;
    
    void mouseUpCompleted(const MouseEvent& e) override;
    // ==================================================
private:
    void resizingStartAction() override;
    void resizingAction() override;
    void resizingCompletedAction() override;

    // ==================================================

    // selected event from IRNodeComponent
private:
    void selectedChangeEvent() override;
    
    void resizedOrMoved() override;
public:
    virtual void selectedChangedAction(bool flag) {}

    void editModeChangedEvent() override;
    //void linkModeChangedEvent() override;
    
    void thisObjectGetFocused() override;
    
    // ==================================================
    void setObjController(IRObjectController* objCtl);
    IRObjectController* getObjController() const { return this->objController; }
    
    // ==================================================
    // move to Front action
    // only modify z order
    void moveThisToFrontZIndex();
    // also update
    void moveToFrontEvent(bool registerZindex) override;
    // only modify z order
    void moveThisToBackIndex();
    // also update
    void moveToBackEvent() override;
    
    // ## ========== Obligatory to implement! ========== ##
    virtual void moveToFrontAction() {}; // for its Child component
    virtual void moveToBackAction() {};
    // ==================================================
    
    // called when this object position is changed
    //virtual void ObjectPositionChanged(int x, int y) override {};
    virtual void ObjectBoundsChanged(Rectangle<int> bounds) override {};
    // ==================================================
    
    // ###### Time Code Anomation ######
    
    //void StatusUpdated() override;
    
    // ==================================================

    // STATUS
    IRNodeObjectStatus getStatus() const { return this->status; }
    void setStatus(IRNodeObjectStatus newStatus);
    
    void transformStatusToOrdinary();
    void transformStatusEnclose();
    void setEncloseMode(bool flag);
    void setEncloseAlreadyDefined(bool flag);
    bool hasEncloseAlreadyDefined() const { return this->hasEncloseObjectAlreadyDefined; }
    IRNodeObjectStatus getEncloseMode() const { return this->getStatus(); }
    void createEnclosedObject();
    void setEncloseColour(Colour colour);
    
    void showEncloseObject(bool flag);
    // ==================================================

    void calcRelativeOrdinaryBounds();
    void calcRelativeEncloseBounds();
    
    void adjustRectangleFloatToAboveZero(Rectangle<float>& bounds);

    // ==================================================

    class Listener
    {
    public:
        virtual ~Listener() {}
        
        //write methods called by IRNodeComponent objects.
        virtual void dragoutNodeObjectFromParent(IRNodeObject* obj) {};
        virtual void dropoutNodeObjectFromParent(IRNodeObject* obj) {};
        
        // save action from IRNodeObject
        virtual void saveProject(){};
        
        virtual void saveAsProject() {};
        
        // close Project
        virtual void closeProject() {};
        
        virtual void openProject() {};
        
        virtual void createNewProject() {};
        
        virtual void openFileInspecter() {};
        virtual void openPreferenceWindow() {};
        
        //object selection
        virtual void nodeObjectSelectionChange(IRNodeObject* obj) {};
        virtual void nodeObjectGetFocused(IRNodeObject* obj) {}
        
        //Front
        virtual void nodeObjectMoveToFront(IRNodeObject* obj) {}
        //Back
        virtual void nodeObjectMoveToBack(IRNodeObject* obj) {}
        
        //dragged in edit mode
        virtual void nodeObjectDragged(IRNodeObject* obj) {}
        virtual void nodeObjectDraggedCompleted(IRNodeObject* obj) {}
        
        virtual void nodeObjectResizingStart(IRNodeObject* obj) {}
        virtual void nodeObjectBeingResized(IRNodeObject* obj) {}
        virtual void nodeObjectResizingCompleted(IRNodeObject* obj) {}

        // notification to IRWorkspace
        virtual void nodeObjectModifiedNotification(IRNodeObject* obj) {};
        
        //inform its parent that edit mode status changed
        virtual void editModeChangedInNodeObject(bool editMode) {};
        
       //inform its position change
        virtual void nodeObjectPositionChanged(IRNodeObject* obj) {};
        
        //inform its start and end time change
        virtual void nodeObjectStartEndTimeChanged(IRNodeObject* obj) {};
        
        //activate changed
        virtual void nodeObjectActivateChanged(IRNodeObject* obj) {};
        //inform any UI changed
        virtual void nodeObjectUIChanged(IRNodeObject* obj) {};
        
        //request workspace to delete this object
        virtual void nodeObjectWantsDeleted(IRNodeObject* obj){};
        
        virtual void nodeObjectWillDeleted(IRNodeObject* obj) {};
        
        // give its IRFileManager when it is given or modified.
        // this is used for IRUIFoundation to receive IRFileManager
        virtual void updateIRFileManager(IRFileManager* fileManager) {};
        
        // add object to a global space in Workspace
        virtual void addObjectGlobal(IRObjectPtr obj, String id) {};
        virtual void getObjectGlobal(IRNodeObject *obj) {};
        
      
        // simply reorganize z-order of objects
        virtual void reorderZIndex() {};

    };
    
    virtual void addListener(Listener* newListener) { this->listeners.add(newListener); }
    virtual void removeListener(Listener* listener) { this->listeners.remove(listener);}
    ListenerList<Listener>& getListenerList() { return this->listeners; }
    
    // ---------------------------------------------------------------------------
    
    std::function<void()> dragoutNodeObjectCompleted;
    std::function<void()> dropoutNodeObjectCompleted;
    std::function<void()> editModeChangedCompleted;
    std::function<void()> linkModeChangedCompleted;

    //std::function<void()> addOBjectGlobalCompleted;
    
    // requests to IRProject
    std::function<void()> saveProjectCompleted;
    std::function<void()> saveAsProjectCompleted;
    std::function<void()> closeProjectCompleted;
    std::function<void()> openProjectCompleted;
    std::function<void()> createNewProjectCompleted;

    //std::function<void()> getObjectGlobalCompleted;
    

    // fire dragoutNodeObjectFromParent() methods in Listener
    void callDragOutNodeObjectFromParent();
    // fire dropoutNodeObjectFromParent() methods in Listener
    void callDropOutNodeObjectFromParent();
    // fire editModeChangedInNodeObject() methods in Listener
    void callEditModeChangedInNodeObject();
    
    // ask IRWorkspace to Recorder objects according to the new ZIndex
    void callReorderZIndex();

    void callNodeObjectPositionChanged();
    
    void callNodeObjectStartEndTimeChanged();
    void callNodeObjectActivateChanged();
    void callNodeObjectUIChanged();

    void callWantDeleteThis();
    
    void callNodeObjectWillDeleted();
    
    void callLinkModeChangedInNodeObject();
    
    // fire addObjectGlobal() method in Listener
    void callAddObjectGlobal(IRObjectPtr obj, String id);
    // fire getObjectGlobal() method in Listener
    IRObjectPtr callGetObjectGlobal(String id);
    // fire saveProject() method in Listener
    void callSaveProject();
    void callSaveAsProject();
    // fire CloseProject() method in Listener
    void callCloseProject();
    void callCreateNewProject();
    void callOpenProject();
    
    void callNodeObjectSelectionChange();
    void callNodeObjectGetFocused();
    
    void callNodeObjectMoveToFront();
    void callNodeObjectMoveToBack();
    
    //call when nodeobject is dragged in edit mode
    void callNodeObjectDragged();
    void callNodeObjectDraggedCompleted();
    
    void callNodeObjectResizingStart();
    void callNodeObjectBeingResized();
    void callNodeObjectResizingCompleted();
    
    void callOpenFileInspecter();
    void callOpenPreferenceWindow();

    
    void notifyNodeObjectModification();
    
    /*
    void callReceiveAudioLink(IRAudio *obj);
    void callReceiveTextLink(IRText *obj);
    void callReceiveImageLink(IRImage* obj);
    void callReceiveDataLink(IRData *obj);
    void callReceiveVideoLink(IRVideo *obj);
     */
    
    void callUpdateIRFileManager(IRFileManager* fileManager);

    // ===========================================================================
        // Global Object
    
    String getGlobalObjectID() const { return this->p_id; }
    void setGlobalObject(IRObjectPtr obj) { this->p_obj = obj; }
    IRObjectPtr getGlobalObject() { return this->p_obj; }
    // ===========================================================================

    // methods for save and load functions. Developers need to define the behavior of objects when save or load project files.
    // otherwise, save data does not contain any information about the object setting but only the objectType and its bounds.
    // The save method must follow the syntax of Json using json11 library.
    
    virtual void saveObjectContents();
    
    virtual void loadObjectContents();
    
    // ============================================================
    
    
    
    

    
    // ============================================================

    
/*
    virtual bool keyPressed (const KeyPress& key,
                     Component* originatingComponent) override
    {
        return true;
    }*/
    
    // ============================================================

    Component* getParent() { return this->parent; }
protected:
    
    Component* parent;
    
private:
    void ObjectPositionChanged4IRNodeObject(int x, int y) override;
    void ObjectBoundsChanged4IRNodeObject(Rectangle<int> bounds) override;

private:
    // ==================================================
    // STATUS //

    IRNodeObjectStatus status = ORDINARY;
    IREnclosedObject enclosedObject;
    void enclosedObjectClickedAction();
    void enclosedObjectClickedInControlMode();
    
    // use this button to go back to WRAP mode.
    std::shared_ptr<EncloseButton> goBackToEncloseButton;
    void goBackToEncloseButtonClicked();
    void createGoBackToEncloseButton(bool createOrDelete);
    void setBoundsGoBackToEncloseButton();
    
    Rectangle<int> ordinaryBounds;
    Rectangle<float> ordinaryBoundsRelative;
    Rectangle<int> encloseBounds;
    Rectangle<float>encloseBoundsRelative;
    
    bool isWorkspaceActiveFlag = false;
public:
    void setWorkspaceActive(bool flag);
    bool isWorkspaceActive() const { return this->isWorkspaceActiveFlag; }
    virtual void workspaceActiveStatusChanged(bool flag) {}
public:
    void setOrdinaryBounds(Rectangle<int> bounds);
    void setEncloseBounds(Rectangle<int> bounds);
    
    // use them when adjusting bounds to relative instead of using absolute bounds
    void adjustOrdinaryBoundsToRelative();
    void adjustEncloseBoundsToRelative();
    
    Rectangle<int> getOrdinaryBounds() const { return this->ordinaryBounds; }
    Rectangle<int> getEncloseBounds() const { return this->encloseBounds; }
private:
    
    // flag to inform if the encloseObject is already created and has encloseBounds.
    bool hasEncloseObjectAlreadyDefined = false;
    // called when the position of this object is changed
    void encloseObjectPositionChangedAction(int x, int y);
    void encloseObjectBoundsChangedAction(Rectangle<int> bounds);

    // ==================================================

    // ObjectController
    IRObjectController* objController = nullptr;
    // Object Arrange Controller//
    ArrangeController* arrangeController = nullptr;
    // called when the position of this object is changed
    void arrangeControllerPositionChangedAction(int x, int y);
    void arrangeControllerBoundsChangedAction(Rectangle<int> bounds);
    void arrangeControllerChangedCallback(ChangeBroadcaster* source);
public:
    void loadArrangeControllerSaveData(t_json arrangeCtl, IRBoundType type = IRBoundType::ABSOLUTE);
private:
    // ==================================================
    // EVENT COMPONENT //
    // for videoAnnotater or Any other objects
    Component* eventComponent = nullptr;
    Component* annotationComponent = nullptr;
public:
    void setEventComponent(Component* event) { this->eventComponent = event; this->hasEventComponentFlag = true; }
    void removeEventComponent() { this->eventComponent = nullptr; this->hasEventComponentFlag = false;}
    bool hasEventComponent() const { return this->hasEventComponentFlag; }
    Component* getEventComponent() { return this->eventComponent; }
    // update event parameters
    void updateEventParam();
    
    // in case this object is used as event
    void setAnnotation(Component* annotation) { this->annotationComponent = annotation; this->hasAnnotationComponentFlag = true; }
    void removeAnnotationComponent() { this->annotationComponent = nullptr; this->hasAnnotationComponentFlag = false; }
    bool hasAnnotationComponent() const { return this->hasAnnotationComponentFlag; }
    Component* getAnnotationComponent() { return this->annotationComponent; }
    
    void updateAnnotationParam();
private:
    bool hasEventComponentFlag = false;
    bool hasAnnotationComponentFlag = false;
    
    // in sec. Annoation time code
    float StartTimeSec = 0.0;
    float EndTimeSec = 0.0;
    // ==================================================
public:
    void setStartTimeSec(float sec, NotificationType notification = dontSendNotification);
    void setEndTimeSec(float sec, NotificationType notification = dontSendNotification);
    float getStartTimeSec() const { return this->StartTimeSec; }
    float getEndTimeSec() const { return this->EndTimeSec; }
    
    // ==================================================
protected:
    // inform system any changes of the parameter of this object
    void paramChanged();
    
private:

    // ==================================================
    // LISTENER //
    ListenerList<Listener> listeners;
    
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    IRObjectPtr p_obj;
    String p_id;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRNodeObject)
};


#endif /* NodeObject_hpp */




