//
//  IRFFTAnalysis.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 26/05/2019.
//

#ifndef IRFFTAnalysis_h
#define IRFFTAnalysis_h

#include "IRAudioDescriptor.hpp"


class IRFFTAnalysis
{
public:
    IRFFTAnalysis(int fftsize, int hopsize, IRWindow::TYPE windowType = IRWindow::TYPE::HAMMING) :
    fftSequence(fftsize, hopsize, windowType)
    {
     
        this->fftSequence.setDescriptor(2,
                                        FFTDescriptor::FFT_MAGNITUDE,
                                        FFTDescriptor::FFT_CENTROID);
        
    }
    
    ~IRFFTAnalysis()
    {
        
    }
    
private:
    
    IRFFTDescriptor fftSequence;
    
};


#endif /* IRFFTAnalysis_h */
