//
//  IRAudioDescriptor.cpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 28/04/2019.
//

#include "IRAudioDescriptor.hpp"

IRFFTDescriptor::IRFFTDescriptor(int fftsize, int hopsize, IRWindow::TYPE windowType):
IRFFTSequence(fftsize,hopsize,windowType)
{
    this->descriptorList.clear();
}

IRFFTDescriptor::~IRFFTDescriptor()
{
    this->descriptorList.clear();
}

void IRFFTDescriptor::setDescriptor(int arg_num, ...)
{
    this->descriptorList.clear();
    this->descriptorNameList.clear();
    
    va_list args;
    int count;
    if (arg_num < 1) return;

    va_start(args , arg_num);
    
    this->descriptorList.clear();
    for (count = 0 ; count < arg_num ; count++) {
        FFTDescriptor d = static_cast<FFTDescriptor>(va_arg(args , int));
        this->descriptorList.push_back(d);
        this->descriptorNameList.push_back(getDescriptorName(d));
    }
    va_end(args);

}

void IRFFTDescriptor::operateAnalysis()
{
    if(!hasFFTOperated())
    {
        
        if(getNumFrame() > 0)
        {
            FFT();
            //cartopol();
        }else{
            std::cout << "Error : IRFFTDescriptor() : Could not operate FFT number of frame = " << getNumFrame() << std::endl;
        }
    }
    
    /*
    for(auto de : descriptorList)
    {
        calcDescriptor(de);
    }*/
     
}



std::string IRFFTDescriptor::getDescriptorName(FFTDescriptor descriptor)
{
    switch (descriptor)
    {
        case FFT_MAGNITUDE:
            return "Magnitude";
            break;
        case FFT_CENTROID:
            return "Centroid";
            break;
            
        case FFT_SPREAD:
            return "Spread";
            break;
        case FFT_FLATNESS:
            return "Flatness";
            break;
            
        case FFT_NOISINESS:
            return "Noisiness";
            break;
            
        case FFT_PITCH:
            return "Pitch";
            break;
            
        case FFT_MFCS:
            return "MFCs";
            break;
            
        case FFT_MFCCS:
            return "MFCCs";
            break;
            
        case FFT_BFCS:
            return "BFCs";
            break;
            
        case FFT_BFCCS:
            return "BFCCs";
            break;
        case FFT_LinearPower:
            return "LienarPower";
            break;
        case FFT_LogPower:
            return "LogPower";
            break;
        default:
            return "UNKNOWN";
            break;
            
    }
}

// ==================================================

// --------------------------------------------------

// --------------------------------------------------

// ==================================================
