//
//  TimeCode.h
//  IRiMaS
//
//  Created by Keitaro on 20/01/2020.
//

#ifndef TimeCode_h
#define TimeCode_h
#include <string>
#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "KLib.h"

class TimeCode : public Component,
public IRStrComponent,
Label::Listener
{
public:
    TimeCode(IRStr* str, float videoLengthInSecond) :
    IRStrComponent(str),
    videoLengthInSecond(videoLengthInSecond)
    {
        makeDigitLabel(this->hourLabel);
        makeDigitLabel(this->minLabel);
        makeDigitLabel(this->secLabel);
        makeDigitLabel(this->msecLabel, true);
    }
    
    ~TimeCode()
    {
        
    }
    
    // ==================================================
    void paint(Graphics& g) override
    {
        g.setColour(getStr()->SYSTEMCOLOUR.text);
        g.drawText(":", this->hourLabel.getX() + this->hourLabel.getWidth() - 6,
                   4, 10, 30, Justification::centred);
        g.drawText(":", this->minLabel.getX() + this->minLabel.getWidth() - 6,
                   4, 10, 30, Justification::centred);
        g.drawText(".", this->secLabel.getX() + this->secLabel.getWidth() - 6,
                   5, 10, 30, Justification::centred);
    }
    
    void resized() override
    {
        int margin = 0;
        int w = 25;
        int h = 30;
        int x = 2;
        this->hourLabel.    setBounds(x, 5, w, h);
        x += margin + w;
        this->minLabel.     setBounds(x, 5, w, h);
        x += margin + w;
        this->secLabel.     setBounds(x, 5, w, h);
        x += margin + w;
        this->msecLabel.    setBounds(x, 5, 32, h);
    }
    // ==================================================
    void setLabelVal(float timeInSec)
    {
        int h,m,s,ms;
        
        if(timeInSec > this->videoLengthInSecond)
            timeInSec = this->videoLengthInSecond;
        
        s2hms(timeInSec, h, m, s, ms);
        
        if(h < 10) this->hourLabel.    setText("0" + String(h), dontSendNotification);
        else this->hourLabel.          setText(String(h), dontSendNotification);
        if(m < 10) this->minLabel.     setText("0" + String(m), dontSendNotification);
        else this->minLabel.           setText(String(m), dontSendNotification);
        if(s < 10) this->secLabel.     setText("0" + String(s), dontSendNotification);
        else this->secLabel.           setText(String(s), dontSendNotification);
            
        if(ms < 100)
        {
            if(ms < 10) this->msecLabel.setText("00" + String(ms), dontSendNotification);
            else this->msecLabel.setText("0" + String(ms), dontSendNotification);
        }else{
            this->msecLabel.setText(String(ms), dontSendNotification);
        }
    }
    // ==================================================
    void s2hms(float sec, int& h, int& m, int& s, int& ms)
    {
        h = floor(sec) / 3600;
        float sec2 = sec - (h * 3600);
        m = floor(sec2) / 60;
        float sec3 = sec2 - (m * 60);
        s = floor(sec3);
        float sec4 = sec3 - s;
        ms = floor(sec4 * 1000.0);
        
    }
    // ==================================================
    float getTimeCodeInSec() const
    {
        int h = std::stoi(this->hourLabel.getText().toStdString());
        int m = std::stoi(this->minLabel.getText().toStdString());
        float s = (float)std::stof(this->secLabel.getText().toStdString()) +
                  (float)(std::stoi(this->msecLabel.getText().toStdString()))/1000.0;

        
        float t = (float)(h * 3600 + m * 60) + s;
        return t;
    }
    // ==================================================
    std::function<void()> timeCodeChangedCallback;
    // ==================================================
    
    void setVideoLengthInSec(float videoLengthInSecond) { this->videoLengthInSecond = videoLengthInSecond; }
    float getVideoLengthInSec() const { return this->videoLengthInSecond; }

private:
    void makeDigitLabel(Label& label, bool ms = false)
    {
        addAndMakeVisible(label);
        
        if(ms) label.setText("000", dontSendNotification);
        else   label.setText("00", dontSendNotification);
        
        label.setEditable(true);
        label.addListener(this);
    }
    // ==================================================

    void labelTextChanged (Label* labelThatHasChanged) override
    {
        std::string val = labelThatHasChanged->getText().toStdString();
        
        std::cout << "label changed = " << val << std::endl;
        
        // check if the input value is digit integer number and otherw
        try
        {
            // fix if Labels are greater than max values
            fixLabelWithMaxVal();
            // fix if total value is greater than video duration
            setLabelVal(getTimeCodeInSec());
            
        }
        catch (const std::invalid_argument &e)
        {
           std::cout << "Bad input " << val << std::endl;
            labelThatHasChanged->setText("00", dontSendNotification);
        }
        
        if(this->timeCodeChangedCallback != nullptr)
            this->timeCodeChangedCallback();

    }
    
    void fixDigi(Label& label, int maxVal, bool ms = false)
    {
        std::string s = label.getText().toStdString();
        int digi = std::stoi(s);
        if(digi)
        {
            if(digi > maxVal)
            {
                digi = maxVal;
            }
            
            if(digi < 0) digi = 0;
        }
        
        String text = String(digi);
        
        if(ms)
        {
            if(digi < 100)
            {
                if(digi < 10) label.setText("00" + text, dontSendNotification);
                else label.setText("0" + text, dontSendNotification);
            }else{
                label.setText(text, dontSendNotification);
            }
        }else{
            if(digi < 10) label.setText("0" + text, dontSendNotification);
            else label.setText(text, dontSendNotification);
        }

    }
    
    void fixLabelWithMaxVal()
    {
        fixDigi(this->hourLabel, maxH);
        fixDigi(this->minLabel, maxM);
        fixDigi(this->secLabel, maxS);
        fixDigi(this->msecLabel, maxMS, true);
    }
    // ==================================================
    float videoLengthInSecond = 0;
    // ==================================================
    
    Label hourLabel;
    Label minLabel;
    Label secLabel;
    Label msecLabel;
    
    int maxH = 59;
    int maxM = 59;
    int maxS = 59;
    int maxMS = 999;
    // ==================================================
    // ==================================================
    // ==================================================


};
#endif /* TimeCode_h */
