//
//  IRWaveformController2.cpp
//  IRiMaS
//
//  Created by Keitaro on 10/10/2019.
//

#include "IRWaveformController2.hpp"


IRWaveformController2::IRWaveformController2(IRStr* str) :
IRObjectController("Waveform", str),
waveformCtl(str)
{
    
    createAndAddArrangeController();
    
    setWaveformControllerVisible(true);
    addAndMakeVisible(&this->waveformCtl);

}

IRWaveformController2::~IRWaveformController2()
{
    
}


void IRWaveformController2::ControllerResized()
{
    int y = 10;
    int yIncrement = 30;
    int yBigIncrement = 40;
    y += yBigIncrement;
    y += yIncrement;
    
    
    this->waveformCtl.setBounds (0, y, getWidth(), 300);
    
    
}

void IRWaveformController2::paint(Graphics& g)
{
    /*
    g.fillAll(getStr()->SYSTEMCOLOUR.contents);
    g.setColour(getStr()->SYSTEMCOLOUR.fundamental);
    g.drawLine(0,42.5,getWidth(),42.5, 2);
     */
    
}


void IRWaveformController2::mainControllerSelected()
{
    setWaveformControllerVisible(true);
    setArrangeControllerVisible(false);
    
}

void IRWaveformController2::arrangeControllerSelected()
{
    setWaveformControllerVisible(false);
    setArrangeControllerVisible(true);
}


void IRWaveformController2::addChangeListenerToAudioController(ChangeListener* listener)
{
    this->waveformCtl.addChangeListenerToAudioController(listener);
}

void IRWaveformController2::setWaveformControllerVisible(bool flag)
{
    this->waveformCtl.setVisible(flag);

}
