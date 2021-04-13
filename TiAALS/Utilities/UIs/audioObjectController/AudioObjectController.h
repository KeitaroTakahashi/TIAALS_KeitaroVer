//
//  AudioObjectController.h
//  IRiMaS
//
//  Created by Keitaro on 10/10/2019.
//

#ifndef AudioObjectController_h
#define AudioObjectController_h
#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"

class AudioObjectController :public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener
{
public:
    
    enum AudioObjectControllerStatus
    {
        AudioFileOpen,
        PLAY,
        PAUSE,
        STOP,
        NONE
    };
    
    AudioObjectController(IRStr* str) : IRStrComponent(str)
    {
        addAndMakeVisible(&this->OpenAudioButton);
        this->OpenAudioButton.setButtonText("Open Audio File");
        this->OpenAudioButton.onClick = [this]{ openAudioButtonClickedAction(); };

        
        addAndMakeVisible(&this->AudioURLLabel);
        this->AudioURLLabel.setText("empty", dontSendNotification);
        
        addAndMakeVisible(&this->playerLabel);
        this->playerLabel.setText("Player", dontSendNotification);
        
        createButton(&this->playButton, getStr()->ICONBANK->icon_play);
        this->playButton.onClick = [this]{ playButtonClickedAction(); };
        createButton(&this->stopButton, getStr()->ICONBANK->icon_stop);
        this->stopButton.onClick = [this]{ stopButtonClickedAction(); };
        createButton(&this->pauseButton, getStr()->ICONBANK->icon_pause);
        this->pauseButton.onClick = [this]{ pauseButtonClickedAction(); };
        
        addAndMakeVisible(&this->modeLabel);
        this->modeLabel.setText("Cursor Mode", dontSendNotification);
        
        addAndMakeVisible(&this->modeBox);
        this->modeBox.addItem("Position", 1);
        this->modeBox.addItem("Horizontal Selection", 2);
        this->modeBox.addItem("vertical Selection", 3);
        this->modeBox.addItem("Advanced Selection", 4);
        this->modeBox.setSelectedId(1, dontSendNotification);
        //this->shapeMenu.addListener(this);

    }
    
    ~AudioObjectController()
    {
        
    }
    // ==================================================
    void resized() override
    {
        int y = 0;
        int yIncrement = 30;
        //int yBigIncrement = 40;
        int x = 10;
        
        int menuWidth = getWidth() - 20;
        
        this->OpenAudioButton.setBounds(x, y, menuWidth, 30);
        
        y+= yIncrement;
        
        this->AudioURLLabel.setBounds(x,y,menuWidth, 30);
        
        y+= 30 + yIncrement;
        
        this->playerLabelLine = y;
        this->playerLabel.setBounds(x,y,menuWidth, 30);
        
        
        y+= yIncrement;
        

        float ratio = this->stopButton.getAspectRatio();
        int buttonWidth = 40;
        int buttonHeight = buttonWidth * ratio;
        
        int playerMargin = ( (getWidth() - 40*3)/4 );

        this->stopButton.setBounds(playerMargin, y, buttonWidth, buttonHeight);
        this->playButton.setBounds(playerMargin*2 + buttonWidth, y, buttonWidth, buttonHeight);
        this->pauseButton.setBounds(playerMargin*3 + buttonWidth*2, y, buttonWidth, buttonHeight);
        
        y += buttonHeight + yIncrement;
        
        //this->modeLabelLine = y;
        
        this->modeLabel.setBounds(x, y, menuWidth, 30);
        y+= yIncrement;
        this->modeBox.setBounds(x, y, menuWidth, 30);
        
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
        
        g.setColour(getStr()->SYSTEMCOLOUR.fundamental);
        g.drawLine(0, this->playerLabelLine, getWidth(), this->playerLabelLine, 2);
        //g.drawLine(0, this->modeLabelLine, getWidth(), this->modeLabelLine, 2);

    }
    // ==================================================
    
    void setLoadedAudioFilePath(String path)
    {
        this->AudioURLLabel.setText(path, dontSendNotification);
    }
    // ==================================================
    
    // ==================================================
    
    AudioObjectControllerStatus getStatus() const{ return this->status; }
    
private:
    
    void changeListenerCallback(ChangeBroadcaster* source) override
    {
        
    }
    

    void createButton(IRImageButton* button, IRIconBank::IRIconImage img)
    {
        if(getStr()->SYSTEMCOLOUR.isWhiteBased)
            button->setImage(img.black);
        else
            button->setImage(img.white);
        
        //button->setDrawCircle(false);
        addAndMakeVisible(button);
    }
    // ==================================================
    
    TextButton OpenAudioButton;
    void openAudioButtonClickedAction()
    {
        this->status = AudioFileOpen;
        sendChangeMessage();
    }
    Label AudioURLLabel;
    
    Label playerLabel;
    
    IRImageButton playButton;
    void playButtonClickedAction()
    {
        this->status = PLAY;
        sendChangeMessage();
    }
    IRImageButton stopButton;
    void stopButtonClickedAction()
    {
        this->status = STOP;
        sendChangeMessage();
    }
    IRImageButton pauseButton;
    void pauseButtonClickedAction()
    {
        this->status = PAUSE;
        sendChangeMessage();
    }
    
    Label modeLabel;
    ComboBox modeBox;

    // ==================================================

    AudioObjectControllerStatus status = NONE;
    // ==================================================
    
    int playerLabelLine = 0;
    int modeLabelLine = 0;
    
    // ==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioObjectController)

};


#endif /* AudioObjectController_h */
