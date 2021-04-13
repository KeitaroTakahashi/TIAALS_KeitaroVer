//
//  IRSwitchButton.h
//  IRiMaS
//
//  Created by Keitaro on 04/02/2020.
//

#ifndef IRSwitchButton_h
#define IRSwitchButton_h
#include <map>
#include "JuceHeader.h"

class IRSquareButton : public Component,
public IRStrComponent
{
public:
    IRSquareButton(String text, IRStr* str) :
    IRStrComponent(str),
    text(text)
    {
        
    }
    
    ~IRSquareButton()
    {
        
    }
    
    void resized() override
    {
        
    }
    
    void paint(Graphics& g) override
    {
        if(isSelected())
            g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
        else
            g.fillAll(getStr()->SYSTEMCOLOUR.contents);
        g.setColour(getStr()->SYSTEMCOLOUR.fundamental);
        g.drawRect(getLocalBounds(), 2);
        
        g.setColour(getStr()->SYSTEMCOLOUR.text);
        g.drawText(this->text, getLocalBounds(), Justification::centred);
        
    }
    
    void mouseDown(const MouseEvent& e) override
    {
        callButtonClicked();
    }
  
    // ==================================================
    String getText() const { return this->text; }
    void setSelected(bool flag) { this->isSelectedFlag = flag; repaint(); }
    bool isSelected() const { return this->isSelectedFlag; }
    
    // ==================================================

    class Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void buttonClicked(IRSquareButton* clickedButton) {};
    };
    
    ListenerList<Listener> listeners;
    
    void addListener(Listener* newListener) { this->listeners.add(newListener); }
    void removeListener(Listener* listener) { this->listeners.remove(listener); }
    

    void callButtonClicked()
    {
        Component::BailOutChecker checker(this);
        // check if the objects are not deleted, if deleted, return
        if(checker.shouldBailOut()) return;
        this->listeners.callChecked(checker, [this](Listener& l){ l.buttonClicked(this); });
        //check again
        if(checker.shouldBailOut()) return;
    }
    
private:
    
    String text;
    bool isSelectedFlag = false;
    
};

class IRSwitchButton : public Component,
public IRStrComponent
{
public:
    IRSwitchButton(IRStr* str) : IRStrComponent(str)
    {
        
    }
    
    ~IRSwitchButton()
    {
        clearButtons();
    }
    
    
    void resized() override
    {
        int num = (int)this->buttons.size();
        int w = getWidth() / num;
        int h = getHeight();
        int index = 0;
        for(auto b : this->buttons)
        {
            b.second->setBounds(w * index, 0, w, h);
            index ++;
        }
    }
    
    void selectAButton(IRSquareButton* button)
    {
        for(auto b : this->buttons)
        {
            b.second->setSelected(false);
        }
        
        button->setSelected(true);
    }
    
    void createButton(std::string text, IRSquareButton::Listener* listener)
    {
        IRSquareButton* button = new IRSquareButton(text, getStr());
        addAndMakeVisible(button);
        button->addListener(listener);
        this->buttons[text] = button;
    }
    
    IRSquareButton* getSquareButtonAt(std::string text)
    {
        return this->buttons[text];
    }

    
private:
    
    std::map<std::string, IRSquareButton*> buttons;
    
    void clearButtons()
    {
        for(auto b : this->buttons)
        {
            delete b.second;
        }
        this->buttons.clear();
    }
    
    
};

#endif /* IRSwitchButton_h */
