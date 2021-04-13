//
//  SlideMenu.cpp
//  IRiMaS
//
//  Created by Keitaro on 17/09/2019.
//

#include "SlideMenu.hpp"

SlideMenu::SlideMenu(IRStr* str) :
IRStrComponent(str)
{
    
}

SlideMenu::~SlideMenu()
{
    for(auto item : this->slides)
    {
        delete item;
    }
}
// ==================================================

void SlideMenu::resized()
{
    int x = this->xMargin;
    int y = this->yMargin;
    for(auto item : this->slides)
    {
        item->setBounds(x, y + this->yMargin, getWidth() - x, this->itemHeight);
        y += this->itemHeight + this->yMargin;
        
        //std::cout << "slide resizing... " << item->getIndex() << " : " << item->getWorkspace()->getIndex() << std::endl;
    }
}

void SlideMenu::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    
}
// ==================================================

void SlideMenu::addSlide(IRWorkspace* space)
{
    int i = (int)this->slides.size() + 1;
    int index = space->getIndex();
    std::cout << "addSlide index = " << index << std::endl;
    this->slides.push_back(new IRWorkspaceSlide(getStr(), index, space));
    addAndMakeVisible(this->slides[i-1]);
    this->slides[i-1]->onClick = [this](IRWorkspaceSlide* slide){ slideSelectedAction(slide); };
    this->slides[i-1]->slideSwitchedCallback = [this](IRWorkspaceSlide* slide){ slideSwitchedAction(slide); };

    this->slides[i-1]->addMouseListener(this, true);
    slideSelectedAction(this->slides[i-1]);
    
    sortByIndex();
    
    resized();

}
// ==================================================

void SlideMenu::slideSelectedAction(IRWorkspaceSlide* slide)
{
    
    std::cout << "SlideMenu::slideSelectedAction : " << slide << std::endl;
    for(auto item : this->slides)
    {
        item->setSelectedFlag(false);
    }
    
    slide->setSelectedFlag(true);
    this->selectedSlide = slide;

}

void SlideMenu::slideSwitchedAction(IRWorkspaceSlide* slide)
{
    if(this->slideHasSelected != nullptr)
        this->slideHasSelected(slide);
    
    toFront(true);
}
// ==================================================

void SlideMenu::moveToLowerSlide()
{
    if(this->selectedSlide == nullptr) return;
    int currentIndex = this->selectedSlide->getIndex();
    
    std::cout << "moveToLowerSlide : " << currentIndex<< std::endl;
    
    if(currentIndex <= 1) return;
    
    slideSelectedAction(this->slides[currentIndex-2]);
    slideSwitchedAction(this->slides[currentIndex-2]);

}

void SlideMenu::moveToHigherSlide()
{
    if(this->selectedSlide == nullptr) return;
    int currentIndex = this->selectedSlide->getIndex();
    std::cout << "moveToHigherSlide : " << currentIndex<< std::endl;

    if(currentIndex >= this->slides.size()) return;
    
    slideSelectedAction(this->slides[currentIndex]);
    slideSwitchedAction(this->slides[currentIndex]);

}

// ==================================================

void SlideMenu::addNewWorkspaceSlide(IRWorkspace* space)
{
    std::cout << "SlideMenu::addNewWorkspaceSlide : " << space << std::endl;
    addSlide(space);
    updateSpace();
}

// ==================================================

void SlideMenu::updateSpace()
{
    int index = 1;
    for(auto s : this->slides)
    {
        s->setIndex(index);
        index ++;
    }
    int v_space = this->yMargin + (this->itemHeight * ((int)this->slides.size() + 1));
    setSize(getWidth(), v_space);
    if(this->slideMenuUpdated != nullptr)
        this->slideMenuUpdated();
}


void SlideMenu::sortByIndex()
{
    std::sort(this->slides.begin(), this->slides.end(), IRWorkspaceSlide::compBy);
    
    //sorted.
    std::cout << "sorting\n";
    for(auto s : this->slides)
    {
        std::cout<< "slide index = " << s->getIndex() << " of ws index = " << s->getWorkspace()->getIndex() << std::endl;
        // update
        //s->getWorkspace()->setIndex(s->getIndex());
    }
}

// ==================================================

IRWorkspace* SlideMenu::deleteSelectedWorkspaceSlide()
{
    
    IRWorkspace* ws = this->selectedSlide->getWorkspace();
    if(this->selectedSlide != nullptr)
    {
        int deleteItemIndex = 0;
        auto it = std::find(this->slides.begin(), this->slides.end(), this->selectedSlide);
        if(it != this->slides.end())
        {
            deleteItemIndex = (int)std::distance(this->slides.begin(), it);
            this->slides.erase(it);
        }
        
        delete this->selectedSlide;
        
        if(this->slides.size() == 0)
        {
            
        } else if(this->slides.size() > deleteItemIndex)
        {
            slideSelectedAction(this->slides[deleteItemIndex]);
            slideSwitchedAction(this->slides[deleteItemIndex]);
        }else{
            slideSelectedAction(this->slides[deleteItemIndex - 1]);
            slideSwitchedAction(this->slides[deleteItemIndex - 1]);
        }
            
        toFront(true);
        updateSpace();
    }
    
    return ws;
}

// ==================================================

IRWorkspaceSlide* SlideMenu::getSelectedSlide()
{
    return this->selectedSlide;
}

// ==================================================

void SlideMenu::mouseDown(const MouseEvent& e)
{
    this->mouseDownPos = e.getEventRelativeTo(this).getPosition();
    this->previousMousePos = this->mouseDownPos;
    
    if(getSelectedSlide() != nullptr)
    {
        this->mouseDownWithinTarget = e.getEventRelativeTo(getSelectedSlide()).getMouseDownPosition();
    }


}
void SlideMenu::mouseDrag(const MouseEvent& e)
{
    auto pos = e.getEventRelativeTo(this).getPosition();
    
    moveSelectedSlide(e);
}
void SlideMenu::mouseUp(const MouseEvent& e)
{
    resized();
}
// ==================================================
void SlideMenu::moveSelectedSlide(const MouseEvent& e)
{
    auto slide = getSelectedSlide();
    
    if(slide != nullptr)
    {
        juce::Point<int> delta = e.getEventRelativeTo(slide).getPosition() - this->mouseDownWithinTarget;

        Rectangle<int> bounds = slide->getBounds();
        bounds.setY(bounds.getY() + delta.getY());
        slide->setBounds(bounds);
        
        isSlideMovedToItsNeighbor(slide);
    }
    
}

// ==================================================

bool SlideMenu::isSlideMovedToItsNeighbor(IRWorkspaceSlide* slide)
{
    int slideIndex = slide->getIndex();
    
    for(auto s : this->slides)
    {
        if(s != slide)
        {
            auto pos = slide->getPosition();
            
            switch(yHittest(slide->getBounds(), s->getBounds()))
            {
                case previous:
                    
                    if(s->getIndex() > slide->getIndex())
                    {
                        slide->setIndex(slide->getIndex() + 1);
                        s->setIndex(s->getIndex() - 1);
                        
                        sortByIndex();
                        resized();
                    }
                    
                    break;
                case next:

                     if(s->getIndex() < slide->getIndex())
                     {
                         slide->setIndex(slide->getIndex() - 1);
                         s->setIndex(s->getIndex() + 1);
                         
                         sortByIndex();
                         resized();
                     }
                    
                    break;
                default:
                    break;
                
                
            }
               
        }
    }
    
    return true;
}


SlideMenu::slideSwitchStatus SlideMenu::yHittest(Rectangle<int>a, Rectangle<int> b)
{
    float ha = a.getHeight() / 2;
    float hb = b.getHeight() / 2;
    float CentreA = (float)a.getY() - ha;
    float CentreB = (float)b.getY() - hb;
    
    float distance = CentreA - CentreB;

    if(distance > 0 && distance < (ha + hb)) return previous;
    else if(distance < 0 && abs(distance) < (ha + hb)) return next;
    else return none;
}
// ==================================================


bool SlideMenu::reloadThumbnails()
{
    for(auto s : this->slides)
    {
        //if(!s->updateThumbnail()) return false;
    }
    return true;
}
