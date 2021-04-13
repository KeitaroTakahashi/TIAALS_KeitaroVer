//
//  VideoAnnotaterWorkspace.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 19/03/2021.
//

#include "VideoAnnotaterWorkspace.hpp"

VideoAnnotaterWorkspace::VideoAnnotaterWorkspace(String title,
                                                 Rectangle<int> draggableMargin,
                                                 IRStr* str,
                                                 VideoAnnotaterBase* base,
                                                 int index) :
IRAnnotationWorkspace(title, draggableMargin, str, index),
VideoAnnotaterDelegate(base),
IRHeavyWeightComponent(this, "VideoAnnotaterWorkspace")
{
    setOpaque(false);
    
    setComponentAlpha(0.2);
    // set only width zoomable
    setZoomable(true, true);
    setCenterMargin(Rectangle<int>(0,0,0,0));
    
    setPreventCreateObjectByKeyCommand(true, "Please open a video file before creating annotations");
    
    this->controller.reset( new VideoAnnotaterWindowController(str) );
    this->controller->openVideoFileCallback = [this]{ openVideoFileAction(); };
    this->controller->videoSizePercentCallback = [this](int val){ videoSizePercentChangedAction(val); };

    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
    setBackgroundColour(Colours::transparentWhite);

    //bringThisToFront("VideoAnnotaterWorkspace");
}

VideoAnnotaterWorkspace::~VideoAnnotaterWorkspace()
{
    
}

void VideoAnnotaterWorkspace::onPaint(Graphics& g)
{
    //g.fillAll(Colour((uint8)0,(uint8)0,(uint8)255,(uint8)25));
    g.fillAll(Colours::transparentWhite);
}

void VideoAnnotaterWorkspace::onResized()
{
    /*
    auto b = getLocalBounds();
    
    int w = b.getWidth() * this->videoScale;
    int h = b.getHeight() * this->videoScale;
    
    int x = (b.getWidth() - w) / 2.0;
    int y = (b.getHeight() - h) / 2.0;
     */
    
}

void VideoAnnotaterWorkspace::openVideoFileAction()
{
    if(this->openVideoFileCallback != nullptr)
        this->openVideoFileCallback();
}

void VideoAnnotaterWorkspace::videoSizePercentChangedAction(int val)
{
    if(this->videoSizePercentCallback != nullptr)
        this->videoSizePercentCallback(val);
}

void VideoAnnotaterWorkspace::IRChangeListenerCallback(ChangeBroadcaster* source)
{
    
}

// ----------------------------------------

void VideoAnnotaterWorkspace::createTextObject()
{
    auto obj = IRObjectCreater<IRVNTextEditorObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);
    IRVNTextEditorObject* nodeObj = static_cast<IRVNTextEditorObject*>(obj);
    nodeObj->initialiseSetup("text...", Colour(uint8(50), uint8(50), uint8(50), uint8(150)));
    createNodeObjectOnWorkspace(nodeObj);
    
}
void VideoAnnotaterWorkspace::createShapeObject()
{
    auto obj = IRObjectCreater<IRVNShapeObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);
    IRVNShapeObject* nodeObj = static_cast<IRVNShapeObject*>(obj);
    createNodeObjectOnWorkspace(nodeObj);
}
void VideoAnnotaterWorkspace::createImageObject()
{
    auto obj = IRObjectCreater<IRVNImageViewerObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);

    IRVNImageViewerObject* nodeObj = static_cast<IRVNImageViewerObject*>(obj);
    createNodeObjectOnWorkspace(nodeObj);
}

void VideoAnnotaterWorkspace::createMediumTextObject()
{
    auto obj = IRObjectCreater<IRVNTextEditorObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);

    IRVNTextEditorObject* nodeObj = static_cast<IRVNTextEditorObject*>(obj);
    nodeObj->initialiseSetup("text...", Colour(uint8(50), uint8(50), uint8(50), uint8(150)), 12);
    nodeObj->setObjectSize(200, 200);
    createNodeObjectOnWorkspace(nodeObj);
}

void VideoAnnotaterWorkspace::createSmallTextObject()
{
    
    auto obj = IRObjectCreater<IRVNTextEditorObject>().create(this, getStr());
    obj->setStartTimeSec(this->currentPlayingPosition);
    obj->setEndTimeSec(this->currentPlayingPosition + 3);

    IRVNTextEditorObject* nodeObj = static_cast<IRVNTextEditorObject*>(obj);
    nodeObj->initialiseSetup("text...", Colour(uint8(50), uint8(50), uint8(50), uint8(150)), 9);
    nodeObj->setObjectSize(200, 200);
    createNodeObjectOnWorkspace(nodeObj);
    
}

// ----------------------------------------

void VideoAnnotaterWorkspace::createNodeObjectOnWorkspace(IRNodeObject* nodeObj)
{
    createObject(nodeObj);
       
    auto visibleSpace = getVisibleArea();
    nodeObj->setObjectCentredPosition(visibleSpace.getX() + visibleSpace.getWidth()/2,
                                      visibleSpace.getY() + visibleSpace.getHeight()/2);
}

// --------------------------------------------------

void VideoAnnotaterWorkspace::command1Pressed()
{
    if(this->isPreventCreateObjectByKeyCommand)
    {
        KLib().showErrorMessage(this->preventCreateObjectMessage);
        return;
    }
    
    createTextObject();
}

void VideoAnnotaterWorkspace::command2Pressed()
{
    if(this->isPreventCreateObjectByKeyCommand)
    {
        KLib().showErrorMessage(this->preventCreateObjectMessage);
        return;
    }
    createShapeObject();
}


void VideoAnnotaterWorkspace::command3Pressed()
{
    if(this->isPreventCreateObjectByKeyCommand)
    {
        KLib().showErrorMessage(this->preventCreateObjectMessage);
        return;
    }
    createImageObject();
}

void VideoAnnotaterWorkspace::command4Pressed()
{
    if(this->isPreventCreateObjectByKeyCommand)
    {
        KLib().showErrorMessage(this->preventCreateObjectMessage);
        return;
    }
    
    createMediumTextObject();
}

void VideoAnnotaterWorkspace::command5Pressed()
{
    if(this->isPreventCreateObjectByKeyCommand)
    {
        KLib().showErrorMessage(this->preventCreateObjectMessage);
        return;
    }
    
    createSmallTextObject();
}


void VideoAnnotaterWorkspace::annotationUpdateByPlayingPosition(double pos)
{
    this->currentPlayingPosition = pos;
    
    for(auto obj : getObjects())
    {
        auto beginTime = obj->getStartTimeSec();
        auto endTime = obj->getEndTimeSec();
        
        if(pos >= beginTime && endTime > pos)
        {
            if(obj->isActive())
            {
                obj->hide(true);
            }else{
                if(obj->isVisible()) obj->hide(false);
            }
        }else{
            if(obj->isVisible()) obj->hide(false);
        }
    }
}

// --------------------------------------------------

void VideoAnnotaterWorkspace::nodeObjectStartEndTimeChanged(IRNodeObject* obj)
{
    eventTimeCodeChangedAction(obj);
}
// --------------------------------------------------

t_json VideoAnnotaterWorkspace::getSaveData()
{
    return makeSaveDataOfThis();
    
}

void VideoAnnotaterWorkspace::loadFromSaveData(t_json saveData)
{
    loadThisFromSaveData(saveData);
    
    
}
// --------------------------------------------------
