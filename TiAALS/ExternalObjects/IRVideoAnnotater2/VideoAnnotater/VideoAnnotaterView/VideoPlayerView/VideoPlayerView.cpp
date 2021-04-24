//
//  VideoPlayerView.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#include "VideoPlayerView.hpp"

VideoPlayerView::VideoPlayerView(IRStr* str, VideoAnnotaterBase* base) : IRStrComponent(str),
VideoAnnotaterDelegate(base),
videoPlayer(false), empty(str)
{
    setFps(17);
    
    Rectangle<int> r (0, 0, 0, 0);
    
    addAndMakeVisible(this->empty);
    
    addAndMakeVisible(this->videoPlayer);
    this->videoPlayer.videoLoadCompleted = [this] { videoLoadCompleteAction(); };

    this->annotationWorkspace.reset( new VideoAnnotaterWorkspace("Video Annotater",
                                                         r,
                                                         str,
                                                         base) );
    addAndMakeVisible(this->annotationWorkspace.get());
    this->annotationWorkspace->addListener(this);
    this->annotationWorkspace->openVideoFileCallback = [this] { openVideoFile(); };
    this->annotationWorkspace->videoSizePercentCallback = [this] (int val) { videoSizePercentChangedAction(val); };

    // default video bounds ratio relative to workspace bounds
    setVideoBoundsScale(0.7);
}

VideoPlayerView::~VideoPlayerView()
{
    this->annotationWorkspace.reset();
}

// ---------------------------------------------

void VideoPlayerView::resized()
{
    
    //this->annotationWorkspace->setBoundsAndCalculateRatio(getLocalBounds());

    auto b = getLocalBounds();
    
    
    int w = b.getWidth() * this->videoScale;
    int h = b.getHeight() * this->videoScale;
    
    int x = (b.getWidth() - w) / 2.0;
    int y = (b.getHeight() - h) / 2.0;
    
    this->videoPlayer.setBounds(x, y, w, h);
    //adjusted bound size
    auto vb = this->videoPlayer.getVideoBounds();
    // annotation workspace
    auto ab = this->annotationWorkspace->getOriginalBounds();
    
    if(vb.getWidth() == 0)
    {
        ab = getLocalBounds();
        setInitialBoundsOfWorkspace(ab);
    }else{
    
        float ratioW = (float)vb.getWidth() / ab.getWidth();
        if(ratioW == 0.0) ratioW = 1.0;

        ratioW /= this->videoScale;

        x = (b.getWidth() - (float)ab.getWidth() * ratioW) / 2.0;
        y = (b.getHeight() - (float)ab.getHeight() * ratioW) / 2.0;
        this->annotationWorkspace->setZoomRatio(x, y, ratioW);
    }

    this->empty.setBounds(this->annotationWorkspace->getBounds());

    //this->annotationWorkspace->setDraggableMarginWithInThisComponent();
    
}

void VideoPlayerView::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}

// ---------------------------------------------

void VideoPlayerView::nothingSelected()
{
    if(this->nothingSelectedAction != nullptr)
        this->nothingSelectedAction();
    
}

void VideoPlayerView::nodeObjectCreated(IRNodeObject* obj)
{
    if(this->requestCreatingSequencerObject)
    {
        std::cout << "VideoPlayerView::nodeObjectCreated\n";
        if(this->nodeObjectCreatedAction != nullptr)
            this->nodeObjectCreatedAction(obj);
    }
}


void VideoPlayerView::nodeObjectGetFocused(IRNodeObject* obj)
{
    if(this->nodeObjectGetFocusedAction != nullptr)
        this->nodeObjectGetFocusedAction(obj);
}

// ---------------------------------------------

void VideoPlayerView::editModeChanged(IRWorkspaceComponent* changedSpace)
{
    
}
// ---------------------------------------------

void VideoPlayerView::setVideoBoundsScale(float scale)
{
    if(scale > 1.0) scale = 1.0;
    this->videoScale = scale;
    
    rescaleVideoAndAdjustWorkspace(scale);
}

void VideoPlayerView::openFile(File file, bool isCallback)
{
    auto url = URL (file);
    this->videoFilePath = file.getFullPathName();
    std::cout << "VideoPlayerView::openFile : " << url.getFileName() << std::endl;
    
    if(!file.exists())
    {
        KLib().showErrorMessage("Could not find a file " + file.getFullPathName());
        return;
    }
    
    //this->videoPlayer.loadVideo(this->videoFilePath, isCallback);
    this->videoPlayer.loadVideo(url, isCallback);

    
}


void VideoPlayerView::openFile()
{
    FileChooser chooser("Select an video file to play...",
                        {},
                        "*.mov, *.mp4, *.m4v");
    
    FilenameComponent co {"movie", {}, true, false, false, "*", {}, "(choose a video file to play)"};
    
    if(chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        auto path = file.getFullPathName();
        auto url = URL (file);
        
        std::cout << url.getFileName() << std::endl;
        this->videoFilePath = path;
        //this->videoPlayer.loadVideo(this->videoFilePath);
        this->videoPlayer.loadVideo(url);

    }
}

void VideoPlayerView::openVideoFile()
{
    openFile();
}

void VideoPlayerView::videoSizePercentChangedAction(int val)
{
    setVideoBoundsScale((float)val/100.0);
    resized();
    
}

void VideoPlayerView::videoLoadCompleteAction()
{
    this->annotationWorkspace->setPreventCreateObjectByKeyCommand(false, "");
    
    Rectangle<int> vb = this->videoPlayer.getVideoBounds();
    
    setInitialBoundsOfWorkspace(vb);
    
    resized();


    std::cout << "video load completed " << vb.getWidth() << ", " << vb.getHeight() << std::endl;
    
   if(this->videoLoadCompletedCallback != nullptr)
       this->videoLoadCompletedCallback();
    
    this->annotationWorkspace->bringThisToFront("VideoAnnotaterWorkspace");

    resized();
    repaint();

    
    // if this method is called during loading the savedata, then operate subsequent process
    if(this->loadingSaveData)
    {
        loadRestSaveDataAfterVideoLoaded();
        this->loadingSaveData = false;
    }
    
}

// --------------------------------------------------
void VideoPlayerView::setPlayPosition(double position)
{
    this->videoPlayer.setPlayPosition(position);
    this->annotationWorkspace->annotationUpdateByPlayingPosition(position);
}

double VideoPlayerView::getPlayPosition()
{
    return this->videoPlayer.getPlayPosition();
}

void VideoPlayerView::setAudioVolume(float newVolume)
{
    this->videoPlayer.setAudioVolume(newVolume);
}

float VideoPlayerView::getAudioVolume()
{
    return this->videoPlayer.getAudioVolume();
}

 double VideoPlayerView::getVideoLength()
{
    return this->videoPlayer.getVideoLength();
}

void VideoPlayerView::setVideoRange(float begin, float end)
{
    
    stopVideo();
    
    this->videoBegin = begin;
    this->videoEnd = end;


    if(getPlayPosition() > end)
    {
        setPlayPosition(end);
    }else{
        setPlayPosition(begin);
    }
    
    
    
}

Point<float> VideoPlayerView::getVideoRange()
{
    return Point<float>(this->videoBegin, this->videoEnd);
}
// --------------------------------------------------

void VideoPlayerView::playVideo()
{
    // if current playing position exceeds the end position then do not play
    if(this->videoPlayer.getPlayPosition() >= this->videoEnd)
    {
        setPlayPosition(this->videoEnd);
        return;
    }
    // video needs to begin from the video begin time
    if(this->videoPlayer.getPlayPosition() < this->videoBegin)
        setPlayPosition(this->videoBegin);
    
    
    startAnimation();
    this->videoPlayer.play();
}
void VideoPlayerView::stopVideo()
{
    stopAnimation();
    this->videoPlayer.stop();
}
// --------------------------------------------------


// ---------------------------------------------

// ---------------------------------------------
void VideoPlayerView::setInitialBoundsOfWorkspace(Rectangle<int> initialBounds)
{
    
    this->annotationWorkspace->setUserDefinedRatio(Rectangle<float>(0,0, (float)initialBounds.getWidth() / 100.0, (float)initialBounds.getHeight() / 100.0));
    this->annotationWorkspace->setZoomRatio(1.0);
    this->annotationWorkspace->setMinSize(10, 10);

}

void VideoPlayerView::setInitialBoundsOfWorkspace(Rectangle<float> initialBounds)
{
    
    this->annotationWorkspace->setUserDefinedRatio(Rectangle<float>(initialBounds.getX(),
                                                                    initialBounds.getY(),
                                                                    initialBounds.getWidth() / 100.0,
                                                                    initialBounds.getHeight() / 100.0));
    //this->annotationWorkspace->setZoomRatio(1.0);
    this->annotationWorkspace->setMinSize(10, 10);

}

void VideoPlayerView::rescaleVideoAndAdjustWorkspace(float scale)
{
    auto b = getLocalBounds();
    int w = b.getWidth() * this->videoScale;
    int h = b.getHeight() * this->videoScale;
    
    int x = (b.getWidth() - w) / 2.0;
    int y = (b.getHeight() - h) / 2.0;
    
    this->videoPlayer.setBounds(x, y, w, h);
    //adjusted bound size
    auto vb = this->videoPlayer.getVideoBounds();
    
    if(vb.getWidth() == 0) return;
    
    b = this->annotationWorkspace->getOriginalBounds();
    std::cout << "originalBounds = " << b.getWidth() << ", " << b.getHeight() << std::endl;
}

// --------------------------------------------------

void VideoPlayerView::createSequencerObjectFromAnnotation(IRNodeObject* obj)
{
    
}


void VideoPlayerView::updateAnimationFrame()
{
    float pos = this->videoPlayer.getPlayPosition();
    
    if(pos >= this->videoEnd)
    {
        setPlayPosition(this->videoEnd);
        stopVideo();
    }
    
    setCurrentVideoPosition(pos);
}
// --------------------------------------------------


t_json VideoPlayerView::getSaveData()
{
    //auto ws = getWorkspace()->getSaveData();
    
    int videoSizePercent = getWorkspace()->getController()->getVideoAnnotaterController()->getVideoSizePercent();
    
    Rectangle<int> vb = this->videoPlayer.getVideoBounds();
    t_json data = t_json::object({
       // {"workspace", ws},
        {"videoFilePath", this->videoFilePath.toStdString()},
        {"videoSizePercent", videoSizePercent},
    });
    
    return data;

}
void VideoPlayerView::loadFromSaveData(t_json saveData)
{
    
    // First, load video file and get video information
    // Second, load sequencer objects and create corresponding annotations
    
    
    this->videoFilePath = saveData["videoFilePath"].string_value();
    int videoSizePercent = saveData["videoSizePercent"].int_value();
    this->temporarlVideoSizePercent = videoSizePercent;
        
    this->loadingSaveData = true;
    
    // open file asyncrhonically
    openFile(File(this->videoFilePath), true);
    
    // wait until video load completed

}
void VideoPlayerView::loadRestSaveDataAfterVideoLoaded()
{
    getWorkspace()->getController()->getVideoAnnotaterController()->setVideoSizePercent(this->temporarlVideoSizePercent);
    videoSizePercentChangedAction(this->temporarlVideoSizePercent);
}
