//
//  IRDescriptorStr.h
//  IRiMaS
//
//  Created by Keitaro on 17/07/2019.
//

#ifndef IRDescriptorStr_h
#define IRDescriptorStr_h

enum FFTDescriptor{
    FFT_MAGNITUDE,
    FFT_CENTROID,
    FFT_SPREAD,
    FFT_FLATNESS,
    FFT_NOISINESS,
    FFT_PITCH,
    FFT_MFCS,
    FFT_MFCCS,
    FFT_BFCS,
    FFT_BFCCS,
    
    FFT_LinearPower,
    FFT_LogPower,
    FFT_Phase,
    
    FFT_NONE
};

class IRDescriptorStr
{
public:
    IRDescriptorStr(int fftsize, int hopsize, FFTDescriptor type) :
    fftsize(fftsize), hopsize(hopsize), type(type)
    {
        this->ffthalfsize = this->fftsize / 2;
    }
    
    ~IRDescriptorStr()
    {
        this->normalizedData.clear();
    }
    // --------------------------------------------------

    void setRawDataPtr(std::vector<float> raw)
    {
        this->raw = raw;
        
        switch(this->type)
        {
            case FFTDescriptor::FFT_LinearPower:
            case FFTDescriptor::FFT_Phase:
            case FFTDescriptor::FFT_LogPower:

                this->nframe = (int)this->raw.size() / this->ffthalfsize;
                break;
            default:
                this->nframe = (int)this->raw.size();
                break;
        }
    }
    // --------------------------------------------------

    void setRawDataPtrAndNormalize(std::vector<float> raw)
    {
        this->raw = raw;
        calcNormalizedData(raw.data(), (int)raw.size());

        switch(this->type)
        {
            case FFTDescriptor::FFT_LinearPower:
            case FFTDescriptor::FFT_Phase:
            case FFTDescriptor::FFT_LogPower:
                
                this->nframe = (int)this->raw.size() / this->ffthalfsize;
                break;
            default:
                this->nframe = (int)this->raw.size();
                break;
        }
        std::cout << "setRawdata : nframe = " << this->nframe << " : " << this->fftsize << std::endl;
       
        
        calcNormalizedData(raw.data(), (int)raw.size());
    }
    // --------------------------------------------------
  
   
    // --------------------------------------------------

    float getMin() const{ return this->min; }
    float getMax() const{ return this->max; }
    int getNumFrame() const { return this->nframe; }
    int getHopSize() const { return this->hopsize; }
    int getFFTSize() const{ return this->fftsize; }
    int getFFTHalfSize() const { return this->ffthalfsize; }
    FFTDescriptor getDescriptorType() const { return this->type; }
    // --------------------------------------------------
    
    const float* getRawData() { return this->raw.data(); }
    const float* getNormalizedData() { return this->normalizedData.data(); }
    std::vector<float> getNormalizedDataVector() { return this->normalizedData; }
    
private:
    // --------------------------------------------------

    void calcMinMax(float* src, int len)
    {
        int i;
        this->min = 99999999;
        this->max = -9999999;
        for(i=0;i<len;i++)
        {
            if(min > src[i]) min = src[i];
            if(max < src[i]) max = src[i];
        }
    }
    // --------------------------------------------------
    void calcNormalizedData(float* raw, int len)
    {
        calcMinMax(raw, len);
        this->normalizedData = std::vector<float>(len, 0.0);
        if(max == 0) return;
        
        int i;
        for(i=0;i<len;i++)
        {
            this->normalizedData[i] = (raw[i] - this->min) / this->max;
        }
    }
    // --------------------------------------------------

    
private:
    int fftsize;
    int ffthalfsize;
    int hopsize;
    int nframe = 0;
    FFTDescriptor type;
    
    float min = 99999999; float max = -99999999;
    
    std::vector<float> raw;
    
    std::vector<float> normalizedData;
};

#endif /* IRDescriptorStr_h */
