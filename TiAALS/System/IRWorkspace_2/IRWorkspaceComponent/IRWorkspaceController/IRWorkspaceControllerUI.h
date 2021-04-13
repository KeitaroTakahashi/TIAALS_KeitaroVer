//
//  IRWorkspaceControllerUI.h
//  TIAALS_LIGHT
//
//  Created by Keitaro on 12/03/2021.
//

#ifndef IRWorkspaceControllerUI_h
#define IRWorkspaceControllerUI_h

#include "IRStrComponent.hpp"
#include "IRLabel.h"
#include "KLib.h"

class IRWorkspaceControllerUI : public Component,
public IRStrComponent,
public ChangeBroadcaster
{
public:
    
    enum uiStatus
    {
        NONE,
        TITLE,
        ASPECT_RATIO,
        WIDTH,
        HEIGHT,
        X,
        Y
    };
    
    
    IRWorkspaceControllerUI(IRStr* str) : IRStrComponent(str)
    {
        this->aspectRatio = Rectangle<float>(0, 0, 16, 9);
        this->initialBounds = Rectangle<int> (0, 0, 800, 600);

        createUI();
        createAspectRatioBox();
    }
    
    ~IRWorkspaceControllerUI()
    {
        //this->aspectRatioBox.clear();
    }
    
    
    uiStatus getStatus() const { return this->status; }
    
    int getSelectedAspectRatioId() const { return this->aspectRatioBox.getSelectedId(); }
    
    String getTitleText() const { return this->titleLabel.getText(); }
    
    Rectangle<int> getInitialBounds() const { return this->initialBounds; }
    
    Rectangle<float> getAspectRatio() const { return this->aspectRatio; }
    
    void setAspectRatio(Rectangle<float> ratio)
    {
        this->aspectRatio = ratio;
        this->aspectRatioWLabelInput.setText(String(ratio.getWidth()), dontSendNotification);
        this->aspectRatioHLabelInput.setText(String(ratio.getHeight()), dontSendNotification);
    }
    
    void setInitialBounds(int x, int y, int w, int h)
    {
        this->initialBounds = Rectangle<int>(x,y,w,h);
        
        this->widthLabelInput.setText(String(w), dontSendNotification);
        this->heightLabelInput.setText(String(h), dontSendNotification);
        this->xLabelInput.setText(String(x), dontSendNotification);
        this->yLabelInput.setText(String(y), dontSendNotification);

    }
private:
    
    void resized() override
    {
        int y = 10;
        int yIncrement = 30;
        int yBigIncrement = 40;
        
        int h = 30;

        int menuWidth = getWidth() - 20;

        this->titleLabel.setBounds               (10, y, 50, h);
        this->titleLabelInput.setBounds          (60, y, getWidth() - 70, h);

        y += yBigIncrement;

        this->aspectRatioLabel.setBounds               (10, y, 100, h);
        y += yIncrement;
        this->aspectRatioBox.setBounds          (10, y, menuWidth, h);
        
        if(this->aspectRatioBox.getSelectedId() == 5)
        {
            y += yBigIncrement;

            this->aspectRatioWLabelInput.setBounds(10, y, 70, h);
            this->dotLabel3.setBounds(85, y, 20, h);
            this->aspectRatioHLabelInput.setBounds(110, y, 70, h);
        }
                
        y += yBigIncrement  ;

        this->widthLabel.setBounds               (10, y, 70, h);
        this->heightLabel.setBounds              (110, y, 70, h);
        
        y += yIncrement;
        this->widthLabelInput.setBounds          (10, y, 70, h);
        this->dotLabel.setBounds                 (85, y, 20, h);
        this->heightLabelInput.setBounds         (110, y, 70, h);
        
        y += yIncrement;
        this->xLabel.setBounds                    (10, y, 70, h);
        this->yLabel.setBounds              (110, y, 70, h);
        
        y += yIncrement;
        this->xLabelInput.setBounds          (10, y, 70, h);
        this->dotLabel2.setBounds            (85, y, 20, h);
        this->yLabelInput.setBounds         (110, y, 70, h);
        
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
        g.setColour(Colours::black);
        int y1 = this->titleLabel.getY() + this->titleLabel.getHeight() + 10;
        g.drawLine(0, y1, getWidth(), y1);
        
        y1 = widthLabel.getY();
        g.drawLine(0, y1, getWidth(), y1);

        
    }
    
    IRLabel titleLabel;
    IRLabel titleLabelInput;
    
    IRLabel aspectRatioLabel;
    ComboBox aspectRatioBox;
    IRLabel aspectInputLabel;
    IRLabel aspectRatioWLabelInput;
    IRLabel aspectRatioHLabelInput;
    IRLabel dotLabel3;

    IRLabel xLabel;
    IRLabel xLabelInput;
    
    IRLabel dotLabel2;
    
    IRLabel yLabel;
    IRLabel yLabelInput;
    
    IRLabel widthLabel;
    IRLabel widthLabelInput;
    
    IRLabel dotLabel;
    
    IRLabel heightLabel;
    IRLabel heightLabelInput;
    
    // --------------------------------------------------
    Rectangle<int> initialBounds;
    Rectangle<float> aspectRatio;
    
    String title;
    // --------------------------------------------------

    uiStatus status = NONE;
    
    // --------------------------------------------------

    void createUI()
    {
        
        createLabel(this->titleLabel, "Title : ", false, false);
        createLabel(this->titleLabelInput, "Untitled", true, true);
        this->titleLabelInput.onTextChange = [this] { titleTextChangedAction(); };
        createLabel(this->aspectRatioLabel, "Space aspect : ", false, false);
        
        createLabel(this->aspectRatioWLabelInput, "16", true, true);
        createLabel(this->aspectRatioHLabelInput, "9", true, true);
        this->aspectRatioWLabelInput.onTextChange = [this]{ aspectRatioWChangedAction(); };
        this->aspectRatioHLabelInput.onTextChange = [this]{ aspectRatioHChangedAction(); };

        createLabel(this->dotLabel3, " : ", false, false);

        createLabel(this->widthLabel, "Width : ", false, false);
        createLabel(this->heightLabel, "height : ", false, false);
        createLabel(this->widthLabelInput, "640", false, false);
        createLabel(this->heightLabelInput, "480", false, false);
        this->widthLabelInput.onTextChange = [this] { widthTextChangedAction(); };
        this->heightLabelInput.onTextChange = [this] { heightTextChangedAction(); };
        
        createLabel(this->xLabel, "X : ", false, false);
        createLabel(this->yLabel, "Y : ", false, false);
        createLabel(this->xLabelInput, "0", false, false);
        createLabel(this->yLabelInput, "0", false, false);
        this->xLabelInput.onTextChange = [this] { xLabelTextChangedAction(); };
        this->yLabelInput.onTextChange = [this] { yLabelTextChangedAction(); };

        createLabel(this->dotLabel, " : ", false, true);

    }

    void createAspectRatioBox()
    {
        addAndMakeVisible(this->aspectRatioBox);
        
        this->aspectRatioBox.setColour(ComboBox::backgroundColourId, getStr()->SYSTEMCOLOUR.fundamental);
        this->aspectRatioBox.setColour(ComboBox::outlineColourId, getStr()->SYSTEMCOLOUR.contents);
        this->aspectRatioBox.setColour(ComboBox::focusedOutlineColourId, getStr()->SYSTEMCOLOUR.contents);

        
        this->aspectRatioBox.addItem("1 : 1",    1);
        this->aspectRatioBox.addItem("3 : 2",    2);
        this->aspectRatioBox.addItem("4 : 3",    3);
        this->aspectRatioBox.addItem("16 : 9",   4);
        this->aspectRatioBox.addItem("User defined",   5);

        this->aspectRatioBox.setSelectedId(3, dontSendNotification);
        this->aspectRatioBox.onChange = [this] { aspectRatioChanged(); };
    }

    void aspectRatioChanged()
    {
        
        std::cout <<"UI aspectRatioChanged\n";
        this->status = ASPECT_RATIO;
        sendChangeMessage();
        
        if(this->aspectRatioBox.getSelectedId() == 5)
        {
            this->aspectRatioWLabelInput.setVisible(true);
            this->dotLabel3.setVisible(true);
            this->aspectRatioHLabelInput.setVisible(true);
        }else{
            this->aspectRatioWLabelInput.setVisible(false);
            this->dotLabel3.setVisible(false);
            this->aspectRatioHLabelInput.setVisible(false);
        }
        
        resized();
        repaint();
    }
    
    // --------------------------------------------------
    
    void createLabel(IRLabel& label, String text, bool border, bool isEditable)
    {
        label.setText(text, dontSendNotification);
        label.enableBorder(border);
        //label.setColour(Label::outlineColourId, Colours::white);
        addAndMakeVisible(label);
        label.setEditable(isEditable);
    }
    
    void titleTextChangedAction()
    {
        this->title = this->titleLabelInput.getText();
        
        this->status = TITLE;
        sendChangeMessage();
    }
    
    void widthTextChangedAction()
    {
        this->status = WIDTH;
        sendChangeMessage();
    }
    
    void heightTextChangedAction()
    {
        this->status = HEIGHT;
        sendChangeMessage();
    }
    
    void xLabelTextChangedAction()
    {
        this->status = X;
        sendChangeMessage();
    }
    
    void yLabelTextChangedAction()
    {
        this->status = Y;
        sendChangeMessage();
    }
    
    void aspectRatioWChangedAction()
    {
        String val = this->aspectRatioWLabelInput.getText();
        if(!isDigitNumber(val))
        {
            val = "4";
            this->aspectRatioWLabelInput.setText("4", dontSendNotification);
        }
        
        int num = std::stoi(val.toStdString());
        
        if(num > 200)
        {
            KLib().showErrorMessage(String(num) + " is too large number.");
            num = 200;
            
        }
        this->aspectRatio.setWidth(num);

        this->status = ASPECT_RATIO;
        sendChangeMessage();
        

    }
    
    void aspectRatioHChangedAction()
    {
        String val = this->aspectRatioHLabelInput.getText();
        if(!isDigitNumber(val))
        {
            val = "3";
            this->aspectRatioHLabelInput.setText("3", dontSendNotification);
        }
        
        int num = std::stoi(val.toStdString());
        
        if(num > 100)
        {
            KLib().showErrorMessage(String(num) + " is too large number.");
            num = 100;
            
        }
        this->aspectRatio.setHeight(num);

        this->status = ASPECT_RATIO;
        sendChangeMessage();
        

    }
 
    // --------------------------------------------------
    
    bool isDigitNumber(String text)
    {
        std::string s = text.toStdString();
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    
    
};
#endif /* IRWorkspaceControllerUI_h */
