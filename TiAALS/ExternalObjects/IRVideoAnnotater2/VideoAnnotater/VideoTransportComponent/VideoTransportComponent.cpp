//
//  VideoTransportComponent.cpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 25/03/2021.
//

#include "VideoTransportComponent.hpp"

VideoTransportComponent::VideoTransportComponent(IRStr* str, VideoAnnotaterBase* base) :
IRStrComponent(str),
VideoAnnotaterDelegate(base),
timeCode(str, 0),
videoSegmentSlider(str, 0)
{
    /*
    addAndMakeVisible(&this->openVideoButton);
    this->openVideoButton.onClick = [this]{ openVideoButtonClicked(); };
    this->openVideoButton.setButtonText("Open Video");
*/
    createButton(&this->addEventButton, getStr()->ICONBANK->icon_newSlide);
    this->addEventButton.setDrawCircle(false);
    this->addEventButton.setDrawRoundedSquare(true);
    this->addEventButton.onClick = [this]{ addEventButtonClickedAction(); };
    
    createButton(&this->deleteEventButton, getStr()->ICONBANK->icon_deleteSlide);
    this->deleteEventButton.setDrawCircle(false);
    this->deleteEventButton.setDrawRoundedSquare(true);
    this->deleteEventButton.onClick = [this]{ deleteEventButtonClickedAction(); };


    //controller
    createButton(&this->playButton, getStr()->ICONBANK->icon_play);
    this->playButton.onClick = [this]{ playButtonClickedAction(); };
    createButton(&this->stopButton, getStr()->ICONBANK->icon_stop);
    this->stopButton.onClick = [this]{ stopButtonClickedAction(); };
    
    addAndMakeVisible(this->timeCode);
    this->timeCode.timeCodeChangedCallback = [this]{timeCodeChanged();};
    
    this->timeCodeSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    this->timeCodeSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,
                                            true, 0, 0);
    addAndMakeVisible(this->timeCodeSlider);
    this->timeCodeSlider.addListener(this);
    
    
    addAndMakeVisible(this->videoSegmentSlider);
    //this->videoSegmentSlider.videoSegmentChangedCallback = [this]{ videoSegmentChangedAction(); };
    this->videoSegmentSlider.videoSegmentMinChangedCallback = [this] { videoSegmentMinChangedAction(); };
    this->videoSegmentSlider.videoSegmentMaxChangedCallback = [this] { videoSegmentMaxChangedAction(); };

}

VideoTransportComponent::~VideoTransportComponent()
{
    
}
// ==================================================

void VideoTransportComponent::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.setColour(getStr()->SYSTEMCOLOUR.fundamental);

    g.drawLine(0, getHeight() / 2,
               getWidth(), getHeight() / 2);
}

void VideoTransportComponent::resized()
{
    int h = 30;
    
    //this->openVideoButton.setBounds(getWidth() - 100, 5, 90, 30);
    
    juce::Point<int> b = juce::Point<int> (((float)h / this->addEventButton.getAspectRatio()), h);
    int marginX = 5;
    int x = marginX;
    
    this->videoSegmentSlider.setBounds(x, b.getY() + 5, getWidth(), 40);
    
    this->addEventButton.setBounds(x, 5, b.getX(), b.getY());
    x += marginX + b.getX();
    this->deleteEventButton.setBounds(x, 5, b.getX(), b.getY());
    
    float ratio = this->playButton.getAspectRatio();
    int buttonWidth = 30;
    int buttonHeight = buttonWidth * ratio;
    
    x += (marginX * 2) + b.getX(); // one more margin
    this->playButton.setBounds(x, 5, buttonWidth, buttonHeight);
    x += marginX + buttonWidth;
    this->stopButton.setBounds(x, 5, buttonWidth, buttonHeight);
    
    x += (marginX * 2) + buttonWidth; // one more margin
    this->timeCode.setBounds(x, 0, 110, getHeight());
    
    x += (marginX) + this->timeCode.getWidth();
    this->timeCodeSlider.setBounds(x, 0, getWidth() - x, 30);
    
    

}
// ==================================================

void VideoTransportComponent::addEventButtonClickedAction()
{
    this->status = addEventButtonClicked;
    sendChangeMessage();
}

void VideoTransportComponent::deleteEventButtonClickedAction()
{
    this->status = deleteEventButtonClicked;
    sendChangeMessage();
}
// ==================================================

void VideoTransportComponent::openVideoButtonClicked()
{
    this->status = OpenVideoFile;
    sendChangeMessage();
}

void VideoTransportComponent::openAnnotationButtonClicked()
{
    this->status = OpenAnnotationFile;
    sendChangeMessage();
}

void VideoTransportComponent::saveAnnotationButtonClicked()
{
    this->status = SaveAnnotationFile;
    sendChangeMessage();
}
// ==================================================

void VideoTransportComponent::setVideoLengthInSec(float videoLengthInSec)
{
    
    std::cout << "setVideoLengthInSec : " << videoLengthInSec << std::endl;
    this->videoLengthInSec = videoLengthInSec;
    
    this->timeCode.setVideoLengthInSec(videoLengthInSec);
    
  
    if(videoLengthInSec > 0)
    {
        std::cout<< "videoLengthInSec = " << videoLengthInSec << std::endl;
        this->timeCodeSlider.setRange(0.0, (double)videoLengthInSec, 0.1);
        this->videoSegmentSlider.setVideoLengthInSecond((double)videoLengthInSec);
        //this->timeCodeSlider.setValue(0.0);

    }
    
    std::cout << "slider max = "<< this->timeCodeSlider.getMaximum() << std::endl;
}

void VideoTransportComponent::setCurrentPlayingPosition(double pos)
{
    setCurrentPlayingPositionLabel(pos);
    // VideoAnnotationDelegate
    setCurrentVideoPosition(pos);
}


void VideoTransportComponent::setCurrentPlayingPositionLabel(double pos)
{
    this->timeCodeSlider.setValue(pos, dontSendNotification);
    this->timeCode.setLabelVal(pos);

}


void VideoTransportComponent::setVideoRange(float begin, float end)
{
    if(begin > 0 && begin >= end)
    {
        begin = end - 0.1;
    }
    this->timeCodeSlider.setRange(begin, end);
    this->videoSegmentSlider.setSliderValue(begin, end);
    
}
// ==================================================

void VideoTransportComponent::createButton(IRImageButton* button, IRIconBank::IRIconImage img)
{
    if(getStr()->SYSTEMCOLOUR.isWhiteBased)
        button->setImage(img.black);
    else  button->setImage(img.white);
    addAndMakeVisible(button);
}
// ==================================================
void VideoTransportComponent::timeCodeChanged()
{
    float timeInSec = this->timeCode.getTimeCodeInSec();
    /*
    std::cout << "timeInSec = " << timeInSec << " of " << this->timeCode.getVideoLengthInSec() << " : " << this->timeCodeSlider.getMaxValue() << std::endl;*/
    if(timeInSec > this->videoLengthInSec)
    {
        timeInSec = this->videoLengthInSec;
    }
    this->timeCodeSlider.setValue(timeInSec, dontSendNotification);
    
    this->status = playPositionChanged;
    sendChangeMessage();

}

void VideoTransportComponent::sliderValueChanged (Slider *slider)
{
    if(slider == &this->timeCodeSlider)
    {
        
        float val = slider->getValue();
        this->timeCode.setLabelVal(val);
        this->status = playPositionChanged;
        sendChangeMessage();
        
        
        //VideoAnnotationDelegate
        setCurrentVideoPosition((double)val);
    }
}
// ==================================================

void VideoTransportComponent::videoSegmentChangedAction()
{
    this->status = videoSegmentChanged;
    sendChangeMessage();
}

void VideoTransportComponent::videoSegmentMinChangedAction()
{
    
    float begin = this->videoSegmentSlider.getSegmentValue()[0];
    float end = this->videoSegmentSlider.getSegmentValue()[1];
    setVideoRange(begin, end);
    setCurrentPlayingPosition(begin);
    
    changeVideoSegment(begin, end); // delegate
   
    // callback to sync : note! sendChangeMessage() does not sync
    if(this->videoSegmentMinChangedCallback != nullptr)
        this->videoSegmentMinChangedCallback();
   
}

void VideoTransportComponent::videoSegmentMaxChangedAction()
{

    float begin = this->videoSegmentSlider.getSegmentValue()[0];
    float end = this->videoSegmentSlider.getSegmentValue()[1];
    setVideoRange(begin, end);
    setCurrentPlayingPosition(end);
    
    changeVideoSegment(begin, end); // delegate


    // callback to sync : note! sendChangeMessage() does not sync
    if(this->videoSegmentMaxChangedCallback != nullptr)
        this->videoSegmentMaxChangedCallback();
  
}
// ==================================================
// ==================================================
