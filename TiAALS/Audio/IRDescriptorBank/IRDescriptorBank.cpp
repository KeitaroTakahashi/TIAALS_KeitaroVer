//
//  IRDescriptorBank.cpp
//  IRiMaS
//
//  Created by Keitaro on 17/07/2019.
//

#include "IRDescriptorBank.hpp"

IRDescriptorBank::IRDescriptorBank()
{
    this->descriptorList.clear();
    this->descriptorNameList.clear();
    
    // descriptor list
    addDescriptorList(FFT_MAGNITUDE);
    addDescriptorList(FFT_CENTROID);
    addDescriptorList(FFT_SPREAD);
    addDescriptorList(FFT_FLATNESS);
    addDescriptorList(FFT_PITCH);
    
}

IRDescriptorBank::~IRDescriptorBank()
{
    this->descriptorList.clear();
    this->fftsequence.reset();
        
    std::cout << "~IRDescriptorBank \n";

}
// ============================================================
void IRDescriptorBank::setCurrentFFTSize(int fftsize)
{
    this->fftsize = fftsize;
    this->ffthalfsize = fftsize / 2;
}

void IRDescriptorBank::setHopSize(int hopsize)
{
    this->hopsize = hopsize;
    
    
}

// ============================================================

// calculate Magnitude, Centroid, Spread at the same time!
void IRDescriptorBank::calcBasicDescriptor()
{
    if(!isDescriptor(FFT_LinearPower, fftsize) ||
       isDescriptor(FFT_MAGNITUDE, fftsize))
    {
        printf("Error : calcMagnitudeAndCentroid. LinearPower not yet be calculated.\n");
        return;
    }
    
    int i, j;
    float freq_accum = 0;
    float spread_accum = 0;
    
    float mag = 0;
    float cent = 0;
    float sp = 0;
    float freq_bin = 44100.0 / float(fftsize);
    
    // call frequency per bin
    std::vector<float> freq_per_bin;
    freq_per_bin.reserve(this->ffthalfsize);
    for(i=0;i<this->ffthalfsize;i++)
    {
        freq_per_bin.emplace_back(float(i) * freq_bin);
    }
    
    IRDescriptorStr* powerStr = getDescriptor(FFT_LinearPower,
                                              fftsize);
    const float* power = powerStr->getRawData();
    int frameNum = powerStr->getNumFrame();
    std::cout << "basic analysis frameNum = " << frameNum << std::endl;
    
    std::vector<float> m(frameNum, 0.0);
    std::vector<float> c(frameNum, 0.0);
    std::vector<float> s(frameNum, 0.0);
    for(i=0;i<frameNum;i++)
    {
        mag = 0;
        cent = 0;
        sp = 0;
        freq_accum = 0;
        spread_accum = 0;
        
        for(j=0;j<this->ffthalfsize;j++)
        {
            int index = i * this->ffthalfsize + j;
            
            freq_accum += (freq_per_bin[j] * power[index]);
            mag += power[index];
        }
        
        if(mag == 0.0) cent = 0.0;
        else cent = freq_accum / mag;
        m[i] = mag;
        c[i] = cent;
        
        for(j=0;j<this->ffthalfsize;j++){
            spread_accum += power[i * this->ffthalfsize + j] * fabs(freq_per_bin[j] * (float)j - cent);
        }
    
        if(mag == 0.0) sp = 0.0;
        else sp = spread_accum / mag;
        
        s[i] = sp;
    }
    
    addDescriptor(FFT_MAGNITUDE, fftsize, m);
    addDescriptor(FFT_CENTROID, fftsize, c);
    addDescriptor(FFT_SPREAD, fftsize, s);

}

void IRDescriptorBank::calcFlatness()
{
    
    if(!isDescriptor(FFT_LinearPower, fftsize) ||
       isDescriptor(FFT_FLATNESS, fftsize))
    {
        printf("Error : calcFlatness. LinearPower not yet be calculated.\n");
        return;
    }
    
    
    int i, j;
    float multi_accum = 1.0;
    float mag = 0;
    
    //float limits = std::numeric_limits<float>::min();
    
    IRDescriptorStr* powerStr = getDescriptor(FFT_LinearPower,
                                              fftsize);
    const float* power = powerStr->getRawData();
    int frameNum = powerStr->getNumFrame();

    std::vector<float> flat(frameNum, 0.0);

    for(i=0;i<frameNum;i++)
    {
        for(j=0;j<this->ffthalfsize;j++)
        {
            int index = i * this->ffthalfsize + j;
            mag += (power[index] + 1.0);
            multi_accum *= (power[index] + 1.0);
            multi_accum = sqrt(multi_accum);
        }
        
        mag = mag / this->ffthalfsize;
        if(multi_accum != 0.0 && mag != 0.0)
            flat[i] = multi_accum / mag;
        else flat[i] = 0.0;
        
        
    }
    addDescriptor(FFT_FLATNESS, fftsize, flat);

}
void IRDescriptorBank::calcPitch()
{
    if(!isDescriptor(FFT_LinearPower, fftsize) ||
       isDescriptor(FFT_PITCH, fftsize))
    {
        printf("Error : calcPitch. LinearPower not yet be calculated.\n");
        return;
    }
}
void IRDescriptorBank::calcNoisiness()
{
    if(!isDescriptor(FFT_LinearPower, fftsize) ||
       isDescriptor(FFT_NOISINESS, fftsize))
    {
        printf("Error : calcNoisiness. LinearPower not yet be calculated.\n");
        return;
    }
}
// ============================================================

std::string IRDescriptorBank::getDescriptorName(FFTDescriptor descriptor)
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
        default:
            return "UNKNOWN";
            break;
            
    }
}

// ============================================================
void IRDescriptorBank::addDescriptorList(FFTDescriptor newDescriptor)
{
    for(auto list : this->descriptorList)
    {
        if(list == newDescriptor) return;
    }
    
    this->descriptorList.add(newDescriptor);
    ascendingSorter sorter;
    this->descriptorList.sort(sorter);
    
    this->descriptorNameList.clear();
    
    for(auto de : this->descriptorList)
    {
        this->descriptorNameList.add(getDescriptorName(de));
    }
}

// ============================================================

void IRDescriptorBank::operateAnalysis(AudioSampleBuffer* data, int fftsize, int hopsize, IRWindow::TYPE type)
{
    setCurrentFFTSize(fftsize);
    if(isDescriptor(FFT_LinearPower, fftsize))
    {
        std::cout << "FFT for " << fftsize << " already operated.\n";
        return;
    }

    
    this->fftsequence.reset(new IRFFTSequence(fftsize, hopsize, type));
    
    float* startPtr = data->getWritePointer(0);
    int len = data->getNumSamples();
    this->fftsequence->setAudioData(startPtr, len);
    
    this->nframe = this->fftsequence->getNumFrame();
    
    
        this->fftsequence->FFT();
    
    if(this->fftsequence->getNumFrame() > 0)
    {
        // get liner power and store it
        addDescriptor(FFT_LinearPower, fftsize, this->fftsequence->getPower());
        
        std::cout << "FFT operated! numFrame = "<< this->fftsequence->getNumFrame() << " : fftsize = " << fftsize << std::endl;
        
        // phase
        // ......
                
    }else
    {
        std::cout << "Error : IRFFTDescriptor() : Could not operate FFT number of frame = " << getNumFrame() << std::endl;
    }


}

// ============================================================

