//
//  VideoAnnotaterWindowControllerUI.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 24/03/2021.
//

#include "VideoAnnotaterWindowControllerUI.hpp"

VideoAnnotaterWindowControllerUI::VideoAnnotaterWindowControllerUI(IRStr* str) : IRStrComponent(str)
{
    this->openVideoAnnotaterButton.setButtonText("Open Video");
    this->openVideoAnnotaterButton.addListener(this);
    addAndMakeVisible(this->openVideoAnnotaterButton);
    
    createLabel(this->videoSizePercentLabel, "Video Size Ratio", false, false);
    createLabel(this->videoSizePercentInput, "65", true, true);
    createLabel(this->percentLabel, " % ", false, false);
    this->videoSizePercentInput.onTextChange = [this] { videoSizePercentChangedAction(); };
    
    createObjectLabel();
}

VideoAnnotaterWindowControllerUI::~VideoAnnotaterWindowControllerUI()
{
    //this->workspaceController.reset();
}

void VideoAnnotaterWindowControllerUI::resized()
{
    int y = 0;
    int yIncrement = 30;
    int yBigIncrement = 50;
    
    this->openVideoAnnotaterButton.setBounds(10, y, getWidth() - 20, 30);
    
    y += yBigIncrement;
    this->videoSizePercentLabel.setBounds(0, y, 100, 30);
    this->videoSizePercentInput.setBounds(100, y, 60, 30);
    this->percentLabel.setBounds(160, y, 50, 30);

    y += yBigIncrement;
    
    int lw = 150; // label width
    int bw = 60; // button width
    int bh = 25; // button height
    this->textEditorObjectLabel.setBounds(0, y, lw, bh);
    this->textEditorObjectButton.setBounds(lw, y, bw, bh);
    y += yIncrement;
    this->shapeObjectLabel.setBounds(0, y, lw, bh);
    this->shapeObjectButton.setBounds(lw, y, bw, bh);

    y += yIncrement;
    this->imageViewerObjectLabel.setBounds(0, y, lw, bh);
    this->imageViewerObjectButton.setBounds(lw, y, bw, bh);
    y += yIncrement;
    this->mediumTextEditorObjectLabel.setBounds(0, y, lw, bh);
    this->mediumTextEditorObjectButton.setBounds(lw, y, bw, bh);
    y += yIncrement;
    this->smallTextEditorObjectLabel.setBounds(0, y, lw, bh);
    this->smallTextEditorObjectButton.setBounds(lw, y, bw, bh);



   // this->workspaceController->setBounds(0, y, getWidth(), 400);
}

void VideoAnnotaterWindowControllerUI::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    
    g.setColour(Colours::black);
    int y = this->videoSizePercentLabel.getY() - 10;
    g.drawLine(0, y, getWidth(), y);

    y = this->textEditorObjectLabel.getY() - 10;
    g.drawLine(0, y, getWidth(), y);

}

void VideoAnnotaterWindowControllerUI::createButton(TextButton& button, String text)
{
    button.setButtonText(text);
    addAndMakeVisible(button);
    button.addListener(this);
}

void VideoAnnotaterWindowControllerUI::buttonClicked(Button* button)
{
    if(button == &this->openVideoAnnotaterButton)
    {
        this->status = openVideoFile;
        sendChangeMessage();
    }else if(button == &this->textEditorObjectButton)
    {
        this->status = TEXTEDITOR;
        sendChangeMessage();
    }else if(button == &this->shapeObjectButton)
    {
        this->status = SHAPE;
        sendChangeMessage();
    }else if(button == &this->imageViewerObjectButton)
    {
        this->status = IMAGE;
        sendChangeMessage();
    }else if(button == &this->mediumTextEditorObjectButton)
    {
        this->status = MEDIUMTEXTEDITOR;
        sendChangeMessage();
    }else if(button == &this->smallTextEditorObjectButton)
    {
        this->status = SMALLTEXTEDITOR;
        sendChangeMessage();
    }
}

// ----------------------------------------

void VideoAnnotaterWindowControllerUI::createLabel(IRLabel& label, String text, bool border, bool isEditable)
{
    label.setText(text, dontSendNotification);
    label.enableBorder(border);
    //label.setColour(Label::outlineColourId, Colours::white);
    addAndMakeVisible(label);
    label.setEditable(isEditable);
}

bool VideoAnnotaterWindowControllerUI::isDigitNumber(String text)
{
    std::string s = text.toStdString();
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void VideoAnnotaterWindowControllerUI::videoSizePercentChangedAction()
{
    String text = this->videoSizePercentInput.getText();
    if(isDigitNumber(text))
    {
        int val = std::stoi(text.toStdString());
        if(val > 0)
        {
            if(KLib().showOKCancelMessage("You are about to change video size ratio. This process does not adjust annotations' sizes and positions to the new video size automatically. Are you sure to change the video size ratio?")){
                this->videoSizePercentVal = val;
                this->status = videoSizePercent;
                sendChangeMessage();
            }else{
                this->videoSizePercentInput.setText(String(this->videoSizePercentVal), dontSendNotification);
            }
            
            
            
            
        }else{
            videoSizePercentInputError();
        }
    }else {
        videoSizePercentInputError();
    }
}


void VideoAnnotaterWindowControllerUI::videoSizePercentInputError()
{
    this->videoSizePercentVal = 65;
    this->videoSizePercentInput.setText("65", dontSendNotification);
    KLib().showErrorMessage("Give me an integer number larger than 0.");
}


void VideoAnnotaterWindowControllerUI::createObjectLabel()
{
    createLabel(this->textEditorObjectLabel, "Subtitle : cmd+1", false, false);
    createLabel(this->shapeObjectLabel, "Shape : cmd+2", false, false);
    createLabel(this->imageViewerObjectLabel, "Image : cmd+3", false, false);
    createLabel(this->mediumTextEditorObjectLabel, "Text : cmd+4", false, false);
    createLabel(this->smallTextEditorObjectLabel, "Small text : cmd+5", false, false);

    /*
    createButton(this->textEditorObjectButton, "create");
    createButton(this->shapeObjectButton, "create");
    createButton(this->imageViewerObjectButton, "create");
    createButton(this->mediumTextEditorObjectButton, "create");
    createButton(this->smallTextEditorObjectButton, "create");
*/
    
}

// ---------------------------------------------
void VideoAnnotaterWindowControllerUI::setVideoSizePercent(int val)
{
    this->videoSizePercentInput.setText(String(val), dontSendNotification);
}
