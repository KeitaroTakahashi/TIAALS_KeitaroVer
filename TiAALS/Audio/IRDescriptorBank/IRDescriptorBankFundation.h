//
//  IRDescriptorBank.h
//  IRiMaS
//
//  Created by Keitaro on 17/07/2019.
//

#ifndef IRDescriptorBank_h
#define IRDescriptorBank_h

class IRDescriptorBankFundation
{
public:

    enum FFTSizeList
    {
        F_256,
        F_512,
        F_1024,
        F_2048,
        F_4096,
        F_8192,
        F_16384,
        F_32768,
        F_NONE
    };
    
    // ============================================================
    
    ~IRDescriptorBankFundation()
    {
        
        for(auto item : this->storedDescriptor)
        {
            delete item;
        }
        this->storedDescriptor.clear();
    }
    
    FFTSizeList getListFromFFTSize(int fftsize)
    {
        if(fftsize == 256)           return F_256;
        else if(fftsize == 512)      return F_256;
        else if(fftsize == 1024)     return F_256;
        else if(fftsize == 2048)     return F_256;
        else if(fftsize == 4096)     return F_256;
        else if(fftsize == 8192)     return F_256;
        else if(fftsize == 16384)    return F_256;
        else if(fftsize == 32768)    return F_256;
        else                         return F_NONE;

    }
    
    bool isDescriptor(FFTDescriptor d, FFTSizeList f)
    {
        return this->flags[d][f];
    }
    
    
    bool isDescriptor(FFTDescriptor d, int fftsize = 2048)
    {
        FFTSizeList f = getListFromFFTSize(fftsize);
        return this->flags[d][f];
    }
    
    IRDescriptorStr* getDescriptor(FFTDescriptor d, int fftsize = 2048)
    {
        FFTSizeList f = getListFromFFTSize(fftsize);
        if(!isDescriptor(d, f))
        {
            std::cout << "ERROR : IRDescriptorBankFundation() Descriptor does not exist!\n";
            return nullptr;
        }
        
        return this->bank[d][f];
    }

    IRDescriptorStr* getDescriptor(FFTDescriptor d, FFTSizeList f)
    {
        if(!isDescriptor(d, f))
        {
            std::cout << "ERROR : IRDescriptorBankFundation() Descriptor does not exist!\n";
            return nullptr;
        }
        
        return this->bank[d][f];
    }
    
    void setDescriptorFlag(FFTDescriptor d, FFTSizeList f, bool flag)
    {
        this->flags[d][f] = flag;
    }
    
    void setDescriptorFlag(FFTDescriptor d, int fftsize, bool flag)
    {
        FFTSizeList f = getListFromFFTSize(fftsize);
        if(!isDescriptor(d, f)) return;
        this->flags[d][f] = flag;
    }
    
    void addDescriptor(FFTDescriptor d, FFTSizeList f, IRDescriptorStr* v)
    {
        if(d != FFT_NONE && f != F_NONE)
        {
            this->bank[d][f] = v;
            setDescriptorFlag(d, f, true);
        }
    }
    
    void addDescriptor(FFTDescriptor d, int fftsize, std::vector<float> v)
    {
        FFTSizeList f = getListFromFFTSize(fftsize);

        std::cout << "adddescriptor of " << d << " : size = " << v.size() << std::endl;
        if(d != FFT_NONE && f != F_NONE)
        {
            if(isDescriptor(d, f)) return; // already registered!
            
           // std::shared_ptr<IRDescriptorStr> b = std::make_shared<IRDescriptorStr>(fftsize, 1024, d);
            
            // shared_ptr did not work!!
            IRDescriptorStr* b = new IRDescriptorStr(fftsize, 1024, d);
            
            b->setRawDataPtrAndNormalize(v);
            
            this->storedDescriptor.push_back(b);
            
            this->bank[d][f] = b;
            setDescriptorFlag(d, f, true);
        }
    }
    
    void resetDescriptor(FFTDescriptor d, FFTSizeList f)
    {
        this->bank[d].erase(f);
        this->flags[d].erase(f);
    }
    
    void resetAll()
    {
        this->bank.clear();
        this->flags.clear();
    }
    
    int minFFTSize = 256;
    int maxFFTSize = 32768;
    
    std::map<FFTDescriptor, std::map<FFTSizeList, IRDescriptorStr*>> bank;
    std::map<FFTDescriptor, std::map<FFTSizeList, bool>> flags;
    
    // useed to delete pointer
    std::vector<IRDescriptorStr*> storedDescriptor;
};

#endif /* IRDescriptorBank_h */
