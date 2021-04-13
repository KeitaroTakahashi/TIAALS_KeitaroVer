//
//  IRTitleBarProjectButtonArea.h
//  IRiMaS
//
//  Created by Keitaro on 18/11/2019.
//

#ifndef IRTitleBarProjectButtonArea_h
#define IRTitleBarProjectButtonArea_h

#include "JuceHeader.h"
#include "IRStrComponent.hpp"
#include "IRImageButton.hpp"

class IRTitleBarProjectButtonArea : public Component,
public IRStrComponent,
public ChangeBroadcaster
{
    
public:
    IRTitleBarProjectButtonArea(IRStr* str) : IRStrComponent(str)
    {
        std::cout << "IRTitleBarProjectButtonArea init\n";
        
        setOpaque(false);
        
        createButton(&this->closeButton, getStr()->ICONBANK->icon_close);
        this->closeButton.onClick = [this] { closeButtonAction(); };
        this->closeButton.setDrawCircle(false);
        this->closeButton.setDrawRoundedSquare(false);
        addAndMakeVisible(&this->closeButton);
        
        this->newProjectButton.reset ( new IRImageButton() );
        createButton(this->newProjectButton.get(), getStr()->ICONBANK->icon_newProject);
        this->newProjectButton->onClick = [this]{ newProjectButtonAction(); };
        this->newProjectButton->setDrawRoundedSquare(true);
        addAndMakeVisible(this->newProjectButton.get());
        this->newProjectButton->setDrawCircle(false);

        this->newProjectLabel.setText("New", dontSendNotification);
        addAndMakeVisible(&this->newProjectLabel);
        this->newProjectLabel.setJustificationType(Justification::centred);
        this->newProjectLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

        this->newSlideButton.reset(new IRImageButton("newSlide"));
        createButton(this->newSlideButton.get(), getStr()->ICONBANK->icon_newSlide);
        this->newSlideButton->onClick = [this]{ newSlideButtonAction(); };
        this->newSlideButton->setDrawRoundedSquare(true);
        addAndMakeVisible(this->newSlideButton.get());
        this->newSlideButton->setDrawCircle(false);

        this->newSlideLabel.setText("Add", dontSendNotification);
        addAndMakeVisible(&this->newSlideLabel);
        this->newSlideLabel.setJustificationType(Justification::centred);
        this->newSlideLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

        this->saveProjectButton.reset( new IRImageButton() );
        createButton(this->saveProjectButton.get(), getStr()->ICONBANK->icon_saveProject_arrow);
        this->saveProjectButton->onClick = [this]{ saveProjectButtonAction(); };
        this->saveProjectButton->setDrawRoundedSquare(true);
        addAndMakeVisible(this->saveProjectButton.get());
        this->saveProjectButton->setDrawCircle(false);

        this->saveProjectLabel.setText("Save", dontSendNotification);
        addAndMakeVisible(&this->saveProjectLabel);
        this->saveProjectLabel.setJustificationType(Justification::centred);
        this->saveProjectLabel.setFont(getStr()->SYSTEMCOLOUR.h5);
        
        this->exportButton.reset( new IRImageButton() );
        createButton(this->exportButton.get(), getStr()->ICONBANK->icon_export);
        this->exportButton->onClick = [this]{ exportButtonAction(); };
        this->exportButton->setDrawRoundedSquare(true);
        addAndMakeVisible(this->exportButton.get());
        this->exportButton->setDrawCircle(false);
        
        this->exportLabel.setText("Export", dontSendNotification);
        addAndMakeVisible(&this->exportLabel);
        this->exportLabel.setJustificationType(Justification::centred);
        this->exportLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

        this->saveasProjectButton.reset( new IRImageButton() );
        createButton(this->saveasProjectButton.get(), getStr()->ICONBANK->icon_saveasProject_arrow);
        this->saveasProjectButton->onClick = [this]{ saveasProjectButtonAction(); };
        addAndMakeVisible(this->saveasProjectButton.get());
        this->saveasProjectButton->setDrawCircle(false);
        this->saveasProjectButton->setDrawRoundedSquare(true);

        this->saveasProjectLabel.setText("Save As", dontSendNotification);
        addAndMakeVisible(&this->saveasProjectLabel);
        this->saveasProjectLabel.setJustificationType(Justification::centred);
        this->saveasProjectLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

        this->openProjectButton.reset( new IRImageButton() );
        createButton(this->openProjectButton.get(), getStr()->ICONBANK->icon_openProject_arrow);
        this->openProjectButton->onClick = [this]{ openProjectButtonAction(); };
        addAndMakeVisible(this->openProjectButton.get());
        this->openProjectButton->setDrawCircle(false);
        this->openProjectButton->setDrawRoundedSquare(true);

        this->openProjectLabel.setText("Open", dontSendNotification);
        addAndMakeVisible(&this->openProjectLabel);
        this->openProjectLabel.setJustificationType(Justification::centred);
        this->openProjectLabel.setFont(getStr()->SYSTEMCOLOUR.h5);

    }
    
    ~IRTitleBarProjectButtonArea()
    {
        
    }
    //==================================================
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::transparentBlack);
        g.setColour(getStr()->SYSTEMCOLOUR.contents);
        g.drawLine(0, getHeight() , getWidth(), getHeight(), 2);
        
        //TiAALS(g);
        
        g.setColour(getStr()->SYSTEMCOLOUR.contents);
        //g.drawLine(135, getHeight(), 135, 0, 2);
        
        g.drawLine(54, getHeight(), 54, 0, 2);
        //g.drawLine(304, getHeight(), 304, 0, 2);
        
        int ws = this->saveasProjectButton->getX() + this->saveasProjectButton->getWidth() + 10;
        g.drawLine(ws, getHeight(), ws, 0, 2);

    }
    
    void TiAALS(Graphics& g)
    {
        g.setColour(getStr()->SYSTEMCOLOUR.text);
        Font f("Avenir Next",34, Font::plain);
        g.setFont(f);
        g.drawText("TiAALS", 30, 10, 200, getHeight()*0.8, dontSendNotification);
    }
    
    void resized() override
    {
        int x = 60;
        int h = getHeight() * 0.41;
        
        this->closeButton.setBounds(5, 5, 20, 20);

        this->buttonSize = juce::Point<int> (((float)h / this->newSlideButton->getAspectRatio()) * 1.2, h);

        int marginY = (getHeight() - this->buttonSize.getY())/2;
        int labelY = getHeight() - marginY + 3;
        int labelHeight = marginY * 0.5;

        
        juce::Point<int> bs = juce::Point<int> ((float)h / this->newProjectButton->getAspectRatio(), h);
        
     
        this->newSlideButton->setBounds(x, marginY, bs.getX(), bs.getY());
        this->newSlideLabel.setBounds(x, labelY, bs.getX(), labelHeight);
        
        x += bs.getX() + 10;
        this->saveProjectButton->setBounds(x, marginY, bs.getX(), bs.getY());
        this->saveProjectLabel.setBounds(x, labelY, bs.getX(), labelHeight);

        x += bs.getX() + 10;
        this->saveasProjectButton->setBounds(x, marginY, bs.getX(), bs.getY());
        this->saveasProjectLabel.setBounds(x, labelY, bs.getX(), labelHeight);

        x += bs.getX() + 20;
        
        this->newProjectButton->setBounds(x, marginY, bs.getX(), bs.getY());
        this->newProjectLabel.setBounds(x, labelY, bs.getX(), labelHeight);

        x += bs.getX() + 10;
        this->openProjectButton->setBounds(x, marginY, bs.getX(), bs.getY());
        this->openProjectLabel.setBounds(x, labelY, bs.getX(), labelHeight);
        
        x += bs.getX() + 20;
        this->exportButton->setBounds(x, marginY, bs.getX(), bs.getY());
        this->exportLabel.setBounds(x, labelY, bs.getX(), labelHeight);
       
        std::cout << " ========== IRTitleBarProjectButtonArea resized\n";
    }
    
    //==================================================
    std::function<void()> newSlideButtonCallback;
    std::function<void()> newProjectButtonCallback;
    std::function<void()> saveButtonCallback;
    std::function<void()> saveasButtonCallback;
    std::function<void()> openButtonCallback;
    std::function<void()> closeButtonCallback;
    std::function<void()> exportButtonCallback;


    //==================================================
    std::function<void()> repaintedCallback;
    //==================================================
    //==================================================

    //==================================================
private:
    //==================================================
    
    void createButton(IRImageButton* button, IRIconBank::IRIconImage img)
    {
        if(getStr()->SYSTEMCOLOUR.isWhiteBased)
            button->setImage(img.black);
        else  button->setImage(img.white);
        addAndMakeVisible(button);
    }

    
    //==================================================
    String title;
    Label titleLabel;

    //==================================================
    // IRImageButton stuff...
    // IRImageButton
    // Label
    // pressedAction()
    
    IRImageButton closeButton;
    void closeButtonAction()
    {
        if(this->closeButtonCallback != nullptr)
            this->closeButtonCallback();
    }
    
    std::shared_ptr<IRImageButton> newProjectButton;
    Label newProjectLabel;
    void newProjectButtonAction()
    {
        if(this->newProjectButtonCallback != nullptr)
        this->newProjectButtonCallback();
    }
    
    std::shared_ptr<IRImageButton> saveProjectButton;
    Label saveProjectLabel;
    void saveProjectButtonAction()
    {
        if(this->saveButtonCallback != nullptr)
        this->saveButtonCallback();
    }
    
    std::shared_ptr<IRImageButton> exportButton;
    Label exportLabel;
    void exportButtonAction()
    {
        if(this->exportButtonCallback != nullptr)
        this->exportButtonCallback();
    }

    std::shared_ptr<IRImageButton> saveasProjectButton;
    Label saveasProjectLabel;
    void saveasProjectButtonAction()
    {
        if(this->saveasButtonCallback != nullptr)
        this->saveasButtonCallback();
    }

    std::shared_ptr<IRImageButton> openProjectButton;
    Label openProjectLabel;
    void openProjectButtonAction()
    {
        if(this->openButtonCallback != nullptr)
        this->openButtonCallback();
    }

    
    std::shared_ptr<IRImageButton> newSlideButton;
    Label newSlideLabel;
    void newSlideButtonAction()
    {
        if(this->newSlideButtonCallback != nullptr)
        this->newSlideButtonCallback();
    }
    //==================================================
    juce::Point<int> buttonSize;
    //==================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRTitleBarProjectButtonArea)

};

#endif /* IRTitleBarProjectButtonArea_h */
