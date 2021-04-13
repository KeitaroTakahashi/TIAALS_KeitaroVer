//
//  SoundPlayer_ThreadSafe.h
//  IRiMaS
//
//  Created by Keitaro on 10/02/2020.
//

#ifndef SoundPlayer_ThreadSafe_h
#define SoundPlayer_ThreadSafe_h


#include "IRUIAudioFoundation.hpp"
#include "IRSoundPlayer.h"

class AudioPlayer_threadSafe : //public /*AudioAppComponent*/ Component, public AudioSource,
public IRUIAudioFoundation,
private ChangeListener, IRAudio::Listener
{
    
public:
    
    AudioPlayer_threadSafe(IRNodeObject* parent, IRStr* str) :
    IRUIAudioFoundation(parent, str)
    {
        this->parent = parent;
        setBounds(0,0,100,98);
        
        addAndMakeVisible(&this->openButton);
        this->openButton.setButtonText("open");
        this->openButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.contents);
        this->openButton.setEnabled(true);
        this->openButton.onClick = [this]{ openButtonClicked(); };
        
        addAndMakeVisible(&this->playButton);
        this->playButton.setButtonText("Play");
        this->playButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.contents);
        this->playButton.setEnabled(false);
        this->playButton.onClick = [this]{ playButtonClicked(); };
        
        addAndMakeVisible(&this->loopButton);
        this->loopButton.setButtonText("Loop");
        this->loopButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.contents);
        this->loopButton.setEnabled(true);
        this->loopButton.onClick = [this]{ loopButtonClicked(); };
        
        addAndMakeVisible(&this->pauseButton);
        this->pauseButton.setButtonText("pause");
        this->pauseButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.contents);
        this->pauseButton.setEnabled(false);
        this->pauseButton.onClick = [this]{ pauseButtonClicked(); };
        
        addAndMakeVisible(&this->stopButton);
        this->stopButton.setButtonText("stop");
        this->stopButton.setColour(TextButton::buttonColourId, SYSTEMCOLOUR.contents);
        this->stopButton.setEnabled(false);
        this->stopButton.onClick = [this]{ stopButtonClicked(); };
        
        this->audioFile.addListener(this);
        this->audioFile.addChangeListener(this);
        
        this->player.addChangeListener(this);
        
    }
    
    ~AudioPlayer_threadSafe()
    {
        // remove pointer
        if(this->audioData != nullptr)
            getFileManager().discardFilePtr(IRFileType::IRAUDIO, this->audioData, this->parent, this->file);
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &this->player)
        {
            if (this->player.isPlaying())
                changeState(Playing);
            else if (this->player.isPausing()){
                // Stopped does not reset playingPosition but just freeze playing process
                changeState(Pausing);
            }
            else
            {
                //first call Stopping to reset playingPosition
                changeState(Stopping);
                //then call Stopped to stop
                changeState(Stopped);
            }
        } else if (source == &this->audioFile)
        {
            if (this->audioFile.isFileLoadCompleted)
            {
                
                
            }
            
            if (this->audioFile.isFileOpened)
            {
                
            }
        }
    }
    
    
    // ==================================================
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        this->player.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }
    
    virtual void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override
    {
        this->player.getNextAudioBlock(bufferToFill);
    }
    
    virtual void releaseResources() override
    {
        this->player.releaseResources();
    }
    // ==================================================
    
    void resized() override
    {
        int numButton = 5;
        
        //distance between buttons in y
        int dis = 2;
        int x2 = this->xMargin * 2;
        int w = getWidth() - x2;
        int h = (getHeight() - this->yMargin*2)/numButton - dis;
        
        int yPosition = this->yMargin + dis;
        this->openButton.setBounds  (this->xMargin, yPosition, w, h);
        yPosition += dis + h;
        this->playButton.setBounds  (this->xMargin, yPosition, w, h);
        yPosition += dis + h;
        this->loopButton.setBounds  (this->xMargin, yPosition, w, h);
        yPosition += dis + h;
        this->pauseButton.setBounds (this->xMargin, yPosition, w, h);
        yPosition += dis + h;
        this->stopButton.setBounds  (this->xMargin, yPosition, w, h);
        
    }
    // ==================================================

    void openFile(File file)
    {
        this->file = file;
        auto p = file.getFullPathName();
        this->path = p;
        
        String pathToOpen;
        pathToOpen.swapWith(p);
        
        if(pathToOpen.isNotEmpty())
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
            
            this->parent->notifyNodeObjectModification();
            
            // do not write any process here but got
            
            // if success, then enable play and stop buttons
            this->stopButton.setEnabled(true);
            this->playButton.setEnabled(true);
            
        }else // cancel
        {
            if(!this->isFileOpened)
                this->audioData = nullptr;
        }
    }
    
    void openFile()
    {
        this->isFileOpened = false;
        
        FileChooser chooser("Select an image file...",
                            {},
                            "*.wav, *.aif, *.aiff, *.mp3");
        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();
            openFile(file);
        }
    }
    
    void openFile(String pathToOpen)
    {
        openFile(File(pathToOpen));
    }
    // ==================================================

    void openButtonClicked()
    {
        openFile();
    }
    
    void playButtonClicked()
    {
        this->player.start();
        changeState(Starting);
    }
    
    void loopButtonClicked()
    {
        bool flag = ! this->player.isLooping();
        this->player.setLooping(flag);
        changeState(Looping);
    }
    
    void stopButtonClicked()
    {
        this->player.stop();
        changeState(Stopping);
    }
    
    void pauseButtonClicked()
    {
        this->player.pause();
        changeState(Pausing);
    }
    
    //==========================================================================
    // Callback functions
    //==========================================================================
    
    void fileImportCompleted()
    {
        
        this->audioData = static_cast<DataAllocationManager<IRAudio>*>(getFileManager().getFileObjectAndRemoveFromBuffer(this->randomIDForPtr));
        //set audioBuffer to player
        std::vector<int>v = {0,1};
        this->player.setAudioBuffer(this->audioData->getData()->getAudioBuffer(), false, this->audioData->getData()->getSampleRate(),v);
        
       

    }
    
    // this method is called when the file import completed.
    // THIS IS NOT CURRENTLY USED = KEITARO
    virtual void fileImportCompleted(IRAudio *obj) override
    {
        
        std::cout << "fileImportCompleted object \n";
        this->audioData = static_cast<DataAllocationManager<IRAudio>*>(getFileManager().getFileObjectAndRemoveFromBuffer(this->randomIDForPtr));
        //set audioBuffer to player
        std::vector<int>v = {0,1};
        this->player.setAudioBuffer(this->audioData->getData()->getAudioBuffer(), false, this->audioData->getData()->getSampleRate(),v);
    }
    
    //this method is called when file status changed
    virtual void fileStatusChanged(IRAudio *obj) override
    {
        
    }
    
    //==========================================================================
    //change labels
    
    
private:
    //==========================================================================
    
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Looping,
        Stopping,
        Pausing
    };
    
    void changeState (TransportState newState)
    {
        if(this->state != newState)
        {
            this->state = newState;
            switch(this->state)
            {
                case Stopped: // called when clickling a stop button or by callback
                    this->stopButton.setEnabled(false);
                    this->playButton.setEnabled(true);
                    this->pauseButton.setEnabled(false);
                    //reset playing position
                    this->player.setNextReadPosition(0);
                    break;
                case Starting:
                    this->playButton.setEnabled(false);
                    break;
                case Playing:
                    this->stopButton.setEnabled(true);
                    this->pauseButton.setEnabled(true);
                    break;
                case Looping:
                    this->loopButton.setEnabled(false);
                    break;
                case Stopping: // called when clicking a stop button
                    
                    this->player.setLooping(false);
                    this->loopButton.setEnabled(true);
                    break;
                case Pausing:
                    this->pauseButton.setEnabled(false);
                    this->playButton.setEnabled(true);
                    this->stopButton.setEnabled(true);
                    break;
            }
        }
    }
    //==========================================================================
    
    IRNodeObject* parent;
    
    IRAudio audioFile;
    SoundPlayerClass player;
    
    bool isFileOpened = false;
    String path;
    File file;
    
    TransportState state;
    
    //buttons
    TextButton playButton;
    TextButton openButton;
    TextButton stopButton;
    TextButton pauseButton;
    TextButton loopButton;
    
    int buttonWidth = 90;
    int buttonHeight = 20;
    int xMargin = 5;
    int yMargin = 4;
    
    DataAllocationManager<IRAudio>* audioData = nullptr;
    // ===========================================================================
    std::string randomIDForPtr;
    // ===========================================================================
    // system appearance
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer_threadSafe)
};


#endif /* SoundPlayer_ThreadSafe_h */
