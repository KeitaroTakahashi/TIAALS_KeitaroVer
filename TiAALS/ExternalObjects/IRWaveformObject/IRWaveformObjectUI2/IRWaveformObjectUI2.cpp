//
//  IRWaveformObjectUI2.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 02/06/2019.
//

#include "IRWaveformObjectUI2.hpp"

IRWaveformObjectUI2::IRWaveformObjectUI2(IRNodeObject* parent, IRStr* str) :
IRUIFoundation(parent, str)
{
    this->waveform = std::make_shared<IRWaveformObjectUI>(parent, str);
    this->waveformView = std::make_shared<IRViewUI>(str,
                                                    this->waveform.get(),
                                                    0, 40,
                                                    0, 40);
    this->waveform->addChangeListener(this);
    addAndMakeVisible(this->waveformView.get());
    this->waveformView->visibleAreaChangedCallback = [this](Rectangle<int> area){ visibleAreaChanged(area); };
    this->waveform->zoomInClickedCallback = [this]{ zoomInClicked(); };
    this->waveform->zoomOutClickedCallback = [this]{ zoomOutClicked(); };
}

IRWaveformObjectUI2::~IRWaveformObjectUI2()
{
    this->waveform.reset();
    this->waveformView.reset();
}

// ==================================================
void IRWaveformObjectUI2::resized()
{
    int x = this->xMargin;
    int y = this->yMargin;
    int w = getWidth() - this->xMargin*2;
    int h = getHeight() - this->yMargin*2;
    
    this->waveformView->setBounds(x, y, w, h);
    this->waveformView->setViewPosition(this->previousOffsetX, 0);
    this->waveformView->setComponentBounds(0,
                                           0,
                                           w * this->automation_width_ratio,
                                           h - this->scrollSpace);
    
    this->waveform->setZoomInfo(this->automation_width_ratio, 1.0);
    this->waveform->linkZoomInfo(nodeObject);
}
void IRWaveformObjectUI2::paint(Graphics& g)
{
    g.fillAll(getStr()->SYSTEMCOLOUR.background);
    
    g.setColour (getStr()->SYSTEMCOLOUR.contents);
    //g.drawRoundedRectangle (area.toFloat(), 5.0f, 4.0f);
    g.drawRect(getLocalBounds().toFloat(), 1.0);
}

// ==================================================

void IRWaveformObjectUI2::zoomResize()
{
    int w = getWidth() - this->xMargin*2;
    int h = getHeight() - this->yMargin*2;
    this->waveformView->setComponentBounds(0,
                                           0,
                                           w * this->automation_width_ratio,
                                           h - this->scrollSpace);
    
    this->waveform->setZoomInfo(this->automation_width_ratio, 1.0);
}
// ==================================================

void IRWaveformObjectUI2::visibleAreaChanged(Rectangle<int> area)
{
    this->waveform->setVisibleArea(area);
    this->waveformView->setVisibleArea(area);
    this->previousOffsetX = area.getX();
}

// ==================================================

void IRWaveformObjectUI2::zoomInClicked()
{
    this->automation_width_ratio *= 2;
    resized();
    //this->waveform->reCalcPos();
}

void IRWaveformObjectUI2::zoomOutClicked()
{
    this->automation_width_ratio /= 2;
    resized();
    //this->automation->reCalcPos();
    
}

void IRWaveformObjectUI2::setEditMode(bool newEditMode)
{
    this->waveform->setEditMode(newEditMode);
}

void IRWaveformObjectUI2::changeListenerCallback (ChangeBroadcaster* source)
{
    if(source == this->waveform.get())
    {
        
        auto s = this->waveform->getStatus();
        if(s == IRWaveform::IRWaveformStatus::zoomInfoShared)
        {
            this->automation_width_ratio = this->waveform->getZoomInfo().getX();
            zoomResize();
        }else if(s == IRWaveform::IRWaveformStatus::currentPlayedFrameShared)
        {
            
        }else if(s == IRWaveform::IRWaveformStatus::viewPosShared)
        {
            auto pos = this->waveform->getVisiblePos();
            this->waveformView->setViewPosition(pos.getX(), pos.getY());
        }
    }
}

void IRWaveformObjectUI2::setAutomationWidthRatio(float ratio)
{
    this->automation_width_ratio = ratio;
    resized();
}
