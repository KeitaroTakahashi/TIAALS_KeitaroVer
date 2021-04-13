//
//  IRAutomationUIWithPreference.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 28/05/2019.
//

#include "IRAutomationUIWithPreference.hpp"

IRAutomationUIWithPreference::IRAutomationUIWithPreference(IRNodeObject* nodeObject, IRStr* str) :
IRAutomationUI(nodeObject, str)
{
    this->preference = std::make_shared<IRAutomationObjectPreference>("Automation Preference", Rectangle<int>(400,720), str);
    this->preference->getUI()->getOpenAudioUI()->setOpenAudioButtonCallback([this]{openAudioFileAction();});
    this->preference->getUI()->getOpenAudioUI()->addChangeListener(this);

    setFps(33);
    std::cout << "IRAutomationUIWithPreference init\n";
    
}

IRAutomationUIWithPreference::~IRAutomationUIWithPreference()
{
    
}

void IRAutomationUIWithPreference::openAudioFileAction()
{
    startAnimation();
    openFile();
    
   
}

void IRAutomationUIWithPreference::updateAudioPreferenceUI()
{
    this->preference->getUI()->getOpenAudioUI()->setAudioFileURL(getFilePath());
    
    //get audio data
    auto data = getAudioData()->getData();
    // get a list of descriptor name
    auto list = data->getDescriptorNameList();
    // add each descriptor name to the menu
    this->preference->getUI()->getOpenAudioUI()->clearDescriptorMenu();

    for(auto l : list)
    {
        this->preference->getUI()->getOpenAudioUI()->addDescriptorMenu(l);
        
        std::cout << " desctiptor = " << l << std::endl;
    }
    
    this->isFileImportCompletedFlag = false;
    stopAnimation();
    
    // initially set Magnitude
    // check if magnitude is already exctracted from the audio data
    if(!data->isCalculated(FFTDescriptor::FFT_MAGNITUDE))
    {
        data->operateAnalysis(FFTDescriptor::FFT_MAGNITUDE, 2048, 1024);
    }
    
    setDescriptor(data->getDescriptor(FFTDescriptor::FFT_MAGNITUDE, 2048));
    
    this->preference->getUI()->getOpenAudioUI()->setSelectedDescriptorItem(0);
}

void IRAutomationUIWithPreference::fileImportCompletedAction()
{
    this->isFileImportCompletedFlag = true;
}


void IRAutomationUIWithPreference::updateAnimationFrame()
{
    if(this->isFileImportCompletedFlag)
    {
        updateAudioPreferenceUI();
    }
    
    std::cout << "isFileImportCompletedFlag\n";
}

void IRAutomationUIWithPreference::hasDescriptorSelectedAction(FFTDescriptor descriptor)
{
    
    std::cout << "hasDescriptorSelectedAction : FFTDescriptor " << descriptor << std::endl;
    auto data = getAudioData()->getData();
    
    if(!data->isCalculated(descriptor))
        data->operateAnalysis(descriptor, this->fftsize, this->hopsize);
    
    auto d = data->getDescriptor(descriptor, this->fftsize);
    if(d != nullptr) setDescriptor(d);
    std::cout << "(FFTDescriptor descriptor) = " << descriptor << std::endl;
   
}

void IRAutomationUIWithPreference::changeListenerCallback(ChangeBroadcaster* source)
{
    
    // OpenAudioUI
    if(source == this->preference->getUI()->getOpenAudioUI())
    {
        auto status = this->preference->getUI()->getOpenAudioUI()->getStatus();
        
        if(status == AutomationPreferenceOpenAudioUI::AutomationpreferenceOpenAudioUIStatus::DescriptorMenuChanged)
        {
            hasDescriptorSelectedAction(this->preference->getUI()->getOpenAudioUI()->getSelectedDescriptor());
        }
    }
}


