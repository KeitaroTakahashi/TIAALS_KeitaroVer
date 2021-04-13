//
//  IRPlayPauseButton.h
//  IRiMaS
//
//  Created by Keitaro on 30/06/2020.
//

#ifndef IRPlayPauseButton_h
#define IRPlayPauseButton_h

#include "IRIconBank.hpp"
#include "IRImageButton.hpp"
#include "IRStrComponent.hpp"

class IRPlayPauseButton : public IRImageButton,
public IRStrComponent
{
public:
    
    enum IRPlayPauseButtonStatus
    {
        PLAY,
        PAUSE
    };
    
    IRPlayPauseButton(IRStr* str) : IRStrComponent(str)
    {
        setTwoImages(str->ICONBANK->icon_play, str->ICONBANK->icon_pause);
        setStatus(PAUSE);
    }
    
    ~IRPlayPauseButton()
    {
        
    }
    
    // --------------------------------------------------
    void resized() override
    {
        
    }
    
   
    
    // --------------------------------------------------

    void clicked() override
    {
        if(getStatus() == PAUSE)
            setStatus(PLAY);
        else if(getStatus() == PLAY)
            setStatus(PAUSE);
    }
    // --------------------------------------------------
    
    void setTwoImages(IRIconBank::IRIconImage playImage, IRIconBank::IRIconImage pauseImage)
    {
        if(getStr()->SYSTEMCOLOUR.isWhiteBased)
        {
            this->playImage = playImage.black;
            this->pauseImage = pauseImage.black;
        }else{
            this->playImage = playImage.white;
            this->pauseImage = pauseImage.white;
        }
        
        repaint();
    }
    
    void setTwoImages(Image playImage, Image pauseImage)
    {
        this->playImage = playImage;
        this->pauseImage = pauseImage;
        
        repaint();
    }
    // --------------------------------------------------
    
    void setStatus(IRPlayPauseButtonStatus status, NotificationType notification = dontSendNotification)
    {
        this->status = status;
        
        if(this->status == PLAY) setImage(this->pauseImage);
        else setImage(this->playImage);
        
        if(notification == sendNotification)
            if(this->statusChanged != nullptr) this->statusChanged(getStatus());
        
        repaint();

    }
    
    IRPlayPauseButtonStatus getStatus() const { return this->status; }
    
    // --------------------------------------------------
    
    std::function<void(IRPlayPauseButtonStatus)> statusChanged;
    // --------------------------------------------------

private:
    IRPlayPauseButtonStatus status = PAUSE;
    
    
    Image playImage;
    Image pauseImage;
    
};


#endif /* IRPlayPauseButton_h */
