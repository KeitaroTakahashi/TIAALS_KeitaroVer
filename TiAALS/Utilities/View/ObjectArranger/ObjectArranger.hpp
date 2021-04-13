//
//  ObjectArranger.hpp
//  IRiMaS
//
//  Created by Keitaro on 04/02/2020.
//

#ifndef ObjectArranger_hpp
#define ObjectArranger_hpp

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRColourSettingIcon.h"


class ArrangeController : public Component,
public IRStrComponent,
public ChangeBroadcaster,
public ChangeListener,
private Label::Listener,
private Button::Listener
{
public:
    
    enum ArrangeControllerStatus{
        NONE,
        INPUTWIDTH,
        INPUTHEIGHT,
        INPUTX,
        INPUTY,
        INPUTROTATION,
        
        FRONTBUTTON,
        BACKBUTTON,
        ENCLOSEBUTTON,
        ENCLOSECOLOUR,
        ACTIVATEBUTTON,
        
        TIMECODE_BEGIN,
        TIMECODE_END,
        
        EncloseColourChanged
    };
    
    
    ArrangeController(IRStr* str);
    ~ArrangeController();
    
    void setArrangeController(ArrangeController* controller);
    // =======================================================
    
    void resized() override;
    
    void paint(Graphics& g) override;
    // =======================================================
    // =======================================================
    ArrangeControllerStatus getStatus() const { return this->status; }
    // =======================================================
    // getter
    Rectangle<int> getRectangle();
    int getLabelWidth();
    int getLabelHeight();
    int getLabelX();
    int getLabelY();
    
    bool getEnclosedButtonStatus();
    bool getActivateStatus();
    
    //setter
    void setRectangle(Rectangle<int> rect);
    void setLabelWidth(int width);
    void setLabelHeight(int height);
    void setLabelX(int x);
    void setLabelY(int y);
    // =======================================================

    //Restrict range
    void setRestrictPosition(int min_x, int max_x, int min_y, int max_y);
    void setRestrictSize(int min_w, int max_w, int min_h, int max_h);
    
    // =======================================================

    Colour getEncloseColour() const;
    
    void setEncloseColour(Colour newColour);
    
    void setEncloseToggle(bool flag, NotificationType notification = dontSendNotification);

    void encloseColourChanged();
    // =======================================================

    void setStartTimeSec(float sec);
    void setEndTimeSec(float sec);
    float getStartTimeSec() const { return this->StartTimeSec; }
    float getEndTimeSec() const { return this->EndTimeSec; }
    
    void setBoundType(int boundType) { this->boundType = boundType;}
    int getBoundType() const { return this->boundType; }
    
    float getRotation() const { return this->rotation; }
    void setRotation(float rotation);
    // =======================================================

private:
    // =======================================================

    void changeListenerCallback(ChangeBroadcaster* source) override;

    // =======================================================
    // Restrict
    
    int res_min_x = 0;
    int res_min_y = 0;
    int res_min_w = 0;
    int res_min_h = 0;
    int res_max_x = 99999;
    int res_max_y = 99999;
    int res_max_w = 99999;
    int res_max_h = 99999;

    
    void fixMinMax(int& val, int min, int max);
    // =======================================================

    Label labelSize;
    Label labelWidth;
    Label labelHeight;
    
    Label labelSizePixel;
    
    Label InputWidth;
    void InputWidthChanged();
    Label InputHeight;
    void InputHeightChanged();

    Label labelPosition;
    Label labelX;
    Label labelY;
    
    Label labelRotation;
    Label InputRotation;
    void InputRotationChanged();
    float rotation = 0.0;
    
    Label InputX;
    void InputXChanged();
    Label InputY;
    void InputYChanged();
    
    Label LabelTimeCode;
    Label labelTimeCodeBegin;
    Label InputTimeCodeBegin;
    Label labelTimeCodeEnd;
    Label InputTimeCodeEnd;
    void InputTimeCodeBeginChanged();
    void InputTimeCodeEndChanged();

    Label PositionLabelPixel;
    
    void createLabel(Label& label, String text);
    void createSmallLabel(Label& label, String text);
    void createToggleButton(ToggleButton& button, String text);
    // =======================================================

    Label layerLabel;
    TextButton frontButton;
    TextButton backButton;
    
    
    Label statusLabel;
    ToggleButton encloseButton;
    IRColourSettingIcon encloseColour;
    ToggleButton activateButton;
    
    
    // Annotation Time
    Label StartTimeLabel;
    Label InputStartTime;
    Label EndTimeLabel;
    Label InputEndTime;
    
    float StartTimeSec = 0;
    float EndTimeSec = 0;
    
    int boundType = 0;

    void createButton(TextButton& button, String text);
    void buttonClicked(Button* button) override;
    // =======================================================

    void labelTextChanged (Label* labelThatHasChanged) override;
    void LabelChangeListener(Label* label);
    // =======================================================
    ArrangeControllerStatus status = NONE;
    // =======================================================
        // use this to avoid infinite loop
    bool shouldUpdate = true;
    
    // =======================================================

    bool isDigitNumber(String text)
    {
        std::string s = text.toStdString();
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

};

#endif /* ObjectArranger_hpp */
