//
//  IRWorkspaceSlide.cpp
//  IRiMaS
//
//  Created by Keitaro on 17/09/2019.
//

#include "IRWorkspaceSlide.hpp"

IRWorkspaceSlide::IRWorkspaceSlide(IRStr* str, int index, IRWorkspace* space) :
IRStrComponent(str),
space(space),
index(index)
{
    //updateThumbnail();
}

IRWorkspaceSlide::~IRWorkspaceSlide()
{
    
}

void IRWorkspaceSlide::paint(Graphics& g)
{
    if(isSelected())
    {
        g.fillAll(getStr()->SYSTEMCOLOUR.fundamental);
        
        //std::cout << "getStr()->SYSTEMCOLOUR.contents colour = " << getStr()->SYSTEMCOLOUR.colourName << std::endl;
    }else{
        g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    }
    
    /*
    if(this->thumbnail.getWidth() > 0 && this->thumbnail.getHeight() > 0)
        g.drawImage(this->thumbnail, getLocalBounds().toFloat());
    else{
        std::cout << "Error : IRWorkspaceSlide : Wrong thumbnail image size : " << getThumbnailURL() << std::endl;
    }*/
    
    
    Image txt = drawTextIntoImage();
    DropShadow shadow(Colours::darkgrey, 5, Point<int>(0,0));
    shadow.drawForImage(g, txt);
    g.setFont(getStr()->SYSTEMCOLOUR.h3);
    g.setColour(getStr()->SYSTEMCOLOUR.text);
    g.drawText(String(this->index), 0, 0, getWidth(), getHeight(), Justification::centred);
}

Image IRWorkspaceSlide::drawTextIntoImage()
{
    
    Image textImage(Image::ARGB, getWidth(), getHeight(),true);
    Graphics g(textImage);
    g.setColour(getStr()->SYSTEMCOLOUR.text);
    g.setFont(getStr()->SYSTEMCOLOUR.h1);
    g.drawText(String(this->index), 0, 0, getWidth(), getHeight(), Justification::centred);
    
    return textImage;
       
}

// ==================================================

void IRWorkspaceSlide::mouseDown(const MouseEvent& e)
{
   if(!isSelected())
   {
       if(this->onClick != nullptr) this->onClick(this);
   }
    
    toFront(true);
    std::cout <<"IRWorkspaceSlide : mouseDown\n";
    
}

void IRWorkspaceSlide::mouseUp(const MouseEvent& e)
{
    if(this->slideSwitchedCallback != nullptr)
        this->slideSwitchedCallback(this);
       // This is important, otherwise an object on the selected workspace will have front focus and gets keyboard Focus.
       // to get focus of keyboard on this object, then we need to call toFront method
       toFront(true);
}


// ==================================================

void IRWorkspaceSlide::deleteThisWorkspace()
{
    
}
// ==================================================

void IRWorkspaceSlide::setIndex(int newIndex)
{
    this->index = newIndex;
    getWorkspace()->setIndex(newIndex);
    repaint();
}

// ==================================================

bool IRWorkspaceSlide::updateThumbnail()
{
    this->thumbnail = loadImage();
    repaint();
    
    if(this->thumbnail.getWidth() == 0 || this->thumbnail.getHeight() == 0)
        return false;
    else{
        repaint();
        return true;
    }
}
