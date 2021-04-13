//
//  IRFFTSequence.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 05/09/2018.
//

#ifndef IRFFTSequence_h
#define IRFFTSequence_h
#include <iostream>
#include <math.h>
#include <vector>
#include "IRFFT.h"
#include "IRSignalWindowLib.h"

class IRFFTSequence
{
    // ============================================================
public:
    IRFFTSequence(int fftsize, int hopsize, IRWindow::TYPE windowType) :
    fftsize(fftsize),
    ffthalfsize(fftsize/2),
    hopsize(hopsize),
    fft(fftsize),
    complexData(fftsize),
    windowType(windowType),
    windowLib(fftsize, windowType)
    {
    }
    
    IRFFTSequence() :
    fftsize(1024),
    ffthalfsize(512),
    hopsize(512),
    fft(1024),
    complexData(fftsize),
    windowType(IRWindow::TYPE::HANNING),
    windowLib(fftsize, windowType)
    {
        
    }
    // ------------------------------------------------------------
    ~IRFFTSequence() {}
    // ------------------------------------------------------------
    void setAudioData(float* data, unsigned long len)
    {
        this->data = data;
        this->len = len;
        //makeSegment();
    }

    void FFT()
    {
        int i, j;
        unsigned long currentIndex = 0;
        unsigned long numFrameSize = 0;

        unsigned long hop = (unsigned long)this->hopsize;
        
        // store current frame
        float* frame = new float [this->fftsize];
        
        
        // calc a number of frames
        while(1)
        {
            // check if there is enough data, if not, break this loop
            if((currentIndex + this->fftsize) >= this->len) break;
            currentIndex += hop;
            numFrameSize ++;
        }
        this->power.clear();
        this->power = std::vector<float>(numFrameSize * this->ffthalfsize, 0.0);
        currentIndex = 0;
        // for each frame...
        for(i=0;i<numFrameSize;i++)
        {
           
            // windowing
            this->windowLib.windowingVector(&this->data[currentIndex],
                                            frame,
                                            this->fftsize);
            
  
            
            this->fft.FFT(frame, this->complexData.data());
            
            
            unsigned long yIndex = i * this->ffthalfsize;
            
            auto c = this->complexData.data();
            for(j=0;j<this->ffthalfsize;j++)
            {
                this->power[yIndex + j] = sqrt(c[j].real() * c[j].real() +
                                               c[j].imag() * c[j].imag());
                
            }
            currentIndex += hop;
        }
        
        this->nframe = numFrameSize;
        
        std::cout << "FFT analysis result numFrame = " << this->nframe << std::endl;
        
        //destroySetup();
        this->hasFFTOperatedFlag = true;
        delete[] frame;
    }
    
    void IFFT()
    {
       
    }
   
    
    void calcDescriptors();
    
    // ------------------------------------------------------------
    unsigned long getNumFrame() const { return this->nframe; }
    std::vector<dsp::Complex<float>> getComplexResultList() { return this->complexData; }
    std::vector<float> getPower() const { return this->power; }
    std::vector<float> getMaxPower() const { return this->maxPower; }
    
    bool hasFFTOperated()               const { return this->hasFFTOperatedFlag; }

    int getHopSize() const { return this->hopsize; }
    // ============================================================
private:
    /*
    void makeSegment()
    {
        int currentIndex = 0;
        int dataSize = (int)this->data.size();
        this->frameData.clear();
        
        do{
            if(currentIndex + this->fftsize < dataSize){
                // process windowing
                std::vector<float>vec = this->windowLib.windowingVector(std::vector<float>(&this->data[currentIndex],
                                                                                           &this->data[currentIndex + this->fftsize]));
                
               
                this->frameData.push_back(vec);

                currentIndex += this->hopsize;
            }else{
                std::vector<float>buf;
                int remainCount = 0;
                for(int i=currentIndex;i<currentIndex+this->fftsize;i++){
                    if(i<dataSize){
                        buf.push_back(data[i]);
                        remainCount ++;
                    }
                    else buf.push_back(0);
                }
                //process windowing
                std::vector<float>vec = this->windowLib.windowingVector(buf,remainCount);
                this->frameData.push_back(vec);
                break;
            }
        }while(true);
        
        std::cout << "audio segment for FFT made. nframe = " << this->frameData.size() << " : fftsize = " << getFFTSize() << " : hopsize = " << getHopSize() <<std::endl;
    }
    */
    int fftsize;
    int ffthalfsize;
    int hopsize;
    unsigned long nframe = 0;
    
    IRFFT fft;
    
    float* data;
    unsigned long len = 0;
    std::vector<std::vector<float>> frameData;
    std::vector<dsp::Complex<float>> complexData;

    std::vector<float> power;
    std::vector<float> maxPower;
    std::vector<float> phase;
    
    IRWindow::TYPE windowType;
    
    IRWindow::IRSignalWindowLib windowLib;
    // ============================================================

    bool hasFFTOperatedFlag = false;
    
    


};
#endif /* IRFFTSequence_h */
