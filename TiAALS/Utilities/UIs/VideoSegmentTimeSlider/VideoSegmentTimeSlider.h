//
//  VideoSegmentTimeSlider.h
//  IRIMAS2020July
//
//  Created by Keitaro on 13/08/2020.
//

#ifndef VideoSegmentTimeSlider_h
#define VideoSegmentTimeSlider_h

#include "TimeCodeInput.h"

class VideoSegmentTimeSlider : public Component,
public IRStrComponent,
Slider::Listener
{
public:
    VideoSegmentTimeSlider(IRStr* str, float videoLengthInSecond) :
    IRStrComponent(str),
    videoLengthInSecond(videoLengthInSecond),
    timeCode(str, videoLengthInSecond)
    {
        this->slider.setSliderStyle(Slider::SliderStyle::TwoValueHorizontal);
        this->slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,
                                     true, 0, 0);
        addAndMakeVisible(this->slider);
        this->slider.addListener(this);
        
        addAndMakeVisible(this->timeCode);
        this->timeCode.timeCodeChangedCallback = [this]{ timeCodeChangedAction(); };
    }
    
    ~VideoSegmentTimeSlider()
    {
        
    }
    
    // ========================================
    void setVideoLengthInSecond(float videoLengthInSecond)
    {
        std::cout << "VideoSegmentTimeSlider::setVideoLengthInSecond : " << videoLengthInSecond << std::endl;
        this->videoLengthInSecond = videoLengthInSecond;
        
        this->slider.setRange(0, videoLengthInSecond, 0.1);
        
        this->slider.setMinValue(0.0);
        this->slider.setMaxValue(videoLengthInSecond);
        //call manually here
        sliderValueChanged(&this->slider);
        
    }
    
    void setSliderValue(float min, float max)
    {
        this->slider.setMinValue(min);
        this->slider.setMaxValue(max);
        
        sliderValueChanged(&this->slider);

    }
    // ========================================
    
    std::function<void()> videoSegmentChangedCallback;

    std::function<void()> videoSegmentMinChangedCallback;
    std::function<void()> videoSegmentMaxChangedCallback;

    // ========================================

    std::vector<float> getSegmentValue()
    {
        std::vector<float> v;
        
        v.push_back(this->slider.getMinValue());
        v.push_back(this->slider.getMaxValue());
        return v;
        
    }
    
private:
    
    // ========================================
    
    void resized() override
    {
        int marginX = 0;
        int marginY = 3;
        
        this->timeCode.setBounds(marginX, marginY, 220, getHeight() - marginY);
        this->slider.setBounds(marginX + 220, marginY,
                               getWidth() - marginX - 220,
                               getHeight());
    }
    
    void paint(Graphics& g) override
    {
    }
    // ========================================
    
    void tastWhenSliderValueChanged()
    {
        this->timeCode.setBeginTime(this->slider.getMinValue());
        this->timeCode.setEndTime(this->slider.getMaxValue());
        
        this->prev_minValue = this->slider.getMinValue();
        this->prev_maxValue = this->slider.getMaxValue();
    }

    void sliderValueChanged (Slider *slider) override
    {
        if(slider == &this->slider)
        {

            // if min value is changed
            if(slider->getMinValue() != this->prev_minValue)
            {

                this->prev_minValue = slider->getMinValue();
                if(this->videoSegmentMinChangedCallback != nullptr)
                    videoSegmentMinChangedCallback();
            }
            
            // if max value is changed
            if(slider->getMaxValue() != this->prev_maxValue)
            {
                this->prev_maxValue = slider->getMaxValue();
                if(this->videoSegmentMaxChangedCallback != nullptr)
                    videoSegmentMaxChangedCallback();
            }
            
            // currently disabled
            /*
            if(this->videoSegmentChangedCallback != nullptr)
                this->videoSegmentChangedCallback();
             */
            
            tastWhenSliderValueChanged();
        }
    }
    
    // ========================================

    void timeCodeChangedAction()
    {
        float maxVal = this->timeCode.getEndTimeCode();
        float minVal = this->timeCode.getBeginTimeCode();
        this->slider.setMaxValue(maxVal, dontSendNotification);
        this->slider.setMinValue(minVal, dontSendNotification);
        
        if(this->videoSegmentChangedCallback != nullptr)
            this->videoSegmentChangedCallback();
    }
    // ========================================

    float videoLengthInSecond;
    
    TimeCodeInput timeCode;
    Slider slider;
    
    double prev_minValue = 0;
    double prev_maxValue = 0;
    // ========================================
    // ========================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VideoSegmentTimeSlider)

};

#endif /* VideoSegmentTimeSlider_h */
