//
//  IRAutomation.cpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#include "IRAutomationUI.hpp"

IRAutomationUI::IRAutomationUI(IRNodeObject* nodeObject, IRStr* str) : IRUIFoundation(nodeObject, str),
visibleArea(0,0,0,0),
playingLine(0,0,0,0)
{
    
    this->automation = std::make_shared<InteractiveAutomation>(nodeObject, str);
    
    this->automationView = std::make_shared<IRViewUI>(str,
                                                      this->automation.get(),
                                                      0, 40,
                                                      0, 40);
    addAndMakeVisible(this->automationView.get());
    
    this->automation->zoomInClickedCallback = [this]{ zoomInClicked(); };
    this->automation->zoomOutClickedCallback = [this]{ zoomOutClicked(); };
    this->automation->movableClickedCallback = [this](IRAutomation::movableStatus status){ movableClicked(status); };
    
    this->automationView->visibleAreaChangedCallback = [this](Rectangle<int> area){ visibleAreaChanged(area); };
    
    this->parent = nodeObject;
}


IRAutomationUI::~IRAutomationUI()
{
    if(this->audioData != nullptr)
    {
        this->audioData->getData()->removeListener(this);
        getFileManager().discardFilePtr(IRFileType::IRAUDIO, this->audioData, this->parent, this->file);
        
    }
}

// ==================================================

void IRAutomationUI::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.background);
    
    g.setColour (getStr()->SYSTEMCOLOUR.contents);
    //g.drawRoundedRectangle (area.toFloat(), 5.0f, 4.0f);
    g.drawRect(getLocalBounds().toFloat(), 1.0);
}

void IRAutomationUI::resized()
{
    int x = this->xMargin;
    int y = this->yMargin;
    int w = getWidth() - this->xMargin*2;
    int h = getHeight() - this->yMargin*2;
    
    int automationMarginY = 10;
    
    this->automationView->setBounds(x, y, w, h);
    this->automationView->setViewPosition(this->previousOffsetX, 0);
    this->automationView->setComponentBounds(0,
                                             0,
                                             w * this->automation_width_ratio,
                                             h - automationMarginY);
    
}
// ==================================================

void IRAutomationUI::zoomInClicked()
{
    this->automation_width_ratio *= 2;
    resized();
    this->automation->reCalcPos();
    setZoomInfo(juce::Point<float>(this->automation_width_ratio, 1.0));
    linkZoomInfo(nodeObject);
}

void IRAutomationUI::zoomOutClicked()
{
    this->automation_width_ratio /= 2;
    resized();
    this->automation->reCalcPos();
    setZoomInfo(juce::Point<float>(this->automation_width_ratio, 1.0));
    linkZoomInfo(nodeObject);
}

void IRAutomationUI::movableClicked(IRAutomation::movableStatus status)
{
    std::cout << "movableClicked : " << status << std::endl;
    
    switch(status)
    {
        case NOTMOVABLE:
            setMovable(false, false, false);
            break;
        case HORIZONTALMOVABLE:
            setMovable(true, false, true);
            break;
        case VERTICALMOVABLE:
            setMovable(true, true, false);
            break;
        case CROSSMOVABLE:
            setMovable(true, true, true);
            break;
        default:
            break;
            
    }
}

void IRAutomationUI::setMovable(bool movable, bool verticalMovable, bool horizontalMovable)
{
    
    Array<IRAutomationVertexComponent*> vs = this->automation->getVerteces();
    
    for(auto v : vs)
    {
        v->setMovable(movable, verticalMovable, horizontalMovable);
    }
    
    this->automation->setMovable(movable, verticalMovable, horizontalMovable);
    
}

// ==================================================

void IRAutomationUI::visibleAreaChanged(Rectangle<int> area)
{
    this->automation->setVisibleArea(area);
    this->automationView->setVisibleArea(area);
    
    this->visiblePos = area.getPosition();
    linkViewPosition(nodeObject);
    
    this->previousOffsetX = area.getX();
    
    this->visibleArea = area;
}

// ==================================================


void IRAutomationUI::demoData(int num)
{
    this->automation->demoData(num);
    //this->controller->setMovableStatus(IRAutomation::movableStatus::VERTICALMOVABLE);
}

void IRAutomationUI::setDescriptor(IRDescriptorStr* data)
{
    this->automation->setDescriptor(data);
}

void IRAutomationUI::openFile()
{
    
    FileChooser chooser("Select an image file...",
                        {},
                        "*.wav, *.aif, *.aiff, *.mp3");
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        this->file = file;
        auto p = file.getFullPathName();
        this->path = p;
        
        String pathToOpen;
        pathToOpen.swapWith(p);
        
        if(pathToOpen.isNotEmpty())
        {
            getFilePtr(this->file);
        }
    }
}

void IRAutomationUI::openFile(String path)
{
    if(path.isNotEmpty())
    {
        File f(path);
        this->file = f;
        this->path = path;
        
        if(f.exists())
        {
            getFilePtr(this->file);
        }
    }
}

void IRAutomationUI::getFilePtr(File file)
{
    
    std::cout << "getFilePtr\n";
    // set a callback function which is called when file load is completed.
    // get a pointer of the audio file
    std::function<void()> callback = [this]{fileImportCompleted();};
    
    // create random ID to identify the retrieved ptr.
    KeRandomStringGenerator a;
    this->randomIDForPtr = a.createStrings(10);
    
    getFileManager().getFilePtrWithCallBack(IRFileType::IRAUDIO,
                                             file,
                                             this->parent,
                                            this->randomIDForPtr,
                                             callback);
    std::cout << "notify!\n";

    // notify changes to IRProject to update IRFileInspecter
    this->parent->notifyNodeObjectModification();
    
}

void IRAutomationUI::fileImportCompleted()
{
    this->audioData = static_cast<DataAllocationManager<IRAudio>*>(getFileManager().getFileObjectAndRemoveFromBuffer(this->randomIDForPtr));
    
    this->audioData->getData()->addListener(this);
    
    this->status = AudioFileImportCompleted;
    sendChangeMessage();
    
    fileImportCompletedAction();
    
    std::cout << "fileImportCompleted!\n";

}
// --------------------------------------------------

void IRAutomationUI::linkZoomInfo(Component* comp)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        data->setZoomInfo(this->zoomInfo);
        data->linkZoomInOutWithSharedComponents(comp);
    }
    
    std::cout << "linkZoomInfo \n";
}

void IRAutomationUI::linkCurrentPlayedFrame(Component* comp)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        data->setCurrentPlayedFrame(this->getCurrentPlayedFrame());
        data->linkAudioPlaywithSharedComponents(comp);
    }
}


void IRAutomationUI::linkViewPosition(Component* comp)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        data->setViewPortPosition(this->visiblePos);
        data->linkViewPortPositionWithSharedComponents(comp);
    }
}
// --------------------------------------------------

void IRAutomationUI::zoomInOutOperatedFromComponent(IRAudio* obj)
{
    auto comp = obj->getEmittingComponent();
    // check if the emmiting component is not this object otherwise we will face on the infinitive loop
    if(comp != nodeObject)
    {
        
        setZoomInfo(obj->getZoomInfo());
        //std::cout << "zoominfo of "<< nodeObject << " = " << this->zoomInfo.getX() <<  " from " << comp << std::endl;
        
        this->automation_width_ratio = obj->getZoomInfo().getX();
        
        resized();
        
        this->status = zoomInfoShared;
        sendChangeMessage();
        
        
    }else{
        //std::cout <<"zoomInfo same \n";
    }
}

void IRAutomationUI::audioPlayOperatedFromComponent(IRAudio* obj)
{
    auto comp = obj->getEmittingComponent();
    // check if the emmiting component is not this object otherwise we will face on the infinitive loop
    if(comp != nodeObject)
    {
        setCurrentPlayedFrame(obj->getCurrentPlayedFrame());
        createPlayingLine(obj->getCurrentPlayedFrame());
        this->status = currentPlayedFrameShared;
        sendChangeMessage();
    }
}

void IRAutomationUI::viewPortPositionFromComponent(IRAudio *obj)
{
    
    std::cout << "IRAutomationUI : viewPortPositionFromComponent\n";
    auto comp = obj->getEmittingComponent();
    // check if the emmiting component is not this object otherwise we will face on the infinitive loop
    if(comp != nodeObject)
    {
        this->visiblePos = obj->getViewPortPosition();
        this->status = viewPosShared;
        sendChangeMessage();
        
        this->automationView->setViewPosition(this->visiblePos.getX(), this->visiblePos.getY());
    }
}


void IRAutomationUI::createPlayingLine(int64 currentFrame)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        double sampleRate = data->getSampleRate();
        int64 nframe = data->getNumSamples();
        
        int width = this->visibleArea.getWidth() * this->zoomInfo.getX();
        
        double ratio = (double)currentFrame / (double)nframe;
        
        int currentX = floor((double)width * ratio);
        
        //std::cout << "spectrogram w " << width << " currentX " << currentX << " visibleX = " << this->visibleArea.getX() << std::endl;
        
        if(currentX < this->visibleArea.getX() + this->visibleArea.getWidth())
        {
            this->playingLine = Rectangle<int>( currentX, 0, currentX, getHeight());
            
        }
        this->automation->setPlayingLine(this->playingLine);
        //repaint();
        
    }
}
