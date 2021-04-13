//
//  IRLinkMenuObject.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 23/04/2019.
//

#ifndef IRLinkMenuObject_hpp
#define IRLinkMenuObject_hpp

#include "JuceHeader.h"
#include "ColourLib.h"
#include "KLib.h"


enum IRLinkSystemFlag
{
    AudioLinkFlag,
    ImageLinkFlag,
    DataLinkFlag,
    ConsoleLinkFlag,
    TextLinkFlag,
    TimeLinkFlag
    
};
// ==================================================

class SquareButton : public Component
{
public:
    SquareButton(Component* parent, IRLinkSystemFlag flag, Image img = Image()) :
    margin(5,5)
    {
        this->img = img;
        this->parent = parent;
        this->flag = flag;
        addMouseListener(this->parent, false);
    }
    
    ~SquareButton() {}
    
    void paint(Graphics& g) override;
    void setPaintBounds(float x, float y, float w, float h);
    
    void setImage(Image img) { this->img = img; }
    void setSelectedImage(Image img) { this->selectedImg = img; }
    
    
    IRLinkSystemFlag getFlag() const { return this->flag; }
    
    std::function<void(IRLinkSystemFlag)> onClick;
    
    bool isSelected = false;

private:
    void mouseDown(const MouseEvent& e) override;
    void mouseEnter(const MouseEvent& e) override;
    void mouseExit(const MouseEvent& e) override;
    

    bool isMouseEnter = false;
    Image img;
    Image selectedImg;
    juce::Point<float> margin;
    
    Rectangle<float> rect;
    
    //workspace
    Component* parent = nullptr;
    
    IRLinkSystemFlag flag;
    
    
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

};



// ==================================================

class IRLinkMenuObject : public Component
{
public:
    IRLinkMenuObject(Component* parent, std::vector<IRLinkSystemFlag> flags);
    ~IRLinkMenuObject();
    
    //void paintLinkMenu(Graphics& g);
    void paintLinkMenuSwitch(Graphics& g, IRLinkSystemFlag flag);
    void paint(Graphics& g) override;
    void resized() override;
    
    void calcPositionOfButtons();
    
    void childComponentManager(Component* comp);
    
    void mouseDown(const MouseEvent& e) override
    {
    }
    
    void deSelectAll();
    void setSelectedItem(IRLinkSystemFlag flag);
    
    std::function<void(IRLinkSystemFlag)> notifySelectedItem;


private:
    void mouseDownDetectedInSquareButton(IRLinkSystemFlag flag);

    void loadAllImages();
    
    Image loadImage(String url);
    
    Rectangle<float> rect;
    
    Image icon_data;
    Image icon_data2;
    std::shared_ptr<SquareButton> button_data;
    
    Image icon_img;
    Image icon_img2;
    std::shared_ptr<SquareButton> button_img;

    Image icon_play;
    Image icon_play2;
    std::shared_ptr<SquareButton> button_play;

    Image icon_text;
    Image icon_text2;
    std::shared_ptr<SquareButton> button_text;

    Image icon_wav;
    Image icon_wav2;
    std::shared_ptr<SquareButton> button_wav;
    
    float num = 0;
    
    std::vector<IRLinkSystemFlag> flags;
    
    std::shared_ptr<SquareButton> test;

    // workspace
    Component* parent = nullptr;
};

#endif /* IRLinkMenuObject_hpp */
