//
//  IRDescriptorBank.hpp
//  IRiMaS
//
//  Created by Keitaro on 17/07/2019.
//

#ifndef IRDescriptorBank_hpp
#define IRDescriptorBank_hpp
#include "JuceHeader.h"
#include <stdio.h>
#include <map>
#include <limits>
#include <vector>
#include <stdarg.h>
#include "IRFFTSequence.h"
#include "IRDescriptorStr.h"
#include "IRDescriptorBankFundation.h"

class IRDescriptorBank : public IRDescriptorBankFundation
{
public:
    IRDescriptorBank();
    ~IRDescriptorBank();
    
    // ============================================================

    // all descriptors produced by the fftsize is stored.
    void setCurrentFFTSize(int fftsize);
    
    // when hopsize changed, operate analysis again...
    void setHopSize(int hopsize);
    
    // ============================================================

    
    
    // ============================================================
    
    void calcBasicDescriptor();
    void calcFlatness();
    void calcPitch();
    void calcNoisiness();
    
    // --------------------------------------------------
    
    
    
    // ============================================================
    int getCurrentFFTSize() const { return this->fftsize; }
    int getCurrentFFTHalfSize() const { return this->ffthalfsize; }
    int getHopSize() const { return this->hopsize; }
    unsigned long getNumFrame() const { return this->nframe; }
    // ============================================================
    std::string getDescriptorName(FFTDescriptor descriptor);
    
    // ============================================================
    Array<FFTDescriptor> getDescriptorList() const { return this->descriptorList; }
    Array<std::string> getDescriptorNameList() const { return descriptorNameList; }

    
    void addDescriptorList(FFTDescriptor newDescriptor);
    // ============================================================
    void operateAnalysis(AudioSampleBuffer* data,
                         int fftsize,
                         int hopsize,
                         IRWindow::TYPE type = IRWindow::TYPE::HANNING);
    
private:
    // ============================================================
    int fftsize = 2048;
    int ffthalfsize = 1024;
    int hopsize = 1024;
    unsigned long nframe = 0;
    
    
    // ============================================================
    
    
    Array<FFTDescriptor> descriptorList;
    Array<std::string> descriptorNameList;

    
    // ============================================================
    
    std::unique_ptr<IRFFTSequence> fftsequence = nullptr;
    
    // ============================================================
    
    class ascendingSorter
    {
    public:
        static int compareElements (const FFTDescriptor first, const FFTDescriptor second)
        {
            if (first < second)
                return -1;
            if (first > second)
                return 1;
            return 0;
        }
    };
};


#endif /* IRDescriptorBank_hpp */
