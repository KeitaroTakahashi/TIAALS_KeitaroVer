
#include "IRWaveform.hpp"

IRWaveform::IRWaveform(IRNodeObject* parent, IRStr* str) :
IRUIAudioFoundation(parent, str),
thumbnailCache(5),
thumbnail(512, formatManager, thumbnailCache),
playingLine(0,0,0,0),
visiblePos(juce::Point<int>(0,0))
{
    this->parent = parent;
    // We need to add this to the ChangeListener of thumbnail to repaint() waveform
    // this process is important when thumbnail calls setSource() and replace the wavedara and paint it, otherwise it does not complete painting.
    // in the changeListenerCallback(), we need to call repaint()
    this->thumbnail.addChangeListener(this);
    this->formatManager.registerBasicFormats();
    
    addAndMakeVisible(&this->openButton);
    this->openButton.setButtonText("open audio");
    
    //this->openButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.fundamental);
    this->setEnabled(true);
    this->openButton.onClick = [this]{ openFile(); };
    
    this->player.reset( new SoundPlayerClass() );
    this->player->addChangeListener(this);
    
    setFps(17);
}


IRWaveform::~IRWaveform()
{
    this->player.reset();
    // delete this->player; // leave it - the owner will delete it.
    // remove pointer
    deinitializeAudioData();
}

void IRWaveform::deinitializeAudioData()
{
    setStart(0);
    setDisplayDuration(0);
    
    if(this->audioData != nullptr)
    {
        this->audioData->getData()->removeListener(this);
        getFileManager().discardFilePtr(IRFileType::IRAUDIO, this->audioData, this->parent, this->file);
    }
}

// OpenAudioFile
// # DO NOT write any task expected to be done after opening file here!
// # write it in changeListenerCallback method.
/*
void IRWaveform::openFile()
{
    if (! this->audioFile.openFile()){
        std::cout << "Error : could not open\n";
    }
}
 */

bool IRWaveform::openFile()
{
    
    // stop first
    if(isPlaying()) stop();
    
    
    
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
            deinitializeAudioData();

            getFilePtr(this->file);
            return true;
        }else return false;
    }else return false;
}

bool IRWaveform::openFile(String path)
{
    
    if(isPlaying()) stop();
    

    if(path.isNotEmpty())
    {
        File f(path);
        this->file = f;
        this->path = path;
    
        if(f.exists())
        {
            deinitializeAudioData();

            getFilePtr(this->file);
            return true;
        }else return false;
    }else return false;
}

void IRWaveform::getFilePtr(File file)
{
    
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
    

    
    // notify changes to IRProject to update IRFileInspecter
    this->parent->notifyNodeObjectModification();
    
}


void IRWaveform::changeListenerCallback (ChangeBroadcaster* source)
{
   if (source == this->player.get())
    {
        if (this->player->isPlaying())
        {
            
        }
        else if (this->player->isPausing())
        {
            //pause();
        }
        else
        { // stop
            //stop();
        }
    }
    else if (source == &this->thumbnail)
    {
        
        //std::cout << "thumbnail changeMessage chan = " << this->thumbnail.getNumChannels() << std::endl;
        this->drawWaveform = true;

        repaint();
    }
}

void IRWaveform::makeThumbnail(String path)
{
    //{
      //  const ScopedLock sl (this->callbackLock); // lock thread
        File file (path);
        
        std::cout << "thumnail = " << path << std::endl;
        this->thumbnail.setSource(new FileInputSource(file));
        
        // initialize display duration if no user defined duration is set.
        if(this->duration == 0)
            this->duration = this->thumbnail.getTotalLength();
        
        removeChildComponent(&this->openButton);
        //repaint();
    //}
}
//==========================================================================
// Callback functions
//==========================================================================

void IRWaveform::fileImportCompleted()
{
    this->duration = 0; // initialize
    
    // init selected

    std::cout << "IRWaveform : fileImportCompleted\n";
    this->audioData = static_cast<DataAllocationManager<IRAudio>*>(getFileManager().getFileObjectAndRemoveFromBuffer(this->randomIDForPtr));

    this->audioData->getData()->addListener(this);
    
    //set audioBuffer to player
    std::vector<int>v = {0,1};
    this->player->setAudioBuffer(this->audioData->getData()->getAudioBuffer(), false, this->audioData->getData()->getSampleRate(),v);
    
   // set received Ptr to the Link System
    //this->parent->setAudioLink(this->audioData->getData());
    
    //
    fileImportCompletedAction();

    // make waveform thumbnail
    makeThumbnail(file.getFullPathName());

}


void IRWaveform::resized()
{
    this->openButton.setBounds(0,0,getWidth(),getHeight());
    updatePlayingLine();
}


void IRWaveform::paint(Graphics& g)
{
    //std::cout << "+++++ IRWaveform repaint() +++++ \n";
    if (this->drawWaveform)
    {
        auto area = getLocalBounds();//.reduced (2);
        
        g.setColour (Colours::white);
        //g.fillRoundedRectangle(area.toFloat(), 5.0f);
        g.fillRect(area.toFloat());
        
        g.setColour (getStr()->SYSTEMCOLOUR.contents);
        //g.drawRoundedRectangle (area.toFloat(), 5.0f, 2.0f);
        g.drawRect(area.toFloat(), 1.0);
        
        g.setColour(getStr()->SYSTEMCOLOUR.fundamental);
        //small margin
        Rectangle<int> thumbnailBounds (1,1, getWidth()-2, getHeight()-2);
        this->thumbnail.drawChannel(g,
                                    thumbnailBounds, // rounds rectangle
                                    this->start, // start in ms.
                                    this->start + this->duration, // end in ms.
                                    0, // channel index
                                    1.0f // zoom factor
                                    );
        
        // line
        g.setColour(Colours::red);
        g.drawLine(this->playingLine.getX(),
                   this->playingLine.getY(),
                   this->playingLine.getWidth(),
                   this->playingLine.getHeight(),
                   3.0);
        
    }
}


void IRWaveform::setStart(double ms)
{
    this->start = ms;
}


double IRWaveform::getStart() const
{
    return this->start;
}


void IRWaveform::setDisplayDuration(double ms)
{
    this->duration = ms;
}


double IRWaveform::getDisplayDuration() const
{
    return this->duration;
}


double IRWaveform::getTotalLength() const
{
    if (this->drawWaveform)
        return this->thumbnail.getTotalLength();
    else return 0;
}


void IRWaveform::setChannelIndex(int channelIndex)
{
    this->channelIndex = channelIndex;
}


void IRWaveform::setZoomFactor(double zoomFactor)
{
    this->zoomFactor = zoomFactor;
}


double IRWaveform::getZoomFactor() const
{
    return this->zoomFactor;
}


double IRWaveform::getSampleRate() const
{
    return this->audioData->getData()->getSampleRate();
}


bool IRWaveform::isWaveformPainted() const
{
    return this->drawWaveform;
}


void IRWaveform::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    this->player->prepareToPlay(samplesPerBlockExpected, sampleRate);
}


void IRWaveform::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    this->player->getNextAudioBlock(bufferToFill);
}


void IRWaveform::releaseResources()
{
    this->player->releaseResources();
}


// player control
void IRWaveform::play(int start, int duration, int offset, bool looping)
{
    if(this->duration > 0)
    {
        if(this->segmentPlayerStatus == END_REACHED)
        {
            stop();
        }
        
        std::cout << "IRWaveform : play() start " << start << " : duration " << duration << std::endl;
        
        this->player->setParameters(start, duration, offset, looping);
        this->player->setLooping(looping);
        this->player->start();
        this->segmentPlayerStatus = PLAYING;
        startAnimation();
    }
}

void IRWaveform::play()
{
    
    if(this->duration > 0)
    {
        auto data = this->audioData->getData();
        double sampleRate = data->getSampleRate();
        double duration = ceil(getDisplayDuration() * sampleRate);
        double start = floor(getStart() * sampleRate);
        
        //std::cout << "start before fixed " << start << " : currentPlayedFrame = " << getCurrentPlayedFrame() << std::endl;
        
        // if already reached the end of segment, then initialize first
        if(getCurrentPlayedFrame() >= (start + duration))
        {
            stop();
        }
        
        // if it is paused in the middle of audio data, then re-start from the paused location.
        double fixLength = getCurrentPlayedFrame() - start;
        if(fixLength > 0 &&
           fixLength < duration)
        {
            start = getCurrentPlayedFrame();
            duration -= fixLength;
            
        }else{
            setCurrentPlayedFrame(start);
        }
    

        play(start, duration, 0, false);
        
        //std::cout << "play : start " << start << ", duration " << duration << " current = "<< getCurrentPlayedFrame() << std::endl;
      
    }
}

void IRWaveform::stop()
{
    if(this->duration > 0)
    {
        this->player->stop();
        this->segmentPlayerStatus = STOPPED;
        setCurrentPlayedFrame(getStart());
        this->player->initializeParameters();
        //update
        updatePlayingLine();
        
        stopAnimation();
        
        
    }
}


void IRWaveform::pausing()
{
    if(this->duration > 0)
    {
        if(this->segmentPlayerStatus == PLAYING)
        {
            setCurrentPlayedFrame(this->player->getNextReadPosition());
            this->player->pause();
            this->segmentPlayerStatus = PAUSED;
            stopAnimation();
        }
    }else{
        std::cout <<"pausing not operated, duration = 0\n";
    }
}

bool IRWaveform::isPlaying() const
{
    if(this->player == nullptr) return false;
    return this->player->isPlaying();
}


SoundPlayerClass* IRWaveform::getPlayer() const
{
    return this->player.get();
}



// --------------------------------------------------
void IRWaveform::linkZoomInfo(Component* comp)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        data->linkZoomInOutWithSharedComponents(comp);
    }
}

void IRWaveform::linkCurrentPlayedFrame(Component* comp)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        data->linkAudioPlaywithSharedComponents(comp);
    }
}


void IRWaveform::linkViewPosition(Component* comp)
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        data->setViewPortPosition(this->visiblePos);
        data->linkViewPortPositionWithSharedComponents(comp);
    }
}


// --------------------------------------------------


void IRWaveform::zoomInOutOperatedFromComponent(IRAudio* obj)
{
    auto comp = obj->getEmittingComponent();
    // check if the emmiting component is not this object otherwise we will face on the infinitive loop
    if(comp != nodeObject)
    {
        
        setZoomInfo(obj->getZoomInfo());
        //std::cout << "zoominfo of "<< nodeObject << " = " << this->zoomInfo.getX() <<  " from " << comp << std::endl;
        
        this->status = zoomInfoShared;
        sendChangeMessage();
       
    }else{
        //std::cout <<"zoomInfo same \n";
    }
}

void IRWaveform::audioPlayOperatedFromComponent(IRAudio* obj)
{
    auto comp = obj->getEmittingComponent();
    // check if the emmiting component is not this object otherwise we will face on the infinitive loop
    
    //std::cout << "audioPlayOperatedFromComponent : comp = " << comp << " received in " << nodeObject << std::endl;
    
    // check if the received component is not this object
    // the received component is MASTER and non-received object is SLAVE
    if(comp != nodeObject)
    {
        //std::cout << "audioPlayOperatedFromComponent from " << comp << " to " << nodeObject << std::endl;

        // Only LINKED
        this->segmentPlayerStatus = PLAYPOSITION_SLAVED;
        
        
        // stop pther playing process in this case to avoid unneccesary lisk
        //if(this->player->isPlaying()) this->player->stop();
        if(this->segmentPlayerStatus == PLAYING ||
           this->segmentPlayerStatus == PAUSED ||
           this->segmentPlayerStatus == END_REACHED)
        {
            stop();
        }

        setCurrentPlayedFrame(obj->getCurrentPlayedFrame());
        createPlayingLine(obj->getCurrentPlayedFrame());
        this->status = currentPlayedFrameShared;
        sendChangeMessage();
    }
}

void IRWaveform::viewPortPositionFromComponent(IRAudio *obj)
{
    auto comp = obj->getEmittingComponent();
    // check if the emmiting component is not this object otherwise we will face on the infinitive loop
    if(comp != nodeObject)
    {
        this->visiblePos = obj->getViewPortPosition();
        this->status = viewPosShared;
        sendChangeMessage();
    }
}

// --------------------------------------------------

void IRWaveform::updatePlayingLine()
{
    if(this->audioData != nullptr)
    {
        auto data = this->audioData->getData();
        int64 playingPosition = this->player->getNextReadPosition();
        
        createPlayingLine(playingPosition);

        // if this object is HOST, then call linkAudioPlaywithSharedComponents()
        if(this->segmentPlayerStatus != PLAYPOSITION_SLAVED)
        {
            data->setCurrentPlayedFrame(playingPosition);
            data->linkAudioPlaywithSharedComponents(nodeObject);
        }
    }
}

void IRWaveform::updateAnimationFrame()
{
    updatePlayingLine();
}

void IRWaveform::createPlayingLine(int64 currentFrame)
{
    if(this->audioData != nullptr)
    {
                
        // in waveform
        auto data = this->audioData->getData();
        double sampleRate = data->getSampleRate();
        double duration = ceil(getDisplayDuration() * sampleRate);
        double start = floor(getStart() * sampleRate);
        
        // in audio player in sample
        double playSamples = this->player->getPlaySamples();
        double playStart   = this->player->getStartPosition();
        
        double p = (double)currentFrame - start;

        if(p >= 0)
        {
            
            //std::cout << this << " : start " << start << ", duration " << duration << " : playStart " << playStart << ", playSamples " << playSamples << " :  current frame" << currentFrame <<std::endl;
            
            float ratio = p / duration;
                    
            int x_pos = floor((float)getWidth() * ratio);
            
            //std::cout << "createPlayingLine : xpos = " << x_pos << " : ratio = " << ratio << " : (p : " << p << " / playStart" << playStart << " from playSamples " << playSamples<< ") "<< std::endl;
            
            this->playingLine = Rectangle<int>(x_pos, 0, x_pos, getHeight());
            repaint();
            
            // reaches to the end
            if((p + start - playStart) >= (playSamples-1))
            {
                //std::cout << "pausing... currentFrame = " << currentFrame << " : than " << (playStart + playSamples-1) << std::endl;

                if(this->segmentPlayerStatus != PLAYPOSITION_SLAVED) pausing();
                this->segmentPlayerStatus = END_REACHED;
                
                
            }

        }
    }
}
// --------------------------------------------------
