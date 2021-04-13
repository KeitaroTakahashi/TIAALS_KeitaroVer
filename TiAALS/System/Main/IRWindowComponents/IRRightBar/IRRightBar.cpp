//
//  IRRightBar.cpp
//  IRiMaS
//
//  Created by Keitaro on 09/08/2019.
//

#include "IRRightBar.hpp"

IRRightBar::IRRightBar(IRStr* str) : IRStrComponent(str)
{
    setFps(60);
    
    this->space = getStr()->ControlBarWidth;
    
    // add keyListener of IRWindowComponent
    addKeyListener(str->key);
}

IRRightBar::~IRRightBar()
{

}

//==================================================

void IRRightBar::resized()
{
    if(this->comp != nullptr)
    {
        if(this->comp->isVisible())
            this->comp->setBounds(getLocalBounds());
    }
    
    if(this->nothingSelectedUI.get() != nullptr)
    {
        this->nothingSelectedUI->setBounds(getLocalBounds());
    }
}

void IRRightBar::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
}
//==================================================

void IRRightBar::openSpaceAction(bool flag)
{
    if(flag) this->openSpace = true;
    else this->openSpace = false;
 
    startAnimation();
    
}

void IRRightBar::updateAnimationFrame()
{
    if(this->openSpace)
    {
        
        setBounds(this->initialPos.getX() - this->space,
                  this->initialPos.getY(),
                  this->space, getHeight());
        this->isOpened = true;
        stopAnimation();
    }else
    {
      
        setBounds(this->initialPos.getX(),
                  this->initialPos.getY(),
                  0, getHeight());
        this->isOpened = false;
        stopAnimation();
    }
    
}

//==================================================
void IRRightBar::addComponentAndMakeVisible(Component& comp)
{
    // give mouse Listener
    //comp.addMouseListener(getStr()->mouse, false);
    addAndMakeVisible(comp);
    resized();
}

//==================================================

void IRRightBar::changeListenerCallback (ChangeBroadcaster* source)
{
    
}

void IRRightBar::nodeObjectSelectionChange(IRNodeObject* obj)
{

}

void IRRightBar::nodeObjectGetFocused(IRNodeObject* obj)
{
    std::cout << " IRRightBar::nodeObjectGetFocused\n";
    removeComponents();
    
    if(obj != nullptr)
    {
        this->comp = obj->getObjController();
        if(this->comp != nullptr)
            addComponentAndMakeVisible(*this->comp);
    }
}

void IRRightBar::removeComponents()
{
    if(this->comp != nullptr)
    {
        removeChildComponent(this->comp);
        this->comp = nullptr;
    }
    
    if(this->nothingSelectedUI.get() != nullptr)
    {
        removeChildComponent(this->nothingSelectedUI.get());
        this->nothingSelectedUI.reset();
    }
}

//==================================================
void IRRightBar::showNothingSelectedUI()
{
    
    removeComponents();
    
    //this->nothingSelectedUI.reset(new NothingSelectedUI(getStr()));
    //addComponentAndMakeVisible(*this->nothingSelectedUI.get());
    
    
}

void IRRightBar::showWorkspaceController(Component* comp)
{
    removeComponents();
    
    this->comp = comp;
    addComponentAndMakeVisible(*comp);
}
