//
//  VideoAnnotaterWindowControllerUI.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 24/03/2021.
//

#ifndef VideoAnnotaterWindowControllerUI_hpp
#define VideoAnnotaterWindowControllerUI_hpp


#include "IRStrComponent.hpp"
#include "IRWorkspaceControllerUI.h"
#include "IRLabel.h"
#include "KLib.h"


class VideoAnnotaterWindowControllerUI : public Component,
public IRStrComponent,
public ChangeBroadcaster,
private Button::Listener
{
public:
    
    enum VideoAnnotaterWindowControllerUIStatus
    {
        NONE,
        openVideoFile,
        videoSizePercent,
        
        TEXTEDITOR,
        SHAPE,
        IMAGE,
        MEDIUMTEXTEDITOR,
        SMALLTEXTEDITOR
    };
    
    VideoAnnotaterWindowControllerUI(IRStr* str);
    ~VideoAnnotaterWindowControllerUI();
    
    

    // --------------------------------------------------
    VideoAnnotaterWindowControllerUIStatus getStatus() const { return this->status; }
    // --------------------------------------------------
    
    int getVideoSizePercent() const { return this->videoSizePercentVal; }
    void setVideoSizePercent(int val);

private:
    // --------------------------------------------------

    void resized() override;
    void paint(Graphics& g) override;
    
    void createLabel(IRLabel& label, String text, bool border, bool isEditable);
    bool isDigitNumber(String text);
    void videoSizePercentInputError();
    // --------------------------------------------------

    TextButton openVideoAnnotaterButton;
    std::unique_ptr<IRWorkspaceControllerUI> workspaceController;
    
    IRLabel videoSizePercentLabel;
    IRLabel videoSizePercentInput;
    IRLabel percentLabel;
    int videoSizePercentPreviousValue = 65;
    
    void videoSizePercentChangedAction();
    int videoSizePercentVal = 65;

    // --------------------------------------------------

    void createButton(TextButton& button, String text);
    

    void buttonClicked(Button* button) override;
    
    // --------------------------------------------------
    
    VideoAnnotaterWindowControllerUIStatus status = NONE;
    // --------------------------------------------------
    
    void createObjectLabel();
    IRLabel textEditorObjectLabel;
    TextButton textEditorObjectButton;
    
    IRLabel shapeObjectLabel;
    TextButton shapeObjectButton;

    IRLabel imageViewerObjectLabel;
    TextButton imageViewerObjectButton;
    
    IRLabel mediumTextEditorObjectLabel;
    TextButton mediumTextEditorObjectButton;
    
    IRLabel smallTextEditorObjectLabel;
    TextButton smallTextEditorObjectButton;

    // --------------------------------------------------
};
#endif /* VideoAnnotaterWindowControllerUI_hpp */
