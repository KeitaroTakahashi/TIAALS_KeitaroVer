//
//  IRVideoAnnotaterObject.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 19/03/2021.
//

#include "IRVideoAnnotaterObject.hpp"


IRVideoAnnotater::IRVideoAnnotater(Component* parent, IRStr* str, IRBoundType boundType) :
IRNodeObject(parent, "IRVideoAnnotater", str, boundType)

{
    
    std::cout << "IRVideoAnnotater oinitialized\n";
    this->UI.reset(new IRVideoAnnotaterObjectUI(str));
    addAndMakeVisible(this->UI.get());
    
    this->videoAnnotaterWindow.reset( new VideoAnnotaterWindow(str) );
    this->UI->setVideoAnnotaterWindow(this->videoAnnotaterWindow.get());
    
    this->controller.reset( new IRVideoAnnotaterController(str) );
    setObjController(this->controller.get());
    
    this->controller->getVideoAnnotaterController()->addChangeListener(this);
    this->controller->getArrangeController()->addChangeListener(this);
    
    setObjectBounds(0, 0, 160, 120);

}

IRVideoAnnotater::~IRVideoAnnotater()
{
    this->UI.reset();
    this->videoAnnotaterWindow.reset();
    this->controller.reset();
}
// ----------------------------------------

void IRVideoAnnotater::onResized()
{
    this->UI->setBounds(getLocalBounds().reduced(10));
}

void IRVideoAnnotater::paint(Graphics& g)
{
    //g.fillAll(Colours::blue);
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

// ----------------------------------------

IRNodeObject* IRVideoAnnotater::copyThisObject()
{
    IRVideoAnnotater* newObj = new IRVideoAnnotater(this->parent, getStr());
    return newObj;
}
// ----------------------------------------

void IRVideoAnnotater::IRChangeListenerCallback (ChangeBroadcaster* source)
{
    if(source == this->controller->getVideoAnnotaterController())
    {
        videoAnnotaterControllerChangeListener();
    }else if(source == this->controller->getArrangeController())
    {
        arrangeControllerChangeListener();
    }
}

// ----------------------------------------

void IRVideoAnnotater::videoAnnotaterControllerChangeListener()
{
    auto ctl = this->controller->getVideoAnnotaterController();
    
    auto status = ctl->getStatus();
    using s = VideoAnnotaterController::VideoAnnotaterControllerStatus;
    switch ( status )
    {
        case s::OpenVideoAnnotater:
            this->UI->openVideoAnnotater();
            break;
        default:
            break;
    }
}

void IRVideoAnnotater::arrangeControllerChangeListener()
{

}

// ----------------------------------------

t_json IRVideoAnnotater::saveThisToSaveData()
{
  
    auto annotater = this->videoAnnotaterWindow->getView();
    
    auto videoPlayerWorkspace = annotater->getVideoWorkspaceSaveData();
    auto sequencerWorkspace = annotater->getSequenceWorkspaceSaveData();
    
    t_json saveData = t_json::object({
        {"videoPlayerWorkspace", videoPlayerWorkspace},
        {"sequencerWorkspace", sequencerWorkspace}
    });
    
    t_json save = t_json::object({
        {"videoAnnotater", saveData}
    });
    
    return save;
    
    return t_json();
}

void IRVideoAnnotater::loadThisFromSaveData(t_json data)
{
    t_json s = data["videoAnnotater"];
    
    auto videoPlayerWorkspace = s["videoPlayerWorkspace"];
    auto sequencerWorkspace = s["sequencerWorkspace"];
    this->squareWorkspace_temporalbuf = sequencerWorkspace;
    
    auto annotater = this->videoAnnotaterWindow->getView();
    //annotater->videoLoadAndLoadSaveDataCompletedCallback = [this]{loadSaveDataAfterVideoLoadCompleted();};
    
    // load save data for video workspace including loading a video file
    annotater->loadVideoWorkspaceSaveData(videoPlayerWorkspace);
    annotater->loadSequenceWorkspaceSaveData(this->squareWorkspace_temporalbuf);

    // when a video and related data is loaded, then loadSaveDataAfterVideoLoadCompleted() is called to load sequencer and annotation objects.
}

void IRVideoAnnotater::loadSaveDataAfterVideoLoadCompleted()
{
    auto annotater = this->videoAnnotaterWindow->getView();
    //annotater->setRequestCreatingSequencerObject(false);
    std::cout << "IRVideoAnnotater::loadSaveDataAfterVideoLoadCompleted\n";
    annotater->loadSequenceWorkspaceSaveData(this->squareWorkspace_temporalbuf);
    //annotater->setRequestCreatingSequencerObject(true);

}

// ----------------------------------------
