//
//  VideoAnnotaterView.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 22/03/2021.
//

#include "VideoAnnotaterView.hpp"

VideoAnnotaterView::VideoAnnotaterView(IRStr* str) : IRStrComponent(str),
transport(str, this)
{
    // create new IRStr for this view
    initialize(str);
    
    this->delegate.reset(new VideoAnnotaterDelegate(this));
    setWantsKeyboardFocus(true);

    addKeyListener(this);
    createViews();

}

VideoAnnotaterView::~VideoAnnotaterView()
{
    this->videoPlayerView.reset();
    this->delegate.reset();
}

void VideoAnnotaterView::resized()
{
    initializeArea(false);
    
    if(this->videoPlayerView.get() != nullptr){
        this->videoPlayerView->setBounds(this->videoPlayerArea);
    }
    
    if(this->controllerView.get() != nullptr)
        this->controllerView->setBounds(this->controllerArea);
    
    if(this->transportView.get() != nullptr)
        this->transportView->setBounds(this->transportArea);
    
    if(this->workspaceView.get() != nullptr)
        this->workspaceView->setBounds(this->workspaceArea);
    
}

void VideoAnnotaterView::paint(Graphics& g)
{
    g.fillAll(this->str->SYSTEMCOLOUR.fundamental);
}


void VideoAnnotaterView::initializeArea(bool setInitialBounds)
{
    int marginX = 10;
    int marginY = 10;
    
    // control bar width
    int ctlw = this->str->parentStr->ControlBarWidth;
    //getStr()->ControlBarWidth;
    int transportH = 80;
    
    int x = marginX;
    int y = marginY;
    
    int leftArea = getWidth() - marginX * 3 - ctlw;
    int videoHeight = getHeight() * 0.6;

    std::cout << "videoHeight = " << videoHeight << std::endl;
    
    this->videoPlayerArea = Rectangle<int>(x, y, leftArea, videoHeight);
    this->videoPlayerRect = Rectangle<int>(30, 30, leftArea - 60, videoHeight - 60);
    y += this->videoPlayerArea.getHeight() + marginY;
    this->transportArea = Rectangle<int>(x, y, leftArea, transportH);
    y += this->transportArea.getHeight() + marginY;
    this->workspaceArea = Rectangle<int>(x, y, leftArea, getHeight() - y - marginY);
    
    
    x = marginX * 2 + this->videoPlayerArea.getWidth();
    y = marginY;
    this->controllerArea = Rectangle<int>(x, y, ctlw, getHeight() - marginY * 2);
    
    // expected to execute this once when this is created and the bounds is set
    // otherwise, workspace needs to use ratio to be changed its size
    if(setInitialBounds)
    {
        if(this->workspaceView.get() != nullptr)
            this->workspaceView->setInitialBoundsOfWorkspace(this->workspaceArea);
        if(this->videoPlayerView.get() != nullptr)
            this->videoPlayerView->setInitialBoundsOfWorkspace(this->videoPlayerArea);
    }
        
}

void VideoAnnotaterView::createViews()
{
    this->videoPlayerView.reset( new VideoPlayerView(this->str.get(), this) );
    addAndMakeVisible(this->videoPlayerView.get());
    this->videoPlayerView->nothingSelectedAction = [this] { nothingSelectedAction(); };
    this->videoPlayerView->nodeObjectGetFocusedAction = [this] (IRNodeObject* focusedObj) { nodeObjectGetFocusedAction(focusedObj); };
    this->videoPlayerView->videoLoadCompletedCallback = [this]{ videoLoadCompletedAction(); };
    this->videoPlayerView->nodeObjectCreatedAction = [this](IRNodeObject* obj){ nodeObjectCreatedAction(obj);  };
    
    this->controllerView.reset(new ControllerView(this->str.get()));
    addAndMakeVisible(this->controllerView.get());
    
    this->transportView.reset(new TransportView(this->str.get()));
    addAndMakeVisible(this->transportView.get());
    this->transportView->setVideoTransport(&this->transport);
    this->transport.addChangeListener(this);
    
    this->workspaceView.reset(new WorkspaceView(this->str.get(), this));
    addAndMakeVisible(this->workspaceView.get());
    this->workspaceView->nothingSelectedAction = [this] { nothingSelectedAction(); };
    this->workspaceView->nodeObjectGetFocusedAction = [this] (IRNodeObject* focusedObj) { nodeObjectGetFocusedAction(focusedObj); };


}

void VideoAnnotaterView::nothingSelectedAction()
{
    if(this->videoPlayerView.get() != nullptr)
        setController(this->videoPlayerView->getController());
}

void VideoAnnotaterView::nodeObjectCreatedAction(IRNodeObject* obj)
{
    
    this->workspaceView->getWorkspace()->createNodeObjectFromAnnotation(obj);
}

void VideoAnnotaterView::nodeObjectGetFocusedAction(IRNodeObject* focusedObj)
{
    if(this->videoPlayerView.get() != nullptr)
    {
        if(focusedObj != nullptr)
        {
            auto ctl = focusedObj->getObjController();
            if(ctl != nullptr) setController(ctl);
        }else{
            
        }
    }
}

void VideoAnnotaterView::setController(IRObjectController* controller)
{
    if(this->controllerView.get() != nullptr)
    {
        this->controllerView->setController(controller);
    }
}

void VideoAnnotaterView::removeController()
{
    if(this->controllerView.get() != nullptr)
    {
        this->controllerView->removeController();
    }
}

bool VideoAnnotaterView::keyPressed (const KeyPress& key, Component* originatingComponent)
{
    std::cout << "VideoAnnotaterView " << key.getKeyCode() << " : " << key.getTextDescription() << ", " << key.getTextCharacter() <<   std::endl;
    
   
    if(key.getTextDescription() == "command + E")
    {
        setEditMode(!isEditMode());
        return true;
    }
    
     /*
    if(key.getTextDescription() == "command + 2")
    {
        
        return true;
    }
    if(key.getTextDescription() == "command + 3")
    {
        
        return true;
    }*/
    
    return false;
}

// ----------------------------------------

void VideoAnnotaterView::setEditMode(bool flag)
{
    this->videoPlayerView->getWorkspace()->setEditMode(flag);
    this->workspaceView->getWorkspace()->setEditMode(flag);
}

bool VideoAnnotaterView::isEditMode() const
{
    return this->videoPlayerView->getWorkspace()->isEditMode();
}

// ----------------------------------------

void VideoAnnotaterView::changeListenerCallback(ChangeBroadcaster* source)
{
    if(source == &this->transport)
    {
        transportChangeCallback();
    }
}

void VideoAnnotaterView::transportChangeCallback()
{
    auto status = this->transport.getStatus();
    
    using s = VideoTransportComponent::VideoTransportStatus;
    switch (status)
    {
        case s::OpenVideoFile:
            initializeAndOpenFile();
            break;
        case s::OpenAnnotationFile:
            break;
        case s::SaveAnnotationFile:
            break;
        case s::addEventButtonClicked:
            //addEventButtonAction();
            break;
        case s::deleteEventButtonClicked:
            //deleteEventButtonAction();
            break;
        case s::play:
            playAction();
            break;
        case s::stop:
            stopAction();
            break;
        case s::playPositionChanged:
            playPositionChangedBySliderAction();
            break;
        case s::videoSegmentMinChanged:
            // DO NOT CALL ANY METHOD NEEDS TO BE SYNCRONIZED
            //videoSegmentSliderMinChangedAction();
            break;
        case s::videoSegmentMaxChanged:
            // DO NOT CALL ANY METHOD NEEDS TO BE SYNCRONIZED
            //videoSegmentSliderMaxChangedAction();
            break;
        default:
            break;
    }
}

void VideoAnnotaterView::initializeAndOpenFile()
{
    
}
void VideoAnnotaterView::playAction()
{
    this->videoPlayerView->playVideo();
}
void VideoAnnotaterView::stopAction()
{
    this->videoPlayerView->stopVideo();
}
void VideoAnnotaterView::playPositionChangedBySliderAction()
{
    float pos = this->transport.getPlayPosition();
    this->videoPlayerView->setPlayPosition(pos);
    this->workspaceView->setPlayPosition(pos);
}

void VideoAnnotaterView::videoLoadCompletedAction()
{
    this->transport.setVideoLengthInSec(this->videoPlayerView->getVideoLength());
    this->transport.setCurrentPlayingPosition(0);
    this->workspaceView->setVideoLength(this->videoPlayerView->getVideoLength());
}

// ----------------------------------------
// base
void VideoAnnotaterView::eventModifiedAction(Component* modifiedEvent)
{}
void VideoAnnotaterView::eventSelectedAction(Component* selectedEvent) {}
void VideoAnnotaterView::newEventCreatedAction(Component* selectedEvent) {}
void VideoAnnotaterView::eventTimeCodeChangedAction(Component* changedEvent)
{

}
void VideoAnnotaterView::updateAnnotation() {}
void VideoAnnotaterView::showEventPosition(Component* event) {}
void VideoAnnotaterView::eventActivationChanged(Component* changedEvent) {}

void VideoAnnotaterView::playPositionUpdated(float sec)
{
    this->transport.setCurrentPlayingPositionLabel(sec);
}

void VideoAnnotaterView::videoSegmentChanged(float begin, float end)
{
    this->videoPlayerView->setVideoRange(begin, end);
}
// ----------------------------------------

void VideoAnnotaterView::initialize(IRStr* parentStr)
{
    this->str.reset(new IRStr());
    this->str->projectOwner = parentStr->projectOwner;
    this->str->parentStr = parentStr;
    
    this->str->setKeyListener(this);
    this->str->setMouseListener(this);
    this->str->projectName = "Video Annotater";
    this->str->SYSTEMCOLOUR = IR::darkGraySet();
    this->str->ICONBANK = parentStr->ICONBANK;
    this->str->SYSTEMCOLOUR = parentStr->SYSTEMCOLOUR;
    
    Font f;
    this->str->fontFamilyList = f.findAllTypefaceNames();
}

// ----------------------------------------

t_json VideoAnnotaterView::getVideoWorkspaceSaveData()
{
    return this->videoPlayerView->getSaveData();
}

void VideoAnnotaterView::loadVideoWorkspaceSaveData(t_json saveData)
{
    this->videoPlayerView->loadFromSaveData(saveData);
}

t_json VideoAnnotaterView::getSequenceWorkspaceSaveData()
{
    return this->workspaceView->getWorkspace()->getSaveData();
}
void VideoAnnotaterView::loadSequenceWorkspaceSaveData(t_json saveData)
{
    this->workspaceView->getWorkspace()->loadFromSaveData(saveData);
}
