//
//  ImageController.h
//  IRiMaS
//
//  Created by Keitaro on 03/10/2019.
//

#ifndef ImageController_h
#define ImageController_h

#include "JuceHeader.h"
class ImageController : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener
{
public:
    
    enum ImageControllerStatus
    {
        OpenImageFile,
        WidthChange,
        HeightChange,
        W_H_Sync,
        NONE
    };
    
    ImageController(IRStr * str) : IRStrComponent(str)
    {
        addAndMakeVisible(&this->openImageButton);
        this->openImageButton.setButtonText("Open Image File");
        this->openImageButton.onClick = [this]{ OpenImageFileAction(); };
    }
    
    ~ImageController()
    {
        
    }
    
    void resized() override
    {
        int y = 0;
       // int yIncrement = 30;
        //int yBigIncrement = 30;
        
        int menuWidth = getWidth() - 20;
        
        this->openImageButton.setBounds(10, y, menuWidth, 30);
    }
    
    void paint(Graphics& g) override
    {
        
    }
    
    void OpenImageFileAction()
    {
        
        std::cout << "OpenImageFileAction\n";
        this->status = OpenImageFile;
        sendChangeMessage();
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        
    }

    ImageControllerStatus getStatus() const { return this->status; }

private:
    
    TextButton openImageButton;
    
    ImageControllerStatus status = NONE;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageController)

};
#endif /* ImageController_h */
