//
//  VideoAnnotaterController.h
//  TIAALS_LIGHT
//
//  Created by Keitaro on 22/03/2021.
//

#ifndef VideoAnnotaterController_h
#define VideoAnnotaterController_h

#include "IRStrComponent.hpp"
class VideoAnnotaterController : public Component,
public IRStrComponent,
public ChangeBroadcaster,
private Button::Listener
{
public:
    
    enum VideoAnnotaterControllerStatus
    {
        NONE,
        OpenVideoAnnotater
    };
    
    VideoAnnotaterController(IRStr* str) : IRStrComponent(str)
    {
        this->openVideoAnnotaterButton.setButtonText("Open Video");
        this->openVideoAnnotaterButton.addListener(this);
        addAndMakeVisible(this->openVideoAnnotaterButton);

    }
    
    ~VideoAnnotaterController()
    {
        
    }
    
    // --------------------------------------------------
    
    VideoAnnotaterControllerStatus getStatus() const { return this->status; }
    // --------------------------------------------------

private:
    // --------------------------------------------------

    void resized() override
    {
        int y = 0;
        int yIncrement = 30;
        int yBigIncrement = 30;
        
        this->openVideoAnnotaterButton.setBounds(10, y, getWidth() - 20, 30);

    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    }
    
    // --------------------------------------------------

    TextButton openVideoAnnotaterButton;
    
    void createButton(TextButton& button, String text)
    {
        button.setButtonText(text);
        addAndMakeVisible(button);
        button.addListener(this);
    }

    void buttonClicked(Button* button) override
    {
        if(button == &this->openVideoAnnotaterButton)
        {
            this->status = OpenVideoAnnotater;
            sendChangeMessage();
        }
    }
    // --------------------------------------------------
    
    VideoAnnotaterControllerStatus status = NONE;
    // --------------------------------------------------

    // --------------------------------------------------
};

#endif /* VideoAnnotaterController_h */
