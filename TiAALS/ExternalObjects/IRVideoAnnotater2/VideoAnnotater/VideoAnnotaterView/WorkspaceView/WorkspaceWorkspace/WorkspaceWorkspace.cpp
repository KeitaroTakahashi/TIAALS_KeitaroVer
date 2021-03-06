//
//  WorkspaceWorkspace.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 26/03/2021.
//

#include "WorkspaceWorkspace.hpp"

WorkspaceWorkspace::WorkspaceWorkspace(String title,
                                                 Rectangle<int> draggableMargin,
                                                 IRStr* str,
                                       VideoAnnotaterBase* base,
                                                 int index) :
IRAnnotationWorkspace(title, draggableMargin, str, index),
VideoAnnotaterDelegate(base)
{
    setOpaque(false);
    
    // set only width zoomable
    setZoomable(true, false);
    setCenterMargin(Rectangle<int>(1,1,0,0));

    setWantsKeyboardFocus(true);
    addKeyListener(this);
    this->line.addMouseListener(this, true);
    
    // notify when it is about to delete object
    setAskBeforeDeleteObjectByKeyCommand(true,this->beforeDeleteObjectMessage);
    
    //addAndMakeVisible(this->measure);
    addAndMakeVisible(this->line);
    
}

WorkspaceWorkspace::~WorkspaceWorkspace()
{
    
}

void WorkspaceWorkspace::onPaint(Graphics& g)
{
    g.fillAll(Colours::grey);
}

void WorkspaceWorkspace::onResized()
{
    
    //this->measure.setBounds(0, 0, getWidth(), this->measureHeight);
    
    int x = (double)getWidth() * (this->currentPlayingPosition / this->videoLength);
    
    this->line.setBounds(x, 0, 4, getHeight());
    
}


void WorkspaceWorkspace::IRChangeListenerCallback(ChangeBroadcaster* source)
{
    
}


IRNodeObject* WorkspaceWorkspace::createTextObject()
{
    auto obj = IRObjectCreater<IRVNTextEditorObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);
    IRVNTextEditorObject* nodeObj = static_cast<IRVNTextEditorObject*>(obj);
    createNodeObjectOnWorkspace(nodeObj);
    return nodeObj;
}

IRNodeObject* WorkspaceWorkspace::createTextSequenceObject()
{
    auto obj = IRObjectCreater<IRVNTextEditorObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);
    IRVNTextEditorObject* nodeObj = static_cast<IRVNTextEditorObject*>(obj);
    createNodeObjectOnWorkspace(nodeObj);
    return nodeObj;
}

IRNodeObject* WorkspaceWorkspace::createShapeObject()
{
    auto obj = IRObjectCreater<IRVNShapeObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);
    IRVNShapeObject* nodeObj = static_cast<IRVNShapeObject*>(obj);
    nodeObj->setObjectSize(200, 100);
    createNodeObjectOnWorkspace(nodeObj);
    
    return nodeObj;
}

IRNodeObject* WorkspaceWorkspace::createImageObject()
{
    auto obj = IRObjectCreater<IRVNImageViewerObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);
    IRVNImageViewerObject* nodeObj = static_cast<IRVNImageViewerObject*>(obj);
    nodeObj->setObjectSize(200, 100);
    createNodeObjectOnWorkspace(nodeObj);
    return nodeObj;
}

void WorkspaceWorkspace::createNodeObjectOnWorkspace(IRNodeObject* nodeObj)
{
    createObject(nodeObj);
    auto visibleSpace = getVisibleArea();
    nodeObj->setObjectCentredPosition(visibleSpace.getX() + visibleSpace.getWidth()/2,
                                      visibleSpace.getY() + visibleSpace.getHeight()/2);
}

void WorkspaceWorkspace::createNodeObjectFromAnnotation(IRNodeObject* annotation)
{
    auto name = annotation->name;
    std::cout << "name = " << name << std::endl;
    if ( name == "IRTextEditor")
    {
        createTextObjectFromAnnotation(annotation);
    }else if( name == "IRShape")
    {
        createShapeObjectFromAnnotation(annotation);
    }else if( name == "IRImageViewer")
    {
        createImageObjectFromAnnotation(annotation);
    }
    
    // give back the focus to videoAnnotaterWorkspace
    annotation->toFront(true);
}

// ---------------------------------------------
IRNodeObject* WorkspaceWorkspace::createTextObjectFromAnnotation(IRNodeObject* annotaiton)
{
    auto a = static_cast<IRVNTextEditorObject*>(annotaiton);
    auto obj = createTextSequenceObject();
    setupEventObject(a, obj);
    obj->initialiseSetup("text", Colour(uint8(255),
                                        uint8(0),
                                        uint8(0),
                                        uint8(51)));
    return obj;
}
IRNodeObject* WorkspaceWorkspace::createShapeObjectFromAnnotation(IRNodeObject* annotaiton)
{
    auto a = static_cast<IRVNShapeObject*>(annotaiton);
    auto obj = createTextSequenceObject();
    setupEventObject(a, obj);
    obj->initialiseSetup("shape", Colour(uint8(255),
                                         uint8(0),
                                         uint8(0),
                                         uint8(51)));
    return obj;
}
IRNodeObject* WorkspaceWorkspace::createImageObjectFromAnnotation(IRNodeObject* annotaiton)
{
    auto a = static_cast<IRVNImageViewerObject*>(annotaiton);
    auto obj = createTextSequenceObject();
    setupEventObject(a, obj);
    obj->initialiseSetup("image", Colour(uint8(255),
                                         uint8(0),
                                         uint8(0),
                                         uint8(51)));
    return obj;
}

// ----------------------------------------
void WorkspaceWorkspace::setupEventObject(IRNodeObject* annotation, IRNodeObject* event)
{
    
    double start = getCurrentVideoPosition();
    
    event->setStartTimeSec(start);
    event->setEndTimeSec(start + 3.0);
    
    event->setAnnotation(annotation);
    adjustObjectWidthToLength(event);
    adjustStartPosition(event);
    annotation->setEventComponent(event);
}

// ---------------------------------------------

// --------------------------------------------------

void WorkspaceWorkspace::adjustObjectWidthToLength(IRNodeObject* event)
{
    float start = event->getStartTimeSec();
    float end = event->getEndTimeSec();
    
    float duration = end - start;
    
    float pixelPerSec = (float)getWidth() / this->videoLength;
    float objectWidth = pixelPerSec * duration;
    
    event->setObjectSize(objectWidth, event->getHeight());
}

void WorkspaceWorkspace::adjustStartPosition(IRNodeObject* event)
{
    float start = event->getStartTimeSec();
    
    
    float pixelPerSec = (float)getWidth() / this->videoLength;
    float x = pixelPerSec * start;
    
    event->setObjectTopLeftPosition(x, event->getY());;
}

void WorkspaceWorkspace::calcEventTimeFromBounds(IRNodeObject* event)
{
    float pixelPerSec = (float)getWidth() / this->videoLength;
    
    float x = (float)event->getBounds().getX();
    float w = (float)event->getBounds().getWidth();
    
    float start = x / pixelPerSec;
    float end = (x + w) / pixelPerSec;

    event->setStartTimeSec(start);
    event->setEndTimeSec(end);
    
    event->updateAnnotationParam();

}

 // --------------------------------------------------
void WorkspaceWorkspace::getParametersFromAnnotation(IRNodeObject* target, IRNodeObject* annotation)
{
    float start = annotation->getStartTimeSec();
    float end = annotation->getEndTimeSec();
    
    target->setStartTimeSec(start);
    target->setEndTimeSec(end);
}
// --------------------------------------------------

void WorkspaceWorkspace::nodeObjectModifiedAction(IRNodeObject* obj)
{
    updateObjectOf(obj);
}

void WorkspaceWorkspace::nodeObjectModifiedNotification(IRNodeObject* event)
{
    calcEventTimeFromBounds(event);

}

void WorkspaceWorkspace::nodeObjectStartEndTimeChanged(IRNodeObject* event)
{
    event->updateAnnotationParam();
    adjustObjectWidthToLength(event);
    adjustStartPosition(event);
}

void WorkspaceWorkspace::nodeObjectDragged(IRNodeObject* event)
{
    if(isEditMode()) calcEventTimeFromBounds(event);

}

void WorkspaceWorkspace::nodeObjectDraggedCompleted(IRNodeObject* event)
{
    if(isEditMode()) calcEventTimeFromBounds(event);
}

void WorkspaceWorkspace::nodeObjectResizingStart(IRNodeObject* event)
{
    
}

void WorkspaceWorkspace::nodeObjectBeingResized(IRNodeObject* event)
{
    calcEventTimeFromBounds(event);
}

void WorkspaceWorkspace::nodeObjectResizingCompleted(IRNodeObject* event)
{
    calcEventTimeFromBounds(event);
}
// --------------------------------------------------

void WorkspaceWorkspace::updateObjectOf(IRNodeObject* obj)
{
    if(obj->hasEventComponent())
    {
        if(obj->getEventComponent() == nullptr) return;
        auto event = static_cast<IRNodeObject*>(obj->getEventComponent());
        adjustObjectWidthToLength(event);
        adjustStartPosition(event);
    }

}

// --------------------------------------------------

void WorkspaceWorkspace::command1Pressed()
{
    createTextObject();
}

void WorkspaceWorkspace::command2Pressed()
{
    createShapeObject();
}


void WorkspaceWorkspace::command3Pressed()
{
    createImageObject();
}


void WorkspaceWorkspace::setPlayPosition(double pos)
{
    this->currentPlayingPosition = pos;
    this->line.setPlayPosition(pos);
    repaint();
    onResized();
    
}
void WorkspaceWorkspace::setVideoLength(double length)
{
    this->videoLength = length;
    this->line.setVideoLength(length);
    this->measure.setLengthInSec(length);
    repaint();
}

void WorkspaceWorkspace::editModeChangedAction()
{
    if(isEditMode()) this->line.toBack();
    else this->line.toFront(true);
    
    this->line.addMouseListener(this, true);

}

void WorkspaceWorkspace::setMeasureHeight(int height)
{
    this->measureHeight = height;
    repaint();
}


// --------------------------------------------------

t_json WorkspaceWorkspace::getSaveData()
{
    auto workspaceData = makeSaveDataOfThis();
    
    t_json data = t_json::object({
        {"workspace", workspaceData}
    });

    return data;
}
void WorkspaceWorkspace::loadFromSaveData(t_json saveData)
{
    loadThisFromSaveData(saveData["workspace"]);

}
