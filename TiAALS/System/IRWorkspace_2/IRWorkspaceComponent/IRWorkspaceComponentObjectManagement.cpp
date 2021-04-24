//
//  IRWorkspaceComponentObjectManagement.cpp
//  IRiMaS
//
//  Created by Keitaro on 18/09/2019.
//

#include "IRWorkspaceComponent.hpp"

void IRWorkspaceComponent::copySelectedObjects()
{
    this->copiedObjects.clear();
    
    std::cout << "copySelectedObjects : " << this->selector->getSelectedObjectList().size() << std::endl;
    for (auto obj : this->selector->getSelectedObjectList())
    {
        
        std::cout << "copying... " << obj << std::endl;
        copyObject(obj, false);
    }
}
// ------------------------------------------------------------

void IRWorkspaceComponent::pasteSelectedObjects()
{
    std::cout << "pasteObject 2\n";

    for (auto obj: this->copiedObjects)
    {
        pasteObject(obj,true);
    }
    //this->selector->addSelectedObjects();
    copySelectedObjects();
}
// ------------------------------------------------------------

void IRWorkspaceComponent::deselectAllObjects()
{
    auto list = this->selector->getSelectedObjectList();

    for(auto obj : list )
    {
        obj->setSelected(false);
    }
}

void IRWorkspaceComponent::deleteSelectedObjects()
{
    auto list = this->selector->getSelectedObjectList();
    
    for(auto obj : list)
    {
       // std::cout << "IRWorkspaceComponent : delete obj " << obj << std::endl;
        deleteObject(obj);
    }
    
    // initialize the focuses on any NodeObject
    nodeObjectGetFocused(nullptr);
    
    repaint();
}

// ------------------------------------------------------------

void IRWorkspaceComponent::duplicateSelectedObjects()
{
    copySelectedObjects();
    pasteSelectedObjects();
    
    //resortHeavyObject();
}


void IRWorkspaceComponent::createObject(IRNodeObject *obj, bool shouldSort)
{
    std::cout << "createObject ==================================================\n ";
        
    //obj->setTransform(AffineTransform::scale(this->zoomRatio));
    
    obj->setResizableMargin(this->draggableMargin);
    // make uniqueID
    //KeRandomStringGenerator a;
    //std::string id = a.createStrings(10);
    // generate uniqueID
    //obj->setUniqueID("id-aa");
    addAndMakeVisible(obj);
    obj->toFront(true);
    obj->addChangeListener(this);
    obj->addListener(this); // IRNodeObjectListener
    obj->addKeyListener(this); // key listener
    this->objects.add(obj);
    
    obj->setZoomable(this->widthZoomable, this->heightZoomable);
    obj->setZoomRatio(this->zoomRatio);
    // adjust object size to the zoom ratio only if both width and height are zoomable
    //if(this->widthZoomable && this->heightZoomable)
     //   obj->setObjectSize(obj->getWidth() / this->zoomRatio, obj->getHeight() / this->zoomRatio);
    
    
    // use this function in order to update file manger of all related UIs etc.
    obj->updateFileManager(this->ir_str->FILEMANAGER);
    obj->callUpdateIRFileManager(&this->ir_str->FILEMANAGER);
    
    //audiosource
    if (obj->isContainAudioSource())
    {
        this->mixer.addAudioSource(obj->getAudioSource());
    }

    
    // register this object to ZOrderIndex but do not refresh heavy weight component order.
    insertObjectAtTopZOrder(obj);
    obj->toFront(true);

    obj->setEditMode(isEditMode());
    
    // let parent componet know
    callNodeObjectCreated(obj);

    //request updating the workspaceList
    if(requestWorkspaceListUpdate != nullptr) requestWorkspaceListUpdate();


    repaint();
    
}


// ------------------------------------------------------------
void IRWorkspaceComponent::copyObject(IRNodeObject *obj, bool clearCopied)
{
    if(clearCopied) this->copiedObjects.clear();
    this->copiedObjects.add(obj);
}

void IRWorkspaceComponent::pasteObject(IRNodeObject *obj, bool addToSelected)
{
    IRNodeObject* newObj = obj->copyThis();
    
    createObject(newObj);
    
    newObj->setObjectBounds(Rectangle<int>(obj->getPosition().x-20, obj->getPosition().y-20,
                                           obj->getWidth(), obj->getHeight()));

    obj->setSelected(false);
    this->selector->removeSelectedObject(obj);
    
    newObj->setSelected(true);
    
    if(addToSelected)
    {
        this->selector->addSelectedObjects();
        //copySelectedObjects();
    }
 
   
    // not used by any classes on 11 March 2021
    callNodeObjectPasted(newObj);
}
void IRWorkspaceComponent::duplicateObject(IRNodeObject *obj)
{
    copyObject(obj, true);
    pasteObject(obj, true);
}
void IRWorkspaceComponent::deleteObject(IRNodeObject *obj)
{
    this->selector->removeSelectedObject(obj);

    callNodeObjectWillDeleted(obj);

    removeObjectFromZOrder(obj);
    removeChildComponent(obj);
    
    int index = this->objects.indexOf(obj);
    
    if (obj->isContainAudioSource())
        this->mixer.removeSource(obj->getAudioSource());
    
    if(index >= 0){
        
        this->objects.remove(index);
        
        
        // ---------------------------------------------
        // ask workspace to delete event or annotation
        if(obj->hasEventComponent())
        {
            std::cout <<"deleting eventComponent\n";
            auto e = obj->getEventComponent();
            if(e != nullptr)
            {
                auto eo = static_cast<IRNodeObject*>(e);
                eo->callWantDeleteThis();
                obj->removeEventComponent();
            }else std::cout <<"failed\n";

        }
        
        if(obj->hasAnnotationComponent())
        {
            auto a = obj->getAnnotationComponent();
            if(a != nullptr)
            {
                auto ao = static_cast<IRNodeObject*>(a);
                ao->callWantDeleteThis();
                obj->removeAnnotationComponent();
            }
        }
        // ---------------------------------------------

        
        delete obj;
        
    }
    
    //request updating the workspaceList
    if(requestWorkspaceListUpdate != nullptr) requestWorkspaceListUpdate();
}

void IRWorkspaceComponent::deleteAllObjects()
{
    this->selector->selectAllObjects();
    deleteSelectedObjects();
}

// ------------------------------------------------------------

void IRWorkspaceComponent::createCover()
{
    /*
    this->cover.reset(new IRWorkspaceCover(getStr()));
    
    addAndMakeVisible(this->cover.get());
    this->cover->addMouseListener(this, true);
    this->cover->addMouseListener(getStr()->projectOwner, false);
    this->cover->addKeyListener(this);
    // add top key lis
    this->cover->addKeyListener(getStr()->key);
    
    */
    
}


void IRWorkspaceComponent::bringCoverToBack()
{
    /*
    if(this->cover.get() != nullptr)
    {
        toBack();
    }
    */
}


void IRWorkspaceComponent::setCoverEditMode(bool editMode)
{
    /*
    if(this->cover.get() != nullptr)
    {
        this->cover->setEditMode(editMode);
    }*/
}

void IRWorkspaceComponent::setGridValue(int grid)
{
    setGridInterval(grid, 5);
}

// ------------------------------------------------------------

void IRWorkspaceComponent::bringParentNodeObjectToFront()
{
    if(this->parentNodeObject != nullptr)
    {
        
        std::cout << "bringParentNodeObjectToFront " << this->parentNodeObject << std::endl ;
        this->parentNodeObject->toFront(true);
        // in case parentNodeObje
        this->parentNodeObject->moveToFrontAction();
        
    }else{
        std::cout << "parentNodeObject = " << this->parentNodeObject << std::endl;
    }
}

void IRWorkspaceComponent::bringParentNodeObjectToBack()
{
    if(this->parentNodeObject != nullptr)
        this->parentNodeObject->bringToBack();

}

// ------------------------------------------------------------


void IRWorkspaceComponent::setParentNodeObject(IRNodeObject* newParentNodeObject)
{
    this->parentNodeObject = newParentNodeObject;
    
    std::cout << "IRWorkspaceComponent::setParentNodeObject " << this->parentNodeObject << std::endl;
    this->hasParentNodeObjectFlag = true;
    this->parentNodeObject->setEnableResizingSquare(false);
    
    /*
    if(this->cover != nullptr)
    {
        this->cover->addMouseListener(this->parentNodeObject, true);
    }*/
}

void IRWorkspaceComponent::removeParentNodeObject()
{
    this->parentNodeObject = nullptr;
    this->hasParentNodeObjectFlag = false;
}

// ------------------------------------------------------------
void IRWorkspaceComponent::dragoutNodeObjectFromParent(IRNodeObject* obj)
{
    std::cout << "workspace : dragoutNodeObject" << std::endl;
    
    // change edit mode and notify its change
    // because dragoutNodeObjectFromParent is called from IRNodeObject and not the up down order.
    setEditMode(true, true);
    // notify the change of editMode to IRProject
    if (this->notifyEditModeChanged != nullptr)
    {
        this->notifyEditModeChanged();
    }
    
    // create new object
    IRNodeObject* o = obj->copyThis();
    
    // create eobject first!!
    createObject(o);
    
    // copy contents here.
    o = obj->copyDragDropContents(o);
    
    // set Position
    o->setObjectCentredPosition(this->currentMousePosition.getX(),
                                this->currentMousePosition.getY());
    
    // set other parameters
    o->setSelected(true);
    this->selector->addSelectedObjects();
    o->repaint();
    
    this->dummy.add(o);
    
}
// ------------------------------------------------------------
void IRWorkspaceComponent::dropoutNodeObjectFromParent(IRNodeObject* obj)
{
    std::cout << "workspace : dropOut" << std::endl;
    
}
// ------------------------------------------------------------
void IRWorkspaceComponent::editModeChangedInNodeObject(bool editMode)
{
    setEditMode(editMode);
    
    // notify it to IRProject
    if(this->notifyEditModeChanged != nullptr)
    {
        this->notifyEditModeChanged();
    }
}

// ------------------------------------------------------------
void IRWorkspaceComponent::saveProject()
{
    if(this->requestSaveProject != nullptr) requestSaveProject();
}
void IRWorkspaceComponent::saveAsProject()
{
    if(this->requestSaveAsProject != nullptr) requestSaveAsProject();
}
void IRWorkspaceComponent::closeProject()
{
    if(this->requestCloseProject != nullptr) requestCloseProject();
}
void IRWorkspaceComponent::openProject()
{
    if(this->requestOpenProject != nullptr) requestOpenProject();
}
void IRWorkspaceComponent::createNewProject()
{
    if(this->requestNewProject != nullptr) requestNewProject();
}
void IRWorkspaceComponent::openFileInspecter()
{
    if(this->requestOpenFileInspecter != nullptr) requestOpenFileInspecter();
}

// ============================================================

// ------------------------------------------------------------

void IRWorkspaceComponent::nodeObjectModifiedNotification(IRNodeObject* obj)
{
    // for child class
    nodeObjectModifiedAction(obj);
    
    if(this->notifyNodeObjectModification != nullptr)
        this->notifyNodeObjectModification(obj);

}

void IRWorkspaceComponent::nodeObjectSelectionChange(IRNodeObject* obj)
{
    //std::cout << "IRWorkspaceComponent nodeObjectSelectionChange " << obj << std::endl;
    
    // add
    this->selector->addSelectedObjects();

    callNodeObjectSelectionChange(obj);
    
    std::cout << this->selector->getSelectedObjectList().size() << std::endl;

}

void IRWorkspaceComponent::nodeObjectGetFocused(IRNodeObject* obj)
{
    
    if(obj != nullptr)
    {
        std::cout << "IRWorkspaceComponent nodeObjectGetFocused " << obj << " : " << obj->name << std::endl;
    }else{
        std::cout << "IRWorkspaceComponent nodeObjectGetFocused " << obj << std::endl;

    }
    //this->cover->toBack();
    callNodeObjectGetFocused(obj);
    
}

void IRWorkspaceComponent::nodeObjectMoveToFront(IRNodeObject* obj)
{
    // bring obj to the top front Z order
    insertObjectAtTopZOrder(obj);
    
    // here we do not need to call reorderZIndex() because only the top z-order object and other elements which should be forward to the top objects need to be re-binded, and all objects behind them are no need to be refreshed.
}

void IRWorkspaceComponent::nodeObjectMoveToBack(IRNodeObject* obj)
{
    
    // bring obj to the top front Z order
    insertObjectAtEndZOrder(obj);
    
    //reorderZIndex();
}

void IRWorkspaceComponent::nodeObjectWantsDeleted(IRNodeObject* obj)
{
    std::cout << "IRWorkspaceComponent::nodeObjectWantsDeleted\n";
    deleteObject(obj);
}

void IRWorkspaceComponent::reorderZIndex()
{
    //re-order the objects
}

void IRWorkspaceComponent::callNodeObjectSelectionChange(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectSelectionChange(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRWorkspaceComponent::callNodeObjectGetFocused(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectGetFocused(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRWorkspaceComponent::callEditModeChanged()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.editModeChanged(this); });
    //check again
    if(checker.shouldBailOut()) return;
}


void IRWorkspaceComponent::callNothingSelected()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nothingSelected(); });
    //check again
    if(checker.shouldBailOut()) return;
}

// ============================================================

void IRWorkspaceComponent::callNodeObjectCreated(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectCreated(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}


void IRWorkspaceComponent::callNodeObjectCopied(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectCopied(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}
void IRWorkspaceComponent::callNodeObjectPasted(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectPasted(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}
void IRWorkspaceComponent::callNodeObjectWillDeleted(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectWillDeleted(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}

// ============================================================

void IRWorkspaceComponent::insertObjectAtTopZOrder(IRNodeObject* obj)
{
    
    std::cout << "IRWorkspaceComponent::insertObjectAtTopZOrder : " << obj->name << std::endl;
    std::cout << "insertObjectAtTopZOrder : " << obj << std::endl;
    // check if inserted obj is already registered and remove it.
    auto it = std::find(this->ObjectZorder.begin(), this->ObjectZorder.end(), obj);
    if(it != this->ObjectZorder.end())
    {
        this->ObjectZorder.erase(it);
    }
    
    it = this->ObjectZorder.begin();
    this->ObjectZorder.insert(it, obj);
    
    for(int i = 0; i < this->ObjectZorder.size(); i ++)
    {
        this->ObjectZorder[i]->sortIndex = i;
        //std::cout << this->ObjectZorder[i]->name << " : " << this->ObjectZorder[i]->sortIndex << std::endl;
    }
}

// ============================================================


void IRWorkspaceComponent::insertObjectAtEndZOrder(IRNodeObject* obj)
{
    // check if inserted obj is already registered and remove it.
    auto it = std::find(this->ObjectZorder.begin(), this->ObjectZorder.end(), obj);
    if(it != this->ObjectZorder.end())
    {
        this->ObjectZorder.erase(it);
    }
    
    it = this->ObjectZorder.end();
    this->ObjectZorder.insert(it, obj);
    
    for(int i = 0; i < this->ObjectZorder.size(); i ++)
    {
        this->ObjectZorder[i]->sortIndex = i;
        //std::cout << this->ObjectZorder[i]->name << " : " << this->ObjectZorder[i]->sortIndex << std::endl;
    }
}

void IRWorkspaceComponent::removeObjectFromZOrder(IRNodeObject* obj)
{
    
    //std::cout << "removeObjectFromZOrder : " << obj << std::endl;

    auto it = std::find(this->ObjectZorder.begin(), this->ObjectZorder.end(), obj);
    if(it != this->ObjectZorder.end())
    {
        this->ObjectZorder.erase(it);
    }
    
    for(int i = 0; i < this->ObjectZorder.size(); i ++)
       {
           this->ObjectZorder[i]->sortIndex = i;
           //std::cout << this->ObjectZorder[i]->name << " : " << this->ObjectZorder[i]->sortIndex << std::endl;
       }
}

