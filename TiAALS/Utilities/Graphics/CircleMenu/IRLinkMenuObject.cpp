//
//  IRLinkMenuObject.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 23/04/2019.
//

#include "IRLinkMenuObject.hpp"

// ==================================================

void SquareButton::paint(Graphics& g)
{
    this->rect = Rectangle<float>(this->margin.getX(),
                                  this->margin.getY(),
                                  getWidth() - this->margin.getX(),
                                  getHeight() - this->margin.getY());
  
    if(this->isMouseEnter || this->isSelected)
        g.setColour(SYSTEMCOLOUR.contents);
    else
        g.setColour(SYSTEMCOLOUR.contents.brighter());

    g.fillEllipse(this->rect);
    
    if(this->isSelected)
        g.drawImage(this->selectedImg, this->rect);
    else
        g.drawImage(this->img, this->rect);
}

void SquareButton::mouseDown(const MouseEvent& e)
{
    this->isSelected = true;
    std::cout << "SquareButton mouse Down\n";
    if(onClick != nullptr) onClick(this->flag);
    
    repaint();
}

void SquareButton::mouseEnter(const MouseEvent& e)
{
    std::cout << "SquareButton mouse enter\n";
    this->isMouseEnter = true;
    repaint();
}

void SquareButton::mouseExit(const MouseEvent& e)
{
    std::cout << "SquareButton mouse exit\n";
    this->isMouseEnter = false;
    repaint();
}
void SquareButton::setPaintBounds(float x, float y, float w, float h)
{
   this->rect = Rectangle<float>(x + this->margin.getX(),
                                  y + this->margin.getY(),
                                  w - this->margin.getX(),
                                  h - this->margin.getY());
}

// ==================================================

IRLinkMenuObject::IRLinkMenuObject(Component* parent, std::vector<IRLinkSystemFlag> flags)
{
    this->parent = parent;
    std::cout << "IRLinkMenuObject\n";
    this->flags = flags;
    this->num = (int)this->flags.size();
    
    loadAllImages();
    
}
// --------------------------------------------------

IRLinkMenuObject::~IRLinkMenuObject()
{
    
}
// --------------------------------------------------

void IRLinkMenuObject::paint(Graphics& g)
{
    calcPositionOfButtons();
}

void IRLinkMenuObject::paintLinkMenuSwitch(Graphics& g, IRLinkSystemFlag flag)
{
    /*
    switch(flag)
    {
        case AudioLinkFlag:
            this->button_wav.get()->paintContents(g);
            break;
        case ImageLinkFlag:
            this->button_img.get()->paintContents(g);
            break;
        case DataLinkFlag:
            this->button_data.get()->paintContents(g);
            break;
        case ConsoleLinkFlag:
            this->button_play.get()->paintContents(g);
            break;
        case TextLinkFlag:
            this->button_text.get()->paintContents(g);
            break;
        case TimeLinkFlag:
            break;
        default:
            break;
    }*/
}
// --------------------------------------------------

void IRLinkMenuObject::resized()
{
    this->rect = Rectangle<float>(getBounds().toFloat());
    
    calcPositionOfButtons();
    
   
}
// --------------------------------------------------

void IRLinkMenuObject::calcPositionOfButtons()
{
    float w = this->rect.getWidth();
    float h = this->rect.getHeight();
    float div_w = w / this->num;
    
    float x = 0;
    for (auto f : this->flags)
    {
        switch (f)
        {
            case AudioLinkFlag:
                this->button_wav.get()->setBounds(x, 0, div_w, h);
                x += div_w;
                break;
            case ImageLinkFlag:
                this->button_img.get()->setBounds(x, 0, div_w, h);

                x += div_w;
                break;
            case DataLinkFlag:
                this->button_data.get()->setBounds(x, 0, div_w, h);

                x += div_w;
                break;
            case ConsoleLinkFlag:
                this->button_play.get()->setBounds(x, 0, div_w, h);

                x += div_w;
                break;
            case TextLinkFlag:
                this->button_text.get()->setBounds(x, 0, div_w, h);

                x += div_w;
                break;
            case TimeLinkFlag:
                //no yet
                break;
            default:
                break;
        }
    }
 
}

void IRLinkMenuObject::loadAllImages()
{
    removeAllChildren();
    //String url = "/materials/Images/icon/menu/icon_data.png";
    String url;
    for(auto f : this->flags)
    {
        switch(f)
        {
            case AudioLinkFlag:
                url = "/materials/Images/icon/menu/icon_wav_white.png";
        #if JUCE_MAC
                this->icon_wav = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_wav = loadImage(url);
        #endif
                
                url = "/materials/Images/icon/menu/icon_wav.png";
        #if JUCE_MAC
                this->icon_wav2 = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_wav2 = loadImage(url);
        #endif
                
                this->button_wav = std::make_shared<SquareButton>(this->parent, AudioLinkFlag);
                this->button_wav.get()->setImage(this->icon_wav);
                this->button_wav.get()->setSelectedImage(this->icon_wav2);
                this->button_wav.get()->onClick = [this] (IRLinkSystemFlag flag){ mouseDownDetectedInSquareButton(flag);};
                addAndMakeVisible(this->button_wav.get());
                
                break;
                
                
                
            case ImageLinkFlag:
                url = "/materials/Images/icon/menu/icon_img_white.png";
        #if JUCE_MAC
                this->icon_img = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_img = loadImage(url);
        #endif
                
                url = "/materials/Images/icon/menu/icon_img.png";
        #if JUCE_MAC
                this->icon_img2 = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_img2 = loadImage(url);
        #endif
                this->button_img = std::make_shared<SquareButton>(this->parent, ImageLinkFlag);
                this->button_img.get()->setImage(this->icon_img);
                this->button_img.get()->setSelectedImage(this->icon_img2);
                this->button_img.get()->onClick = [this] (IRLinkSystemFlag flag){ mouseDownDetectedInSquareButton(flag);};

                addAndMakeVisible(this->button_img.get());

                break;
                
            case DataLinkFlag:
                url = "/materials/Images/icon/menu/icon_data_white.png";
        #if JUCE_MAC
                this->icon_data = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_data = loadImage(url);
        #endif
                url = "/materials/Images/icon/menu/icon_data.png";
        #if JUCE_MAC
                this->icon_data2 = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_data2 = loadImage(url);
        #endif
                this->button_data = std::make_shared<SquareButton>(this->parent, DataLinkFlag);
                this->button_data.get()->setImage(this->icon_data);
                this->button_data.get()->setSelectedImage(this->icon_data2);
                this->button_data.get()->onClick = [this] (IRLinkSystemFlag flag){ mouseDownDetectedInSquareButton(flag);};

                addAndMakeVisible(this->button_data.get());

                break;
                
            case ConsoleLinkFlag:
                url = "/materials/Images/icon/menu/icon_play_white.png";
        #if JUCE_MAC
                this->icon_play = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_play = loadImage(url);
        #endif
                url = "/materials/Images/icon/menu/icon_play.png";
        #if JUCE_MAC
                this->icon_play2 = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_play2 = loadImage(url);
        #endif
                this->button_play = std::make_shared<SquareButton>(this->parent, ConsoleLinkFlag);
                this->button_play.get()->setImage(this->icon_play);
                this->button_play.get()->setSelectedImage(this->icon_play2);
                this->button_play.get()->onClick = [this] (IRLinkSystemFlag flag){ mouseDownDetectedInSquareButton(flag);};

                addAndMakeVisible(this->button_play.get());

                break;
                
            case TextLinkFlag:
                url = "/materials/Images/icon/menu/icon_text_white.png";
        #if JUCE_MAC
                this->icon_text = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_text = loadImage(url);
        #endif
                url = "/materials/Images/icon/menu/icon_text.png";
        #if JUCE_MAC
                this->icon_text2 = loadImage("/Contents/Resources" + url);
        #elif JUCE_IOS
                this->icon_text2 = loadImage(url);
        #endif
                this->button_text = std::make_shared<SquareButton>(this->parent, TextLinkFlag);
                this->button_text.get()->setImage(this->icon_text);
                this->button_text.get()->setSelectedImage(this->icon_text2);
                this->button_text.get()->onClick = [this] (IRLinkSystemFlag flag){ mouseDownDetectedInSquareButton(flag);};

                addAndMakeVisible(this->button_text.get());

                break;
            case TimeLinkFlag:
                //no yet
                break;
            default:
                break;
        }
    }
}

// --------------------------------------------------

Image IRLinkMenuObject::loadImage(String url)
{
    File file = File(IRPath().getAppContentsDirectoryPath() + url);
    return ImageFileFormat::loadFrom(file);
}
// --------------------------------------------------

// Child Component Management
void IRLinkMenuObject::childComponentManager(Component* comp)
{
    comp->addMouseListener(this, true);
    //comp->setInterceptsMouseClicks(true, false);
}

// --------------------------------------------------
void IRLinkMenuObject::mouseDownDetectedInSquareButton(IRLinkSystemFlag flag)
{    
    deSelectAll();
    
    setSelectedItem(flag);
    
    if(this->notifySelectedItem != nullptr) this->notifySelectedItem(flag);
    else printf("null\n");
}
void IRLinkMenuObject::deSelectAll()
{
    // all reset
    if(this->button_data)
        this->button_data.get()->isSelected = false;
    if(this->button_img)
        this->button_img.get()->isSelected = false;
    if(this->button_wav)
        this->button_wav.get()->isSelected = false;
    if(this->button_play)
        this->button_play.get()->isSelected = false;
    if(this->button_text)
        this->button_text.get()->isSelected = false;
}

void IRLinkMenuObject::setSelectedItem(IRLinkSystemFlag flag)
{
    switch(flag)
    {
        case AudioLinkFlag:
            this->button_wav.get()->isSelected = true;
            break;
        case ImageLinkFlag:
            this->button_img.get()->isSelected = true;
            break;
        case DataLinkFlag:
            this->button_data.get()->isSelected = true;
            break;
        case ConsoleLinkFlag:
            this->button_play.get()->isSelected = true;
            break;
        case TextLinkFlag:
            this->button_text.get()->isSelected = true;
            break;
        case TimeLinkFlag:
            break;
        default:
            break;
    }
}
