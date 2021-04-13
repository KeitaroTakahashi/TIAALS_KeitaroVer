//
//  IRMainSpace.cpp
//  IRiMaS
//
//  Created by Keitaro on 27/08/2019.
//

#include "IRMainSpace.hpp"

IRMainSpace::IRMainSpace(IRStr* str)
{
    this->ir_str = str;
    this->referenceImage = getReferenceOfIndex(1);
    
    
}

IRMainSpace::~IRMainSpace()
{
    for(auto space : this->workspaces )
    {
        delete space;
    }
    
}
//==================================================

void IRMainSpace::paint(Graphics& g)
{
    
    g.fillAll(this->ir_str->SYSTEMCOLOUR.fundamental);
    
    if(this->workspaces.size() == 0)
    {
        g.drawImage(this->referenceImage, getLocalBounds().toFloat());
    }
}

void IRMainSpace::resized()
{
    
    /*
    for(auto space : this->workspaces)
    {
        if(space->isFullScreenMode())
            space->setOriginalBounds(Desktop::getInstance().getDisplays().getMainDisplay().userArea);
        else
            space->setOriginalBounds(getLocalBounds());
    }*/
}
//==================================================

void IRMainSpace::changeListenerCallback (ChangeBroadcaster* source)
{
    
    
}

//==================================================

void IRMainSpace::updateAnimationFrame()
{
    
}

// ==================================================
// WORKSPACE
// ==================================================

void IRMainSpace::createNewWorkspace()
{
    std::cout << "create IRWorkspace\n";
    String title = this->ir_str->projectName + "_" + String(this->workspaces.size() + 1);
    Rectangle<int> r (-1000, -1000, 1000, 1000);
    
    int index = (int)this->workspaces.size() + 1; // start from 1
    IRWorkspace* space = new IRWorkspace(title, r, this->ir_str, index);
    space->addListener(this);
    // register key and mouse listeners if necessary
    space->registerKeyListener(this->ir_str->key);
    space->registerMouseListener(this->ir_str->mouse);
    addKeyListener(space);
    this->workspaces.push_back(space);
    this->mixer.addAudioSource(&space->getMixer());
    addAndMakeVisibleWorkspace(space);

    // call after added
    space->setUserDefinedRatio(Rectangle<float>(0,0,8,6));

    // update a top workspace
    setTopWorkspace(space);
    // --------------------------------------------------

    // call listener's function
    callnewWorkspaceCreated(space);
    
}


void IRMainSpace::createNewWorkspace(int sortIndex)
{
    std::cout << "create IRWorkspace : " << sortIndex << std::endl;
    String title = this->ir_str->projectName + "_" + String(this->workspaces.size() + 1);
    Rectangle<int> r (-1000, -1000, 1000, 1000);
    
    //int index = (int)this->workspaces.size();
    int index = sortIndex;
    IRWorkspace* space = new IRWorkspace(title, r, this->ir_str, index);
    space->setIndex(sortIndex);
    space->addListener(this);
    // register key and mouse listeners if necessary
    space->registerKeyListener(this->ir_str->key);
    space->registerMouseListener(this->ir_str->mouse);
    addKeyListener(space);
    
    this->workspaces.push_back(space);
    this->mixer.addAudioSource(&space->getMixer());
    
    addAndMakeVisibleWorkspace(space);
    // update a top workspace
    setTopWorkspace(space);
    // --------------------------------------------------

    // call listener's function
    callnewWorkspaceCreated(space);
    
}


void IRMainSpace::addAndMakeVisibleWorkspace(IRWorkspace* space)
{
    addAndMakeVisible(space);
}

void IRMainSpace::deleteWorkspace(IRWorkspace* space)
{
    
    std::cout << "IRMainSpace::deleteWorkspace" << std::endl;
    callWorkspaceWillDeleted(space);
    
    this->mixer.removeSource(&space->getMixer());
    removeChildComponent(space);
    
    this->topWorkspace = nullptr;
    auto it = std::find(this->workspaces.begin(), this->workspaces.end(), space);
    if(it != this->workspaces.end())
    {
        this->workspaces.erase(it);
        delete space;
    }
    
    callWorkspaceHasDeleted();
}

void IRMainSpace::fullScreenWorkspace()
{
    auto w = this->topWorkspace;
    if(w != nullptr)
    {
        //first remove all fullscreen workspace
        resetAllFullscreenWorkspace(w);
        
        bool flag = w->isFullScreenMode();
        //switch full screen mode
        fullScreenWorkspace(w, !flag);
    }
}


void IRMainSpace::fullScreenWorkspace(IRWorkspace* space, bool isFullScreen)
{
    space->setFullScreenMode(isFullScreen);

    if(isFullScreen)
    {
        space->addToDesktop(0);
        
    }else{
        addAndMakeVisibleWorkspace(space);
    }
    
    // --------------------------------------------------
    // resize before bring OopenGLContext to front
    resized();
    space->toFront(true);
    // --------------------------------------------------
    
}

void IRMainSpace::moveToHigherWorkspace()
{
    auto w = this->getTopWorkspace();
    if(w != nullptr)
    {
        int index = w->getIndex();
        if(index >= this->workspaces.size()) return;
        setTopWorkspace(this->workspaces[index]);
        
    }
}

void IRMainSpace::moveToLowerWorkspace()
{
    auto w = this->getTopWorkspace();
    if(w != nullptr)
    {
        int index = w->getIndex();
        if(index <= 1) return;
        setTopWorkspace(this->workspaces[index-2]);

        
    }
}

void IRMainSpace::resetAllFullscreenWorkspace(IRWorkspace* exception)
{
    for(auto ws : this->workspaces)
    {
        if(ws != exception)
        {
            if(ws->isFullScreenMode())
            {
                fullScreenWorkspace(ws, false);
            }
        }
    }
}


void IRMainSpace::setTopWorkspace(IRWorkspace* topSpace)
{
    
    for(auto w : this->workspaces)
    {
        w->setWantsKeyboardFocus(false);
        removeKeyListener(w);
        w->setTopWorkspace(false);
        removeChildComponent(w);
        
    }
    
    // search if workspaces has the received IRWorkspace.
    auto it = std::find(this->workspaces.begin(), this->workspaces.end(), topSpace);
    if(it != this->workspaces.end())
    {
        
        addAndMakeVisible(topSpace);
        
        this->topWorkspace = topSpace;
        this->topWorkspace->setTopWorkspace(true);
        // resize before bring OpenGLContext to front
        resized();

        this->topWorkspace->toFront(true);
        this->ir_str->TopWorkspace = this->topWorkspace;
        
        giveKeyboardFocusOnTopWorkspace();
        
    }else{
        std::cout << "ERROR : IRMainSpace setTopWorkspace : Could not find received topSpace of " << topSpace << std::endl;
    }
}

void IRMainSpace::giveKeyboardFocusOnTopWorkspace()
{
    
    if(this->topWorkspace == nullptr) return;
    
    for(auto w : this->workspaces)
    {
        w->setWantsKeyboardFocus(false);
        removeKeyListener(w);
    }
    
    this->topWorkspace->setWantsKeyboardFocus(true);
    addKeyListener(this->topWorkspace);
    this->topWorkspace->toFront(true);
}



void IRMainSpace::nodeObjectSelectionChange(IRNodeObject* obj)
{
    
    callNodeObjectSelectionChange(obj);
  
}

void IRMainSpace::nodeObjectGetFocused(IRNodeObject* obj)
{
    
    std::cout << "IRMainSpace::nodeObjectGetFocused\n";
    callNodeObjectGetFocused(obj);
}

void IRMainSpace::nothingSelected()
{
    callNothingSelected();
}

void IRMainSpace::editModeChanged(IRWorkspaceComponent* changedSpace)
{
    auto space = static_cast<IRWorkspace*> (changedSpace);
    callWorkspaceEditModeChanged(space);
}

void IRMainSpace::setWorkspaceGrid(int grid)
{
    if(this->topWorkspace != nullptr)
        this->topWorkspace->setGridValue(grid);
}

void IRMainSpace::setWorkspaceGuid(int guid)
{
    if(this->topWorkspace != nullptr)
        this->topWorkspace->setGuidValue(guid);
}

// ==================================================
// MOUSE EVENT
// ==================================================
void IRMainSpace::mouseDown(const MouseEvent& e)
{
    std::cout << "MainSpace mouseDown\n";
}

void IRMainSpace::mouseMagnify(const MouseEvent& e, float scaleFactor)
{

    if(this->topWorkspace != nullptr)
        this->topWorkspace->setMouseMagnify(e, scaleFactor);
}

void IRMainSpace::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& w)
{
    if(this->topWorkspace != nullptr)
        this->topWorkspace->setMouseWheelMove(e, w);
    
}
// ==================================================
// SYSTEM
// ==================================================

// Audio
void IRMainSpace::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    
    this->mixer.getAudioSource().prepareToPlay(samplesPerBlockExpected, sampleRate);
}


void IRMainSpace::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    this->mixer.getAudioSource().getNextAudioBlock(bufferToFill);
}


void IRMainSpace::releaseResources()
{
    this->mixer.getAudioSource().releaseResources();
}
// ==================================================
//Listener

void IRMainSpace::callNodeObjectSelectionChange(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectSelectionChange(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::callNodeObjectGetFocused(IRNodeObject* obj)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [obj](Listener& l){ l.nodeObjectGetFocused(obj); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::callnewWorkspaceCreated(IRWorkspace* space)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [space](Listener& l){ l.newWorkspaceCreated(space); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::callWorkspaceWillDeleted(IRWorkspace* space)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [space](Listener& l){ l.workspaceWillDeleted(space); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::callWorkspaceHasDeleted()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [](Listener& l){ l.workspaceHasDeleted(); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::callWorkspaceEditModeChanged(IRWorkspace* space)
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [space](Listener& l){ l.workspaceEditModeChanged(space); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::callNothingSelected()
{
    Component::BailOutChecker checker(this);
    // check if the objects are not deleted, if deleted, return
    if(checker.shouldBailOut()) return;
    this->listeners.callChecked(checker, [this](Listener& l){ l.nothingSelected(); });
    //check again
    if(checker.shouldBailOut()) return;
}

void IRMainSpace::addListener(Listener* newListener)
{
    this->listeners.add(newListener);
}


void IRMainSpace::removeListener(Listener* listener)
{
    this->listeners.remove(listener);
}

// ==================================================

Image IRMainSpace::loadImage(String url)
{
    File file = File(IRPath().getAppContentsDirectoryPath() + url);
    return ImageFileFormat::loadFrom(file);
}

Image IRMainSpace::getReferenceOfIndex(int index)
{
#if JUCE_MAC
    String url = "/Contents/Resources/materials/Images/Reference/TiAALS_Reference" + String(index) + ".png";
    return loadImage(url);
#elif JUCE_IOS
    String url = "/materials/Images/Reference/TiAALS_Reference" + String(index) + ".png";
    return loadImage(url);
#endif
    
    
}

// ==================================================

void IRMainSpace::exportTopWorkspaceToImage()
{
    if(this->topWorkspace != nullptr)
    {
        this->topWorkspace->exportThisToPNG();
    }
}
