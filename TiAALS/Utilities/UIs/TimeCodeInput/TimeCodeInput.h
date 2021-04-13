//
//  TimeCodeInput.h
//  IRiMaS
//
//  Created by Keitaro on 12/12/2019.
//

#ifndef TimeCodeInput_h
#define TimeCodeInput_h
#include <string>
#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "KLib.h"

class TimeCodeInput : public Component,
public IRStrComponent,
Label::Listener
{
public:
    TimeCodeInput(IRStr *str, float videoLengthInSecond) :
    IRStrComponent(str),
    videoLengthInSecond(videoLengthInSecond)
    {
        makeDigitLabel(this->hourLabelBegin);
        makeDigitLabel(this->minLabelBegin);
        makeDigitLabel(this->secLabelBegin);
        makeDigitLabel(this->msecLabelBegin, true);

        makeDigitLabel(this->hourLabelEnd);
        makeDigitLabel(this->minLabelEnd);
        makeDigitLabel(this->secLabelEnd);
        makeDigitLabel(this->msecLabelEnd, true);

        //setMaxTimeCode(videoLengthInSecond);
    }
    
    ~TimeCodeInput()
    {
        
    }
    // ==================================================

    void paint(Graphics& g) override
    {
        g.setColour(getStr()->SYSTEMCOLOUR.text);
        g.drawText(":", this->hourLabelBegin.getX() + this->hourLabelBegin.getWidth() - 6,
                   4, 10, 30, Justification::centred);
        g.drawText(":", this->minLabelBegin.getX() + this->minLabelBegin.getWidth() - 6,
                   4, 10, 30, Justification::centred);
        g.drawText(".", this->secLabelBegin.getX() + this->secLabelBegin.getWidth() - 6,
                   5, 10, 30, Justification::centred);
        g.drawText("-", this->msecLabelBegin.getX() + this->msecLabelBegin.getWidth(),
                   5, 10, 30, Justification::centred);
        
        g.drawText(":", this->hourLabelEnd.getX() + this->hourLabelEnd.getWidth() - 6,
                   4, 10, 30, Justification::centred);
        g.drawText(":", this->minLabelEnd.getX() + this->minLabelEnd.getWidth() - 6,
                   4, 10, 30, Justification::centred);
        g.drawText(".", this->secLabelEnd.getX() + this->secLabelEnd.getWidth() - 6,
                   4, 10, 30, Justification::centred);


        g.drawRect(getLocalBounds().reduced(2), 1);
    }
    
    void resized() override
    {
        int margin = 0;
        int w = 25;
        int h = 30;
        int x = 2;
        this->hourLabelBegin.    setBounds(x, 5, w, h);
        x += margin + w;
        this->minLabelBegin.     setBounds(x, 5, w, h);
        x += margin + w;
        this->secLabelBegin.     setBounds(x, 5, w, h);
        x += margin + w;
        this->msecLabelBegin.    setBounds(x, 5, 32, h);
        
        x += 35;
        
        this->hourLabelEnd.    setBounds(x, 5, w, h);
        x += margin + w;
        this->minLabelEnd.     setBounds(x, 5, w, h);
        x += margin + w;
        this->secLabelEnd.     setBounds(x, 5, w, h);
        x += margin + w;
        this->msecLabelEnd.    setBounds(x, 5, 32, h);
        
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
    void setMaxTimeCode(float sec)
    {
        int h,m,s,ms;
        s2hms(sec, h, m, s, ms);
        
        this->maxH = h;
        this->maxM = m;
        this->maxS = s;
        this->maxMS = ms;
        
    }
  
    // ==================================================
    float getBeginTimeCode() const
    {
 
        int h = std::stoi(this->hourLabelBegin.getText().toStdString());
        int m = std::stoi(this->minLabelBegin.getText().toStdString());
        int sec = std::stoi(this->secLabelBegin.getText().toStdString());
        int msec = std::stoi(this->msecLabelBegin.getText().toStdString());
        
        float s = (float)sec + (float)msec /1000.0;

        
        float t = (float)(h * 3600 + m * 60) + s;
        return t;
    }
    
    std::string getBeginTimeInString()
    {
        return getTimeCodeInString(getBeginTimeCode());
    }

    void setBeginTime(std::string beginTime)
    {
        std::vector<std::string> buf = KLib().StringSplit(beginTime, ':');
        if(buf.size() < 3)
        {
            std::cout << "ERRROR : TimeCodeInput::setBeginTime() beginTime wrong format " << beginTime << std::endl;
            return ;
        }
        
        std::string h = buf[0];
        std::string m = buf[1];
        std::string s = buf[2];

        std::vector<std::string> buf2 = KLib().StringSplit(s, ',');
        std::string s2 = buf2[0];
        std::string ms = buf2[1];

        this->hourLabelBegin.setText    (h, dontSendNotification);
        this->minLabelBegin.setText     (m, dontSendNotification);
        this->secLabelBegin.setText     (s2, dontSendNotification);
        this->msecLabelBegin.setText    (ms, dontSendNotification);
    }
    
    void setBeginTime(float beginTime)
    {

        //setBeginTime(getTimeCodeInString(beginTime));
        
        int h,m,s,ms;
        std::string h_s, m_s, s_s, ms_s;
        s2hms(beginTime, h, m, s, ms);
        
        if(h < 10) h_s = "0" + std::to_string(h);
        else h_s = std::to_string(h);
        if(m < 10) m_s = "0" + std::to_string(m);
        else m_s = std::to_string(m);
        if(s < 10) s_s = "0" + std::to_string(s);
        else s_s = std::to_string(s);
        
        if(ms < 100)
        {
            if(ms < 10) ms_s = "00" + std::to_string(ms);
            else ms_s = "0" + std::to_string(ms);
        }else ms_s = std::to_string(ms);
        
        this->hourLabelBegin.setText    (h_s, dontSendNotification);
        this->minLabelBegin.setText     (m_s, dontSendNotification);
        this->secLabelBegin.setText     (s_s, dontSendNotification);
        this->msecLabelBegin.setText    (ms_s, dontSendNotification);
    }
    
    float getEndTimeCode() const
    {
        int h = std::stoi(this->hourLabelEnd.getText().toStdString());
        int m = std::stoi(this->minLabelEnd.getText().toStdString());
        float s = (float)std::stof(this->secLabelEnd.getText().toStdString()) +
                  (float)(std::stoi(this->msecLabelEnd.getText().toStdString()))/1000.0;

        
        float t = (float)(h * 3600 + m * 60) + s;
        return t;
    }
    
    std::string getEndTimeInString()
    {
        return getTimeCodeInString(getEndTimeCode());
    }
    
    void setEndTime(std::string endTime)
    {
        std::vector<std::string> buf = KLib().StringSplit(endTime, ':');
        if(buf.size() < 3)
        {
            std::cout << "ERRROR : TimeCodeInput::setEndTime() endTime wrong format " << endTime << std::endl;
            return ;
        }
        
        std::string h = buf[0];
        std::string m = buf[1];
        std::string s = buf[2];

        std::vector<std::string> buf2 = KLib().StringSplit(s, ',');
                
        std::string s2 = buf2[0];
        std::string ms = buf2[1];

        this->hourLabelEnd.setText    (h, dontSendNotification);
        this->minLabelEnd.setText     (m, dontSendNotification);
        this->secLabelEnd.setText     (s2, dontSendNotification);
        this->msecLabelEnd.setText    (ms, dontSendNotification);
    }
    
    void setEndTime(float endTime)
    {
        //setEndTime(getTimeCodeInString(endTime));
        
        int h,m,s,ms;
        std::string h_s, m_s, s_s, ms_s;
        s2hms(endTime, h, m, s, ms);
        
        if(h < 10) h_s = "0" + std::to_string(h);
        else h_s = std::to_string(h);
        if(m < 10) m_s = "0" + std::to_string(m);
        else m_s = std::to_string(m);
        if(s < 10) s_s = "0" + std::to_string(s);
        else s_s = std::to_string(s);
        
        if(ms < 100)
        {
            if(ms < 10) ms_s = "00" + std::to_string(ms);
            else ms_s = "0" + std::to_string(ms);
        }else ms_s = std::to_string(ms);
        
        this->hourLabelEnd.setText    (h_s, dontSendNotification);
        this->minLabelEnd.setText     (m_s, dontSendNotification);
        this->secLabelEnd.setText     (s_s, dontSendNotification);
        this->msecLabelEnd.setText    (ms_s, dontSendNotification);
    }
    
    std::string getTimeCodeInString(float timeCodeInSec)
    {
        int h,m,s,ms;
        std::string h_s, m_s, s_s, ms_s;
        s2hms(timeCodeInSec, h, m, s, ms);
        
        if(h < 10) h_s = "0" + std::to_string(h);
        else h_s = std::to_string(h);
        if(m < 10) m_s = "0" + std::to_string(m);
        else m_s = std::to_string(m);
        if(s < 10) s_s = "0" + std::to_string(s);
        else s_s = std::to_string(s);
        
        if(ms < 100)
        {
            if(ms < 10) ms_s = "00" + std::to_string(ms);
            else ms_s = "0" + std::to_string(ms);
        }else ms_s = std::to_string(ms);

        std::string timeCode = h_s + ":" + m_s + ":" + s_s + "," + ms_s;
        return timeCode;
    }
    // ==================================================
    
    void setVideoLegnth(int videoLengthInSecond)
    {
        //setMaxTimeCode(videoLengthInSecond);
    }
    
    // ==================================================

    std::function<void()> timeCodeChangedCallback;

private:
    
    // ==================================================
    void labelTextChanged (Label* labelThatHasChanged) override
    {
        std::string val = labelThatHasChanged->getText().toStdString();
        
        std::cout << "label changed = " << val << std::endl;
        
        // check if the input value is digit integer number and otherw
        try
        {
            // fix if BeginLabels are greater than EndLabels
            fixBeginAndEnd();
            // fix if Labels are greater than max values
            fixLabelWithMaxVal();
        }
        catch (const std::invalid_argument &e)
        {
           std::cout << "Bad input " << val << std::endl;
            labelThatHasChanged->setText("00", dontSendNotification);
        }
        
        if(this->timeCodeChangedCallback != nullptr)
            this->timeCodeChangedCallback();

    }
    // ==================================================
    
    void makeDigitLabel(Label& label, bool ms = false)
    {
        addAndMakeVisible(label);
        
        if(ms) label.setText("000", dontSendNotification);
        else   label.setText("00", dontSendNotification);
        
        label.setEditable(true);
        label.addListener(this);
    }
    
    void setLabelVal(float beginSec, float endSec)
    {
        int h,m,s,ms;
        
        s2hms(beginSec, h, m, s, ms);
        
        if(h < 10) this->hourLabelBegin.    setText("0" + String(h), dontSendNotification);
        else this->hourLabelBegin.          setText(String(h), dontSendNotification);
        if(m < 10) this->minLabelBegin.     setText("0" + String(m), dontSendNotification);
        else this->minLabelBegin.           setText(String(m), dontSendNotification);
        if(s < 10) this->secLabelBegin.     setText("0" + String(s), dontSendNotification);
        else this->secLabelBegin.           setText(String(s), dontSendNotification);
            
        if(ms < 100)
        {
            if(ms < 10) this->msecLabelBegin.   setText("00" + String(ms), dontSendNotification);
            else this->msecLabelBegin.   setText("0" + String(ms), dontSendNotification);
        }else{
            this->msecLabelBegin.setText(String(ms), dontSendNotification);
        }

        s2hms(endSec, h, m, s, ms);

        if(h < 10) this->hourLabelEnd.    setText("0" + String(h), dontSendNotification);
        else this->hourLabelEnd.          setText(String(h), dontSendNotification);
        if(m < 10) this->minLabelEnd.     setText("0" + String(m), dontSendNotification);
        else this->minLabelEnd.          setText(String(m), dontSendNotification);
        if(s < 10) this->secLabelEnd.     setText("0" + String(s), dontSendNotification);
        else this->secLabelEnd.          setText(String(s), dontSendNotification);

        if(ms < 100)
        {
            if(ms < 10) this->msecLabelEnd.   setText("00" + String(ms), dontSendNotification);
            else this->msecLabelEnd.   setText("0" + String(ms), dontSendNotification);
        }else{
            this->msecLabelEnd.setText(String(ms), dontSendNotification);
        }

    }
    // ==================================================
    
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
    
    void fixBeginAndEnd()
    {
        float beginSec, endSec;
        if(isBeginLargerThanEnd(beginSec, endSec))
        {
            std::cout << "begin " << beginSec << " is larger than " << endSec << std::endl;
            endSec = beginSec + 0.1; // add 0.1 sec. duration
            setLabelVal(beginSec, endSec);
        }
    }
    
    bool isBeginLargerThanEnd(float& beginSec, float& endSec)
    {
        beginSec = std::stoi(this->hourLabelBegin.getText().toStdString()) * 3600 +
                   std::stoi(this->minLabelBegin.getText().toStdString()) * 60 +
                   std::stoi(this->secLabelBegin.getText().toStdString());
        
        beginSec += (float)(std::stoi(this->msecLabelBegin.getText().toStdString()))/1000.0;
        
        endSec = std::stoi(this->hourLabelEnd.getText().toStdString()) * 3600 +
                 std::stoi(this->minLabelEnd.getText().toStdString()) * 60 +
                 std::stoi(this->secLabelEnd.getText().toStdString());
        endSec += (float)(std::stoi(this->msecLabelEnd.getText().toStdString()))/1000.0;
        
        
        std::cout << "begin = " << beginSec << " : " << endSec << std::endl;
        if(beginSec > endSec) return true;
        else return false;
    }
    
    void fixLabelWithMaxVal()
    {
        fixDigi(this->hourLabelBegin, maxH);
        fixDigi(this->minLabelBegin, maxM);
        fixDigi(this->secLabelBegin, maxS);
        fixDigi(this->msecLabelBegin, maxMS, true);

        fixDigi(this->hourLabelEnd, maxH);
        fixDigi(this->minLabelEnd, maxM);
        fixDigi(this->secLabelEnd, maxS);
        fixDigi(this->msecLabelEnd, maxMS, true);

    }
    // ==================================================

    Label hourLabelBegin;
    Label minLabelBegin;
    Label secLabelBegin;
    Label msecLabelBegin;
    
    Label hourLabelEnd;
    Label minLabelEnd;
    Label secLabelEnd;
    Label msecLabelEnd;
    
    int maxH = 59;
    int maxM = 59;
    int maxS = 59;
    int maxMS = 999;
    
    
    float videoLengthInSecond;
};
#endif /* TimeCodeInput_h */
