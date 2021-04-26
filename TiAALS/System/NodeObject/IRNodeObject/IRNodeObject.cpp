
#include "IRNodeObject.hpp"

IRNodeObject::IRNodeObject(Component* parent,
                           String name,
                           IRStr* str,
                           IRBoundType boundType) :
IRNodeComponent(parent, name, str, boundType)
{
    this->parent = parent;
    
    createEnclosedObject();
    
}


IRNodeObject::~IRNodeObject()
{
    
    //this->enclosedObject.reset();
    //notify any modification
    //notifyNodeObjectModification();
}
// ==================================================


void IRNodeObject::resizedOrMoved()
{
    setBoundsGoBackToEncloseButton();
}

// ==================================================

//copy constructor
IRNodeObject* IRNodeObject::copyThis()
{
    auto obj = copyThisObject();
    obj->copyArrangeController(this);
    
    return obj;
}

IRNodeObject* IRNodeObject::copyThisObject()
{
    
    KLib().showErrorMessage("Oops! This object does not override a virtual function copyThisObject() ! Can not copy! ");
    
    return new IRNodeObject(this->parent, "IRNodeObject", getStr(), getBoundType());
}


// copy constructor with contents
IRNodeObject* IRNodeObject::copyContents(IRNodeObject* object)
{
    return new IRNodeObject(this->parent, "IRNodeObject", getStr(), getBoundType());
}

IRNodeObject* IRNodeObject::copyDragDropContents(IRNodeObject* object)
{
    return new IRNodeObject(this->parent, "IRNodeObject", getStr(), getBoundType());
}

bool IRNodeObject::deleteThis()
{
    callWantDeleteThis();
    
    return true;
}
// ==================================================

t_json IRNodeObject::saveThisToSaveData()
{
    t_json a;
    return a;
}


// load data contents from save data
void IRNodeObject::loadThisFromSaveData(t_json saveData)
{
    
}
// ==================================================
void IRNodeObject::setObjController(IRObjectController* objCtl)
{
    this->objController = objCtl;
    
    if(this->objController->hasArrangeController())
    {
        setArrangeController(this->objController->getArrangeController());
    }
}


void IRNodeObject::setArrangeController(ArrangeController* controller)
{
    this->arrangeController = controller;
    this->arrangeController->addChangeListener(this);
    
    
    //if controlelr has arrangeController, then set wrap colour
    if(getArrangeController() != nullptr)
        getStatusStr()->wrapColour = getArrangeController()->getEncloseColour();
}

void IRNodeObject::copyArrangeController(IRNodeObject* copiedObject)
{
    auto c = copiedObject;
    if(c == nullptr) return;
    
    if(c->getArrangeController() == nullptr) return;
    
    setBoundType(c->getBoundType());
    
    if(c->getBoundType() == IRBoundType::ABSOLUTE)
        setObjectBoundsRelative(c->getObjectBoundsRelative());
    else if(c->getBoundType() == IRBoundType::ABSOLUTE)
        setObjectBounds(c->getBounds());
    
    if(c->getEncloseMode() == 1) setEncloseMode(c->getEncloseMode());
    
    setEncloseColour(c->getArrangeController()->getEncloseColour());
    
    setStartTimeSec(c->getStartTimeSec());
    setEndTimeSec(c->getEndTimeSec());
}


t_json IRNodeObject::getArrangeControllerSaveData()
{
    
    auto s = getStatusStr();
    
    // update relative bounds
    calcRelativeEncloseBounds();
    calcRelativeOrdinaryBounds();
    
    std::string contents = "";

    // ----------
    contents += "{";
    
    contents += "\"boundType\": " + std::to_string(s->boundType) + ", ";
    
  
    contents += "\"encloseBounds\": [" + std::to_string(s->encloseBounds.getX()) +
    ", " + std::to_string(s->encloseBounds.getY()) +
    ", " + std::to_string(s->encloseBounds.getWidth()) +
    ", " + std::to_string(s->encloseBounds.getHeight()) + "], ";
    
    
    auto ib = getInitialBounds();
    
    contents += "\"initialBounds\": [" + std::to_string(ib.getX()) +
    ", " + std::to_string(ib.getY()) +
    ", " + std::to_string(ib.getWidth()) +
    ", " + std::to_string(ib.getHeight()) + "], ";
    
    contents += "\"encloseBoundsRelative\": [" + std::to_string(s->encloseBoundsRelative.getX()) +
    ", " + std::to_string(s->encloseBoundsRelative.getY()) +
    ", " + std::to_string(s->encloseBoundsRelative.getWidth()) +
    ", " + std::to_string(s->encloseBoundsRelative.getHeight()) + "], ";
    
    contents += "\"wrap\": " + std::to_string(s->wrap) + ", ";
    
    contents += "\"hasWrap\": " + std::to_string(s->hasEncloseObjectAlreadyDefined) + ", ";

    contents += "\"wrapColour\": [" + std::to_string(s->wrapColour.getRed()) +
    ", " + std::to_string(s->wrapColour.getGreen()) +
    ", " + std::to_string(s->wrapColour.getBlue()) +
    ", " + std::to_string(s->wrapColour.getAlpha()) + "], ";
    
    contents += "\"angle\" : " + std::to_string(getRotateAngle()) + ", ";
    
    contents += "\"startTime\": " + std::to_string(s->startTimeCode) + ", ";
    contents += "\"endTime\": " + std::to_string(s->endTimeCode);
    
    contents += "}";
    // ----------
    std::string err;
    return t_json::parse(contents,err);
    
}

t_json IRNodeObject::saveAnnotationData()
{
    
    t_json ob;
    bool hasAnnotation = hasAnnotationComponent();
    if(hasAnnotation)
    {
        
        auto item = static_cast<IRNodeObject*>(getAnnotationComponent());
        
        ob = t_json::object({
            {"hasAnnotation", hasAnnotation},
            {"annotationObject", json11::Json::object({

                {"objectType",          item->name.toStdString()},
                {"objectUniqueID",      item->getUniqueID().toStdString()},
                {"ArrangeController",   item->getArrangeControllerSaveData()},
                {"ObjectDefined",       item->saveThisToSaveData()}
            })},

        });
        

    }else{
        
        ob = t_json::object({
            {"hasAnnotation", hasAnnotation}
        });
    }

    return ob;
}

void IRNodeObject::arrangeControllerChangedCallback(ChangeBroadcaster* source)
{
    using t = ArrangeController::ArrangeControllerStatus;
    
    switch (this->arrangeController->getStatus()) {
        case t::INPUTWIDTH:
            setObjectSize(this->arrangeController->getLabelWidth(), getHeight());
            break;
        case t::INPUTHEIGHT:
            setObjectSize(getWidth(), this->arrangeController->getLabelHeight());
            break;
        case t::INPUTX:
            setObjectBounds(this->arrangeController->getLabelX(), getY(),
            getWidth(), getHeight());
            break;
        case t::INPUTY:
            setObjectBounds(getX(), this->arrangeController->getLabelY(),
                            getWidth(), getHeight());
            break;
        case t::INPUTROTATION:
            setRotateAngle(this->arrangeController->getRotation());
            break;
        case t::FRONTBUTTON:
            bringToFront();
            break;
        case t::BACKBUTTON:
            bringToBack();
            break;
        case t::ENCLOSEBUTTON:
            setEncloseMode(this->arrangeController->getEnclosedButtonStatus());
            break;
        case t::ENCLOSECOLOUR:
            setEncloseColour(this->arrangeController->getEncloseColour());
            break;
        case t::ACTIVATEBUTTON:
            setActive(this->arrangeController->getActivateStatus());
            break;
        case t::TIMECODE_BEGIN:
            setStartTimeSec(this->arrangeController->getStartTimeSec(), sendNotification);
            break;
        case t::TIMECODE_END:
            setEndTimeSec(this->arrangeController->getEndTimeSec(), sendNotification);
            break;
        default:
            break;
    }
    
    arrangeControllerChangedNotify();
}
// ==================================================


void IRNodeObject::mouseDownEvent(const MouseEvent& e)
{
    
}


void IRNodeObject::mouseUpEvent(const MouseEvent& e)
{
    
}

void IRNodeObject::mouseUpCompleted(const MouseEvent& e)
{
    notifyNodeObjectModification();
}


void IRNodeObject::mouseMoveEvent(const MouseEvent& e)
{
    
}


void IRNodeObject::mouseDoubleClickEvent(const MouseEvent& e)
{
    
}

void IRNodeObject::mouseDragEvent(const MouseEvent& e)
{
    callNodeObjectDragged();
}

void IRNodeObject::resizingStartAction()
{
    callNodeObjectResizingStart();
}

void IRNodeObject::resizingAction()
{
    callNodeObjectBeingResized();
}

void IRNodeObject::resizingCompletedAction()
{
    callNodeObjectResizingCompleted();
}




void IRNodeObject::callDragOutNodeObjectFromParent()
{
    Component::BailOutChecker checker(this);
    
    setSelected(false); // IMPORTANT
    
    
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.dragoutNodeObjectFromParent(this); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->dragoutNodeObjectCompleted != nullptr) this->dragoutNodeObjectCompleted();
}

void IRNodeObject::callDropOutNodeObjectFromParent()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.dropoutNodeObjectFromParent(this); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->dropoutNodeObjectCompleted != nullptr) this->dropoutNodeObjectCompleted();

}

void IRNodeObject::callEditModeChangedInNodeObject()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.editModeChangedInNodeObject(isEditMode()); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->editModeChangedCompleted != nullptr) this->editModeChangedCompleted();
}

void IRNodeObject::callReorderZIndex()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.reorderZIndex(); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callSaveProject()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.saveProject(); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->saveProjectCompleted != nullptr) this->saveProjectCompleted();

}

void IRNodeObject::callSaveAsProject()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.saveAsProject(); });
    //check again
    if(checker.shouldBailOut()) return;
    //std::function
    if(this->saveAsProjectCompleted != nullptr) this->saveAsProjectCompleted();
    
}

void IRNodeObject::callCloseProject()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.closeProject(); });
    //check again
    if(checker.shouldBailOut()) return;
    if(this->closeProjectCompleted != nullptr) this->closeProjectCompleted();

}

void IRNodeObject::callOpenProject()
{
    
    std::cout << "IRNodeObject : openProject" << std::endl;
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.openProject(); });
    //check again
    if(checker.shouldBailOut()) return;
    if(this->openProjectCompleted != nullptr) this->openProjectCompleted();
    
}

void IRNodeObject::callCreateNewProject()
{
    Component::BailOutChecker checker(this);
    //==========
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.createNewProject(); });
    //check again
    if(checker.shouldBailOut()) return;
    if(this->createNewProjectCompleted != nullptr) this->createNewProjectCompleted();
    
}

void IRNodeObject::callOpenFileInspecter()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.openFileInspecter(); });
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callOpenPreferenceWindow()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.openPreferenceWindow(); });
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::notifyNodeObjectModification()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;

    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectModifiedNotification(this); });
    if(checker.shouldBailOut()) return;
    
}

void IRNodeObject::callNodeObjectResizingStart()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectResizingStart(this); });
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectBeingResized()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectBeingResized(this); });
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectResizingCompleted()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectResizingCompleted(this); });
    if(checker.shouldBailOut()) return;
}
// ==================================================
/*
void IRNodeObject::callReceiveAudioLink(IRAudio* obj)
{
    printf("callReceiveAudioLink\n");
    
    if(obj == nullptr) return; // check empty object
    
    setAudioLink(obj);
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.receiveAudioLink(this); });
    if(checker.shouldBailOut()) return;
}


void IRNodeObject::callReceiveTextLink(IRText* obj)
{
    if(obj == nullptr) return; // check empty object

    setTextLink(obj);
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.receiveTextLink(this); });
    if(checker.shouldBailOut()) return;
}
void IRNodeObject::callReceiveImageLink(IRImage* obj)
{
    if(obj == nullptr) return; // check empty object

    setImageLink(obj);
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.receiveImageLink(this); });
    if(checker.shouldBailOut()) return;
}
void IRNodeObject::callReceiveDataLink(IRData* obj)
{
    if(obj == nullptr) return; // check empty object

    setDataLink(obj);
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.receiveDataLink(this); });
    if(checker.shouldBailOut()) return;
}
void IRNodeObject::callReceiveVideoLink(IRVideo* obj)
{
    if(obj == nullptr) return; // check empty object

    setVideoLink(obj);
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.receiveVideoLink(this); });
    if(checker.shouldBailOut()) return;
}
*/
void IRNodeObject::callUpdateIRFileManager(IRFileManager* fileManager)
{
    
    //setIRFileManager(fileManager);
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.updateIRFileManager(getFileManager()); });
    if(checker.shouldBailOut()) return;
}
// ==================================================

void IRNodeObject::saveObjectContents()
{
    
}


void IRNodeObject::loadObjectContents()
{
    
}

// ==================================================
// called from IRNodeComponent
void IRNodeObject::selectedChangeEvent()
{
    selectedChangedAction(isSelected());
    //call callNodeObjectSelectionChange() in Workspace
    callNodeObjectSelectionChange();
}

void IRNodeObject::thisObjectGetFocused()
{
    //std::cout << "IRNodeObject::thisObjectGetFocused\n";
    // for IRWorkspace Event
    callNodeObjectGetFocused();
}
/*
void IRNodeObject::setLinkActivationEvent()
{
    if(isLinkMode())
    {
        if(isLinkActivated()) openLinkMenu();
        else if(isLinkMode()) closeLinkMenu();
    }
    //repaint();
}
*/
void IRNodeObject::editModeChangedEvent()
{
    
}
/*
void IRNodeObject::linkModeChangedEvent()
{
    if(isLinkMode())
    {
        if(isLinkActivated()) openLinkMenu();
    }else{
        if(isLinkMenuOpened()) closeLinkMenu();
    }
    
    statusChangedWrapper(IRNodeComponentStatus::LinkModeStatus);
    repaint();
}*/


// ==================================================

void IRNodeObject::initialPaintOnWorkspace(Graphics& g, Component* workspace)
{

    //this->setLinkMenuCentrePosition(getX() + getWidth()/2,
                                    //getY() + getHeight()/2);
    paintOnWorkspace(g, workspace);
    workspace->repaint();
}

// ==================================================

void IRNodeObject::callNodeObjectSelectionChange()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectSelectionChange(this); });
    //check again
    if(checker.shouldBailOut()) return;
}


void IRNodeObject::callNodeObjectGetFocused()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectGetFocused(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectMoveToFront()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectMoveToFront(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectMoveToBack()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectMoveToBack(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectDragged()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectDragged(this); });
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectDraggedCompleted()
{
    Component::BailOutChecker checker(this);
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectDraggedCompleted(this); });
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectPositionChanged()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectPositionChanged(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectStartEndTimeChanged()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectStartEndTimeChanged(this); });
    //check again
    if(checker.shouldBailOut()) return;
}
void IRNodeObject::callNodeObjectActivateChanged()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectActivateChanged(this); });
    //check again
    if(checker.shouldBailOut()) return;
}
void IRNodeObject::callNodeObjectUIChanged()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectUIChanged(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callWantDeleteThis()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectWantsDeleted(this); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRNodeObject::callNodeObjectWillDeleted()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nodeObjectWillDeleted(this); });
    //check again
    if(checker.shouldBailOut()) return;
}
// ==================================================

void IRNodeObject::changeListenerCallback (ChangeBroadcaster* source)
{
    // first check arrange controller if it exists
    if(this->arrangeController != nullptr)
    {
        if(source == this->arrangeController)
            arrangeControllerChangedCallback(source);
    }
    
    IRChangeListenerCallback(source);
}

void IRNodeObject::IRChangeListenerCallback(ChangeBroadcaster* source)
{
    
}
// ==================================================

// ==================================================
// move to Front

void IRNodeObject::moveThisToFrontZIndex()
{
    // to inform IRWorkspace to add this object in the top of Z-Index
       callNodeObjectMoveToFront();
}

void IRNodeObject::moveToFrontEvent(bool registerZindex)
{
    // move to front z index
    if(registerZindex) moveThisToFrontZIndex();
    
    // virtual method to inform IRNodeObject
    moveToFrontAction();
    
}

void IRNodeObject::moveThisToBackIndex()
{
    // inform to IRWorkspace
    callNodeObjectMoveToBack();
}

void IRNodeObject::moveToBackEvent()
{
    // move to back z index
    moveThisToBackIndex();
    
    // IRWorkspace will reorder objects according to the new ZIndex.
    callReorderZIndex();
    
    //to inform IRNodeObject
    moveToBackAction();

}

// ==================================================
// ==================================================
// STATUS //

void IRNodeObject::setOrdinaryBounds(Rectangle<int> bounds)
{
    
    //std::cout << "setOrdinaryBounds\n";
    auto str = getStatusStr();

    str->ordinaryBounds = bounds;
    this->ordinaryBounds = bounds;
    
    calcRelativeOrdinaryBounds();
    
}

void IRNodeObject::setEncloseBounds(Rectangle<int> bounds)
{
    auto str = getStatusStr();

    this->encloseBounds = bounds;
    str->encloseBounds = bounds;
    
    calcRelativeEncloseBounds();
}

void IRNodeObject::adjustOrdinaryBoundsToRelative()
{
    float w = this->parent->getWidth();
    float h = this->parent->getHeight();
        
    this->ordinaryBounds = Rectangle<int> (floor(w * this->ordinaryBoundsRelative.getX()),
                                           floor(h * this->ordinaryBoundsRelative.getY()),
                                           floor(w * this->ordinaryBoundsRelative.getWidth()),
                                           floor(h * this->ordinaryBoundsRelative.getHeight())
                                           );
    //setObjectBounds(this->ordinaryBounds);
}

void IRNodeObject::adjustEncloseBoundsToRelative()
{
    float w = this->parent->getWidth();
    float h = this->parent->getHeight();
            
    this->encloseBounds = Rectangle<int> (
                                          floor(w * this->encloseBoundsRelative.getX()),
                                          floor(h * this->encloseBoundsRelative.getY()),
                                          floor(w * this->encloseBoundsRelative.getWidth()),
                                          floor(h * this->encloseBoundsRelative.getHeight())
                                          );
    
    /*
    std::cout << "this->encloseBoundsRelative.getY() = " << this->encloseBoundsRelative.getY() << std::endl;
    std::cout << "adjustEncloseBoundsToRelative : " << this->encloseBounds.getX() << ", " << this->encloseBounds.getY() << " : "<<this->encloseBounds.getWidth() << ", " << this->encloseBounds.getHeight() << std::endl;
    
    std::cout << "encloseObject : " << this->enclosedObject.getBounds().getX() << ", " << this->enclosedObject.getBounds().getY() << " : "<<this->enclosedObject.getBounds().getWidth() << ", " << this->enclosedObject.getBounds().getHeight() << std::endl;
     */
}

void IRNodeObject::setStatus(IRNodeObjectStatus newStatus)
{
    this->status = newStatus;
    
    switch(newStatus)
    {
        case ORDINARY:
            transformStatusToOrdinary();
            break;
        case ENCLOSE:
            transformStatusEnclose();
            break;
        default:
            break;
    }
}

void IRNodeObject::transformStatusToOrdinary()
{

    this->resizingSquare.applyMouseListenerToIRNodeObject();
    this->resizingSquare.removeMouseListener(&this->enclosedObject);
    
    showEncloseObject(false);
    
    adjustOrdinaryBoundsToRelative();
    setObjectBounds(this->ordinaryBounds);
}

void IRNodeObject::transformStatusEnclose()
{
    std::cout << "transformStatusEnclose : bounds " << getBounds().getWidth() << ", " << getBounds().getHeight() << " : ordinary = " << this->ordinaryBounds.getWidth() << ", " << this->ordinaryBounds.getHeight() << std::endl;
    
    showEncloseObject(true);

    // then move this object to the enclosed object if encloseBounds is not empty
    if(hasEncloseAlreadyDefined())
    {
        std::cout << "hasEnclosedAlreadyDefined\n";
        adjustEncloseBoundsToRelative();
        setObjectBounds(this->encloseBounds);
        
        this->enclosedObject.setBounds(getLocalBounds());
        auto b = this->enclosedObject.getBounds();
        std::cout << "encloseObject bounds = " << b.getX() << " , " << b.getY() << " : " << b.getWidth() << ", " << b.getHeight() << std::endl;
        
        b = this->encloseBounds;
        std::cout << "encloseBounds = " << b.getX() << " , " << b.getY() << " : " << b.getWidth() << ", " << b.getHeight() << std::endl;

        
    }else{
        std::cout << "NOE YET enclose DEFINED\n";

        // first time set
        this->encloseBounds = getBounds();
        calcRelativeEncloseBounds();
        adjustEncloseBoundsToRelative();

        setEncloseAlreadyDefined(true);
        setObjectBounds(this->encloseBounds);
        this->enclosedObject.setBounds(getLocalBounds());

        
    }
    
    this->resizingSquare.toFront(true);
    
}

void IRNodeObject::createEnclosedObject()
{
    this->enclosedObject.onClick = [this]{ enclosedObjectClickedAction(); };
    addAndMakeVisible(this->enclosedObject);
    this->enclosedObject.addMouseListener(this, true);
    
    this->goBackToEncloseButton.reset( new EncloseButton(getStr()) );
    this->goBackToEncloseButton->setButtonText("close");
    this->goBackToEncloseButton->setColour(TextButton::ColourIds::buttonColourId, getStr()->SYSTEMCOLOUR.fundamental);
    this->goBackToEncloseButton->onClick = [this] { goBackToEncloseButtonClicked(); };
    this->parent->addAndMakeVisible(this->goBackToEncloseButton.get());
    this->goBackToEncloseButton->setVisible(false);
    
}

void IRNodeObject::showEncloseObject(bool flag)
{
    //std::cout << "showEncloseObject " << flag << std::endl;
    //update colour
    this->enclosedObject.setColour(this->arrangeController->getEncloseColour());
    getStatusStr()->wrapColour = this->arrangeController->getEncloseColour();
    
    
    if(flag) addAndMakeVisible(this->enclosedObject);
    else removeChildComponent(&this->enclosedObject);
    
    this->enclosedObject.setVisible(flag);
    
    if(flag) this->enclosedObject.toFront(true);
    else this->enclosedObject.toBack();
    
    //std::cout << "encloseObject visible = " << this->enclosedObject.isVisible() << std::endl;
}

void IRNodeObject::calcRelativeOrdinaryBounds()
{
    float w = (float) this->parent->getWidth();
    float h = (float) this->parent->getHeight();
    
    auto b = this->ordinaryBounds;
    this->ordinaryBoundsRelative = Rectangle<float> (
                                                     (float)b.getX() / w,
                                                     (float)b.getY() / h,
                                                     (float)b.getWidth() / w,
                                                     (float)b.getHeight() / h
                                                     );
    
    
    
    
    adjustRectangleFloatToAboveZero(this->ordinaryBoundsRelative);

    auto s = getStatusStr();
    s->ordinaryBoundsRelative = this->ordinaryBoundsRelative;
    
}

void IRNodeObject::calcRelativeEncloseBounds()
{
    float w = (float) this->parent->getWidth();
    float h = (float) this->parent->getHeight();
    
    auto b = this->encloseBounds;
    this->encloseBoundsRelative = Rectangle<float> (
                                                     (float)b.getX() / w,
                                                     (float)b.getY() / h,
                                                     (float)b.getWidth() / w,
                                                     (float)b.getHeight() / h
                                                     );
    
    adjustRectangleFloatToAboveZero(this->encloseBoundsRelative);
    auto s = getStatusStr();
    s->encloseBoundsRelative = this->encloseBoundsRelative;
 
}

void IRNodeObject::adjustRectangleFloatToAboveZero(Rectangle<float>& bounds)
{
    if(bounds.getX() < 0) bounds.setX(0);
    if(bounds.getY() < 0) bounds.setY(0);
    if(bounds.getWidth() < 0) bounds.setWidth(0);
    if(bounds.getHeight() < 0) bounds.setHeight(0);
}


void IRNodeObject::setEncloseColour(Colour colour)
{
    auto statusStr = getStatusStr();
    statusStr->wrapColour = colour;
    this->enclosedObject.setColour(colour);
}

void IRNodeObject::enclosedObjectClickedAction()
{
    std::cout << "enclosedObject clicked\n";
    if(isEditMode())
    {
        
    }else{
        enclosedObjectClickedInControlMode();
    }
}

void IRNodeObject::enclosedObjectClickedInControlMode()
{
    if(getStatus() == IRNodeObjectStatus::ENCLOSE)
    {
        createGoBackToEncloseButton(true);
        setEncloseMode(false);
        getArrangeController()->setEncloseToggle(false, dontSendNotification);
        
    }else if(getStatus() == IRNodeObjectStatus::ORDINARY)
    {
        createGoBackToEncloseButton(false);

        setEncloseMode(true);
        getArrangeController()->setEncloseToggle(true, dontSendNotification);
    }
}

void IRNodeObject::goBackToEncloseButtonClicked()
{
    enclosedObjectClickedInControlMode();
}

void IRNodeObject::createGoBackToEncloseButton(bool createOrDelete)
{
    
    std::cout <<"createGoBackToEncloseButton : " << createOrDelete << std::endl;
    if(createOrDelete)
    {
        std::cout <<"createGoBackToEncloseButton visible \n";
        this->goBackToEncloseButton->setVisible(true);
        this->goBackToEncloseButton->toFront(true);
        setBoundsGoBackToEncloseButton();
    }else{
        this->goBackToEncloseButton->setVisible(false);
    }
    
}

void IRNodeObject::setBoundsGoBackToEncloseButton()
{
    
    if(!this->goBackToEncloseButton->isVisible()) return;
    
    std::cout << "setBoundsGoBackToEncloseButton\n";
    auto b = getBounds();
    auto p = this->parent->getBounds();
    int w = 50;
    int h = 20;
    if(b.getX() < p.getWidth()/2)
    {
        this->goBackToEncloseButton->setBounds(b.getX() + b.getWidth(),
                                               b.getY(),
                                               w, h);
    }else{
        this->goBackToEncloseButton->setBounds(b.getX() - w,
                                               b.getY(),
                                               w, h);
    }
    
    
  
}



void IRNodeObject::setEncloseMode(bool flag)
{
    
    std::cout << "setEncloseMode " << flag << std::endl;
    // data
    auto statusStr = getStatusStr();
    statusStr->wrap = flag;
    
    
    if(flag) setStatus(IRNodeObjectStatus::ENCLOSE);
    else setStatus(IRNodeObjectStatus::ORDINARY);
}

void IRNodeObject::setEncloseAlreadyDefined(bool flag)
{
    this->hasEncloseObjectAlreadyDefined = flag;
    getStatusStr()->hasEncloseObjectAlreadyDefined = flag;
}

// ==================================================

void IRNodeObject::ObjectPositionChanged4IRNodeObject(int x, int y)
{
    encloseObjectPositionChangedAction(x, y);
    arrangeControllerPositionChangedAction(x, y);
}

void IRNodeObject::ObjectBoundsChanged4IRNodeObject(Rectangle<int> bounds)
{
    
    updateResizingSquare();
    encloseObjectBoundsChangedAction(bounds);
    arrangeControllerBoundsChangedAction(bounds);
    //IRNodeObject::Listener
    callNodeObjectPositionChanged();
}

void IRNodeObject::encloseObjectPositionChangedAction(int x, int y)
{
    if(this->status == IRNodeObjectStatus::ENCLOSE)
    {
        this->enclosedObject.setBounds(getLocalBounds());
        setEncloseBounds(getBounds());
    }else if(this->status == IRNodeObjectStatus::ORDINARY){
        setOrdinaryBounds(getBounds());
    }
}

void IRNodeObject::encloseObjectBoundsChangedAction(Rectangle<int> bounds)
{
    if(this->status == IRNodeObjectStatus::ENCLOSE)
    {
        this->enclosedObject.setBounds(getLocalBounds());
        setEncloseBounds(getBounds());
    }else if(this->status == IRNodeObjectStatus::ORDINARY){
        setOrdinaryBounds(getBounds());
    }
}
                                           
                                           
void IRNodeObject::arrangeControllerPositionChangedAction(int x, int y)
{
    // update arrangeController Labels
    if(this->arrangeController != nullptr)
    {
        this->arrangeController->setLabelX(x);
        this->arrangeController->setLabelY(y);
    }
}
                                           
void IRNodeObject::arrangeControllerBoundsChangedAction(Rectangle<int> bounds)
{
    // set bounds info without emitting notification
    if(this->arrangeController != nullptr)
        this->arrangeController->setRectangle(getBounds());
 }

void IRNodeObject::loadArrangeControllerSaveData(t_json arrangeCtl, IRBoundType type)
{
    std::cout << " # loadArrangeControllerSaveData\n";

    auto eb = arrangeCtl["encloseBounds"].array_items();

    auto ebr = arrangeCtl["encloseBoundsRelative"].array_items();
    
    // we need to determin boundtype each time of calling loadArrangeControllerSaveData.
    setBoundType(type);
    // ====== WRAP ======
    //wrap colour
    auto wrapColour = arrangeCtl["wrapColour"].array_items();
    Colour wc = Colour((uint8)wrapColour[0].int_value(),
                       (uint8)wrapColour[1].int_value(),
                       (uint8)wrapColour[2].int_value(),
                       (uint8)wrapColour[3].int_value()
                       );
    
    setEncloseColour(wc);
    auto a = getArrangeController();
    if(a != nullptr)
    {
        a->setEncloseColour(wc);
    }
    
    auto ib = arrangeCtl["initialBounds"].array_items();
    setObjectBounds(Rectangle<int>(ib[0].number_value(), ib[1].number_value(), ib[2].number_value(), ib[3].number_value()));

    std::cout << " ## initialBounds ("<< ib[0].number_value() << ", " << ib[1].number_value() << ", " << ib[2].number_value() << ", " << ib[3].number_value() << ")" << std::endl;
    this->encloseBoundsRelative = Rectangle<float>(ebr[0].number_value(), ebr[1].number_value(),
                                                   ebr[2].number_value(), ebr[3].number_value());
    
    float angle = arrangeCtl["angle"].number_value();
    setRotateAngle(angle);
    getArrangeController()->setRotation(angle);
    
    int wrap = arrangeCtl["wrap"].int_value();
    int hasWrap = arrangeCtl["hasWrap"].int_value();
    setEncloseAlreadyDefined((bool)hasWrap);
    
    // give wrap only when wrap is TRUE because the oridinary bounds of the enclosed mode does not have the initial bounds. It gets the bounds only when it transfers to enclose mode.
    
    if(wrap == 1)
    {
        
        // adjust bounds based in the relative ratio to the parent size
        //adjustEncloseBoundsToRelative();
        getArrangeController()->setEncloseToggle(true, sendNotification);
        setEncloseMode((bool)wrap);
            
        // adjust ordinary bounds in accordance with the current parent component bounds
        //adjustOrdinaryBoundsToRelative();

    }else{
        // adjust enclose bounds in accordance with the current parent component bounds
        //adjustEncloseBoundsToRelative();
    }
    // ====== TimeCode ======
    float startTime = arrangeCtl["startTime"].number_value();
    float endTime = arrangeCtl["endTime"].number_value();
    
    setStartTimeSec(startTime);
    setEndTimeSec(endTime);
    
    std::cout << "loadArranceControllerSaveData completed\n";

}
// ==================================================


void IRNodeObject::setWorkspaceActive(bool flag)
{
    // virtual method
    workspaceActiveStatusChanged(flag);
}
// ==================================================

void IRNodeObject::setStartTimeSec(float sec, NotificationType notification)
{
    this->StartTimeSec = sec;
    getStatusStr()->startTimeCode = sec;
    getArrangeController()->setStartTimeSec(sec);
    //std::cout << "StartTimeSec = " << sec << std::endl;
    
    if(notification == sendNotification)
    {
        paramChanged();
        callNodeObjectStartEndTimeChanged();
    }
    
}
void IRNodeObject::setEndTimeSec(float sec, NotificationType notification)
{
    this->EndTimeSec = sec;
    getStatusStr()->endTimeCode = sec;
    getArrangeController()->setEndTimeSec(sec);

    //std::cout << "EndTimeSec = " << sec << std::endl;
    if(notification == sendNotification)
    {
        paramChanged();
        callNodeObjectStartEndTimeChanged();
    }
    
    
}

// ==================================================

void IRNodeObject::updateEventParam()
{
    if(getEventComponent() == nullptr) return;
    
    IRNodeObject* target = static_cast<IRNodeObject*>(getEventComponent());
    float start = getStartTimeSec();
    float end = getEndTimeSec();
    
    // sendNotification to the event object to let workspace knows the modification
    target->setStartTimeSec(start, sendNotification);
    target->setEndTimeSec(end, sendNotification);
    //target->getArrangeController()->setStartTimeSec(start);
    //target->getArrangeController()->setEndTimeSec(end);
}

void IRNodeObject::updateAnnotationParam()
{
    if(getAnnotationComponent() == nullptr) return;
    
    IRNodeObject* target = static_cast<IRNodeObject*>(getAnnotationComponent());
    float start = getStartTimeSec();
    float end = getEndTimeSec();
    
    target->setStartTimeSec(start);
    target->setEndTimeSec(end);
    //target->getArrangeController()->setStartTimeSec(start);
    //target->getArrangeController()->setEndTimeSec(end);

}


void IRNodeObject::paramChanged()
{
    std::cout << "IRNodeObject::paramChanged\n";
    if(hasEventComponent()) updateEventParam();
    //if(hasAnnotationComponent()) updateAnnotationParam();
}
// ==================================================
