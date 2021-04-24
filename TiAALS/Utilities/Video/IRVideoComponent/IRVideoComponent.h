//
//  IRVideoComponent.h
//  IRiMaS
//
//  Created by Keitaro on 10/12/2019.
//

#ifndef IRVideoComponent_h
#define IRVideoComponent_h

#include "JuceHeader.h"
#include "KLib.h"
#include "IRNSViewManager.hpp"

class IRVideoComponent : public Component
{
public:
    IRVideoComponent(bool enableController = true) :
    enableController(enableController)
    {
        
    }
    
    ~IRVideoComponent()
    {
        if(this->isVideoLoaded)
        {
            if(this->player_without_controller.get() != nullptr)
                this->player_without_controller.reset();
        }
    }
    // ==================================================

    void paint(Graphics& g) override
    {
        g.fillAll(Colours::transparentWhite);
    }

    void resized() override
    {
        
        if(this->isVideoLoaded)
        {
            if(this->player_without_controller.get() != nullptr)
                this->player_without_controller->setBounds(getLocalBounds());

            auto p = this->player_without_controller;
            int w = p->getHeight() * this->aspectRatio;
            
            if(p->getWidth() < w)
            {
                // follow width
                int h = p->getWidth() / this->aspectRatio;
                int y = (getHeight() - h) / 2;
                this->videoBounds = Rectangle<int> (0, y,
                                                    p->getWidth(), h);
            }else{
                // follow h
                // follow width
                int w = p->getHeight() * this->aspectRatio;
                int x = (getWidth() - w) / 2;

                this->videoBounds = Rectangle<int> (x, 0,
                                                    w, p->getHeight());
            }
            
        }

    }
    
    // ==================================================
    void setVideoPlayer()
    {
        this->currentPlayer = this->player_without_controller.get();

    }
    // ==================================================

    void play()
    {
        if(this->currentPlayer != nullptr)
            this->currentPlayer->play();
    }
    
    void stop()
    {
        if(this->currentPlayer != nullptr)
            this->currentPlayer->stop();
    }
    
    bool isPlaying() const
    {
        if(this->currentPlayer == nullptr) return false;
        else return this->currentPlayer->isPlaying();
    }
    void setPlayPosition(double newPlayPositionInSec)
    {
        if(this->currentPlayer != nullptr)
            this->currentPlayer->setPlayPosition(newPlayPositionInSec);
    }
    double getPlayPosition()
    {
        if(this->currentPlayer == nullptr) return 0;
        else return this->currentPlayer->getPlayPosition();
    }
    void setPlaySpeed(double newSpeed)
    {
        if(this->currentPlayer != nullptr)
            this->currentPlayer->setPlaySpeed(newSpeed);
        
    }
    double getPlaySpeed()
    {
        if(this->currentPlayer == nullptr) return 1.0;
        else return this->currentPlayer->getPlaySpeed();
    }
    void setAudioVolume(float newVolume)
    {
        if(this->currentPlayer != nullptr)
            this->currentPlayer->setAudioVolume(newVolume);
    }
    
    float getAudioVolume()
    {
        if(this->currentPlayer == nullptr) return 0;
        else return this->currentPlayer->getAudioVolume();
    }
    double getVideoLength()
    {
        if(this->currentPlayer == nullptr) return 0;
        else return this->currentPlayer->getVideoDuration();
    }
    
    Rectangle<int> getCurrentVideoBounds() { return getBounds(); }
    // ==================================================
    void setNeedController(bool flag)
    {
        this->enableController = flag;
        
        if(!this->isVideoLoaded) return;

        addAndMakeVisible(this->player_without_controller.get());
        this->currentPlayer = this->player_without_controller.get();
    }

    bool isController() const { return this->enableController; }
    // ==================================================

    void createVideos()
    {
        //this->player_with_controller.reset(new VideoComponent(true));
        this->player_without_controller.reset(new VideoComponent(false));
        setVideoPlayer();
    }
    
    void loadVideo(URL url, bool callback = true)
    {
        createVideos();
                
        this->isCallback = callback;
                
        if(callback)
        {
            this->player_without_controller->loadAsync(url, [this] (const URL& u, Result r) {
                videoLoadingFinished (u, r);
            });
        }else{
            Result r = this->player_without_controller->load(url);
            videoLoadingFinished(url, r);
        }

    }
    
    void videoLoadingFinished (const URL& url, Result result)
    {
        //ignoreUnused (url);

        if(result.wasOk()){
            
            this->isVideoLoaded = true;
                        
            this->videoSize = this->player_without_controller->getVideoNativeSize();

            this->aspectRatio = (float)this->videoSize.getWidth() / (float)this->videoSize.getHeight();
           
            setNeedController(false);
            
            int w,h;
            if(this->videoSize.getWidth() > getWidth())
            {
                w = getWidth();
                h = (int)((float)w / this->aspectRatio);
            }else{
                w = this->videoSize.getWidth();
                h = this->videoSize.getHeight();
            }
            
            setVideoPlayer();
            
            // here we need to call resized() of this class. This resized() does not probagate to its parent resized()
            resized();
            
            std::cout << "complete video load : length = " << getVideoLength() << std::endl;
            
            if(this->isCallback)
            {
                if(videoLoadCompleted != nullptr)
                {
                    videoLoadCompleted();
                }
            }
                
        }else{
            this->isVideoLoaded = false;
            removeChildComponent(this->player_without_controller.get());
            //removeChildComponent(this->player_with_controller.get());
            this->currentPlayer = nullptr;
            KLib().showConnectionErrorMessage("Could not load the video file of "+url.getSubPath());
        }
    }
    
    // ==================================================
    
    bool hasVideo() const { return this->isVideoLoaded; }

    Rectangle<int> getVideoSize() const { return this->videoSize; }
    float getAspectRatio() const { return this->aspectRatio; }
    Rectangle<int> getVideoBounds() const { return this->videoBounds; }
    
    //URL getURL() const { return this->url; }
        
    // ==================================================
    void bringViewToFront()
    {
        
        // **** add following code in juce::VideoComponent
        /*
         
         void*  getPimpl() {
             if(pimpl.get() != nullptr)
                 return pimpl.get();
             else return nullptr;
         }
         
         */
        
    #if JUCE_MAC
        
        if(this->currentPlayer == nullptr) return;
        
        NSViewComponent* view = static_cast<NSViewComponent*>(this->currentPlayer->getPimpl());
        if(view == nullptr) return;
        
        IRNSViewManager manager;
        manager.bringOpenGLContextFront(this, view);
        
    #endif
        
    }
    // ==================================================

    //callback
    std::function<void()> videoLoadCompleted = nullptr;
    
private:
    
    std::shared_ptr<VideoComponent> player_without_controller;
    
    VideoComponent* currentPlayer = nullptr;

    bool isVideoLoaded = false;
    
    bool isCallback = true;
    
    bool enableController = false;;
    
    //URL url;
    String path;
    // width / height
    float aspectRatio = 1.0;
    
    Rectangle<int> videoSize;
    Rectangle<int> videoBounds;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRVideoComponent)

};
#endif /* IRVideoComponent_h */
