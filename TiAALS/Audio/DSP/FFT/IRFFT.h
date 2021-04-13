//
//  IRFFT.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 03/09/2018.
//

#ifndef IRFFT_h
#define IRFFT_h

#include "JuceHeader.h"

using namespace juce;

class IRFFT
{
public:
    
    IRFFT(int fftsize) :
    fftsize(fftsize),
    ffthalfsize(fftsize/2),
    fft(log2(fftsize))
    {
        
    }
    ~IRFFT() {}
    
    
    void FFT(dsp::Complex<float>* input, dsp::Complex<float>* output, bool direction)
    {
        this->fft.perform (input, output, direction);
    }
    
    void FFT(const float* input, dsp::Complex<float>* output)
    {
        std::vector<dsp::Complex<float>>buf(this->fftsize);
        for(int i = 0; i < this->fftsize; i ++) buf[i] = std::complex<float>( input[i], 0.0f );
        this->fft.perform(buf.data(), output, false);
        
        //for(int i = 0; i < 10; i ++) std::cout << "input = " << input[i] << " : buf = " << buf[i].real() << " : fft r = " << output[i].real() << ", i = " << output[i].imag() << std::endl;
    }
    
    void iFFT(dsp::Complex<float>*input, float* output)
    {
        HeapBlock<dsp::Complex<float>> buf(this->fftsize);

        this->fft.perform(input, buf, true);
        
        for(int i = 0; i < this->fftsize; i ++) output[i] = buf[i].real();

    }

    void iFFT(float* real, float* imag, dsp::Complex<float>* output)
    {
        HeapBlock<dsp::Complex<float>> buf(this->fftsize);
        // insert real value only
        for(int i = 0; i < this->fftsize; i ++) buf[i] = { real[i], imag[i] };

        this->fft.perform(buf, output, true);
    }
    
    // ========================================
    
    static size_t ComplexSize(size_t size)
    {
        // vDSP size
        return (size / 2) + 1;
    }

    
    

    
    int fftsize = 0;
    int ffthalfsize = 0;
    
private:
    
    dsp::FFT fft;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRFFT)
    
};

#endif /* IRFFT_h */
