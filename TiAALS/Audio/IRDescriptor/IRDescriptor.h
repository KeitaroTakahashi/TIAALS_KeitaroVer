//
//  IRDescriptor.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 24/05/2019.
//

#ifndef IRDescriptor_h
#define IRDescriptor_h

#include "JuceHeader.h"
#include "IRAudioDescriptor.hpp"


struct IRAnalysisDataStr
{
    
public:
    IRAnalysisDataStr()
    {
        this->rowData.clear();
        this->data.clear();
        this->normalizedData.clear();
        
    }
    
    IRAnalysisDataStr(int fftsize, int hopsize)
    {
        this->fftsize = fftsize;
        this->hopsize = hopsize;
    }
    // ==================================================

    void setRowData(std::vector<std::vector<float>> data)
    {
        if(data.size() > 0)
        {
            this->rowData = data;
            this->data = data;
            this->nframe = (int)data[0].size();
        }
    }
    
    void setRowDataAndNormalize(std::vector<std::vector<float>> data)
    {
        if(data.size() > 0)
        {
            this->rowData = data;
            this->data = data;
            this->nframe = (int)data[0].size();
            operateNormalization();
            rescale();
        }
    }
    
    float getRawValue(int frameIndex, int index) const
    {
        return this->rowData[index][frameIndex];
    }
    
    float getNormalizedValue(int frameIndex, int index) const
    {
        return this->normalizedData[index][frameIndex];
    }
    
    std::vector<std::vector<float>> getNormalizedData() const
    {
        return this->normalizedData;
    }
    
    std::vector<std::vector<float>> getRowData() const
    {
        return this->rowData;
    }
    
    std::vector<std::vector<float>> getData() const
    {
        return this->data;
    }
    
    std::vector<std::vector<float>> getScaledData() const
    {
        return this->scaledData;
    }
    
    std::vector<std::vector<float>> getScaledMaxData() const
    {
        return this->scaledMaxData;
    }

    void setData(int frameIndex, int index, float val)
    {
        this->data[index][frameIndex] = val;
    }
    
    float getData(int frameIndex, int index) const
    {
        return this->data[index][frameIndex];
    }
    
    void operateRescale()
    {
        rescale();
    }
    
   
    void setFFTSize(int newFFTSize) { this->fftsize = newFFTSize; }
    void setHopSize(int newHopSize) { this->hopsize = newHopSize; }
    int getFFTSize() const { return this->fftsize; }
    int getHopSize() const { return this->hopsize; }
    int getNumFrame() const { return this->nframe; }
    
    float getMin() const { return this->min; }
    float getMax() const { return this->max; }
    // ==================================================
    
    FFTDescriptor getDescriptorType() const { return this->type; }
    void setDescriptorType(FFTDescriptor newType) { this->type = newType; rescaledMax(); }

private:
    
    void operateNormalization()
    {
        int i, j;
        
        calcMinMax();
        this->normalizedData = this->rowData;
        // normalize row data
        for(i = 0; i < this->rowData.size(); i ++)
            for(j = 0; j < this->rowData[i].size(); j ++)
                this->normalizedData[i][j] = (this->rowData[i][j] - this->min) / this->max;
    }
    
    void calcMinMax()
    {
        int i, j;
        float min = 99999999;
        float max = -99999999;
        float val = 0.0;
        
        for(i = 0; i < this->rowData.size(); i ++)
        {
            for(j = 0; j < this->rowData[i].size(); j ++)
            {
                val = this->rowData[i][j];
                if( min > val ) min = val;
                if( max < val ) max = val;
            }
        }
        
        this->min = min;
        this->max = max;
    }
    
    void rescale()
    {
        int i,j;
        std::cout << "rescale type " << this->type << std::endl;
        this->scaledData = this->rowData;
        if(this->type == FFTDescriptor::FFT_CENTROID ||
           this->type == FFTDescriptor::FFT_PITCH)
        {
            for(i = 0; i < this->rowData.size(); i ++)
            {
                for(j = 0; j < this->rowData[i].size(); j ++)
                {
                    this->scaledData[i][j] = this->rowData[i][j] / 22050.0;
                }
            }
        }else if(this->type == FFTDescriptor::FFT_MAGNITUDE)
        {
            for(i = 0; i < this->rowData.size(); i ++)
            {
                for(j = 0; j < this->rowData[i].size(); j ++)
                {
                    this->scaledData[i][j] = this->rowData[i][j] / 10000;
                }
            }
        }else if(this->type == FFTDescriptor::FFT_SPREAD ||
                 this->type == FFTDescriptor::FFT_FLATNESS)
        {
            for(i = 0; i < this->rowData.size(); i ++)
            {
                for(j = 0; j < this->rowData[i].size(); j ++)
                {
                    this->scaledData[i][j] = this->rowData[i][j];
                }
            }
        }
    }
    
    void rescaledMax()
    {
        int i, j;
        
        calcMinMax();
        this->scaledMaxData = this->rowData;
        // normalize row data
        for(i = 0; i < this->rowData.size(); i ++)
            for(j = 0; j < this->rowData[i].size(); j ++)
                this->scaledMaxData[i][j] = (this->rowData[i][j]) / this->max;
    }
    
    // ==================================================
    
    int fftsize;
    int hopsize;
    int nframe;
    
    FFTDescriptor type = FFTDescriptor::FFT_NONE;
    
    float min, max;
    // this data will be displayed on the object and can be manipulated
    std::vector<std::vector<float>> data;
    // this data will be holded as Original data and can not be manipulated
    std::vector<std::vector<float>> rowData;
    
    // normalized to 0 - 1.0 no matter how the range of the descriptor
    std::vector<std::vector<float>> normalizedData;
    
    // scaled to 0 - 1.0 along with the possible range of the descriptor
    std::vector<std::vector<float>> scaledData;
    
    // scaled to 0 - 1.0 along with the maximum value of the descriptor
    std::vector<std::vector<float>> scaledMaxData;
    
    // ==================================================

};

class IRDescriptor
{
public:
    
    
    IRDescriptor()
    {
        this->descriptorList.clear();
        this->descriptorNameList.clear();
        
        // descriptor list
        addDescriptorList(FFT_MAGNITUDE);
        addDescriptorList(FFT_CENTROID);
        addDescriptorList(FFT_SPREAD);
        addDescriptorList(FFT_FLATNESS);
        //addDescriptorList(FFT_NOISINESS);
        addDescriptorList(FFT_PITCH);
        
        /*
        addDescriptorList(FFT_MFCS);
        addDescriptorList(FFT_MFCCS);
        addDescriptorList(FFT_BFCS);
        addDescriptorList(FFT_BFCCS);
         */

    }
    ~IRDescriptor()
    {
        
    }
    
    // ============================================================

    bool isLinearPower()    const { return this->linearPowerFlag; }
    bool isLogPower()       const { return this->logPowerFlag; }
    bool isPhase()          const { return this->phaseFlag; }

    bool isMagnitude()      const { return this->magnitudeFlag; }
    bool isCentroid()       const { return this->centroidFlag; }
    bool isSpread()         const { return this->spreadFlag; }
    bool isNoisiness()      const { return this->noisinessFlag; }
    bool isPitch()          const { return this->pitchFlag; }
    bool isFlatness()       const { return this->flatnessFlag; }

    bool isMFCs()           const { return this->MFCsFlag; }
    bool isMFCCs()          const { return this->MFCCsFlag; }
    bool isBFCs()           const { return this->BFCsFlag; }
    bool isBFCCs()          const { return this->BFCCsFlag; }

    // ============================================================

    void setLinearPower(IRAnalysisDataStr linearPower)
    {
        this->linearPower = linearPower;
        this->linearPower.setDescriptorType(FFTDescriptor::FFT_LinearPower);
        this->linearPowerFlag = true;
    }
    void setLogPower(IRAnalysisDataStr logPower)
    {
        this->logPower = logPower;
        this->logPower.setDescriptorType(FFTDescriptor::FFT_LogPower);
        this->logPowerFlag = true;
    }
    void setPhase(IRAnalysisDataStr phase)
    {
        this->phase = phase;
        this->logPower.setDescriptorType(FFTDescriptor::FFT_Phase);
        this->phaseFlag = true;
    }

    void setMagnitude(IRAnalysisDataStr magnitude)
    {
        this->magnitude = magnitude;
        this->magnitude.setDescriptorType(FFTDescriptor::FFT_MAGNITUDE);
        this->magnitudeFlag = true;
    }
    void setCentroid(IRAnalysisDataStr centroid)
    {
        this->centroid = centroid;
        this->centroid.setDescriptorType(FFTDescriptor::FFT_CENTROID);
        this->centroidFlag = true;
    }
    void setSpread(IRAnalysisDataStr spread)
    {
        this->spread = spread;
        this->spread.setDescriptorType(FFTDescriptor::FFT_SPREAD);
        this->spreadFlag = true;
    }
    void setNoisiness(IRAnalysisDataStr noisiness)
    {
        this->noisiness = noisiness;
        this->noisiness.setDescriptorType(FFTDescriptor::FFT_NOISINESS);
        this->noisinessFlag = true;
    }
    void setPitch(IRAnalysisDataStr pitch)
    {
        this->pitch = pitch;
        this->pitch.setDescriptorType(FFTDescriptor::FFT_PITCH);
        this->pitchFlag = true;
    }
    void setFlatness(IRAnalysisDataStr flatness)
    {
        this->flatness = flatness;
        this->flatness.setDescriptorType(FFTDescriptor::FFT_FLATNESS);
        this->flatnessFlag = true;
    }
    
    
    void setMFCs(IRAnalysisDataStr MFCs)
    {
        this->MFCs = MFCs;
        this->MFCs.setDescriptorType(FFTDescriptor::FFT_MFCS);
        this->MFCsFlag = true;
    }
    void setMFCCs(IRAnalysisDataStr MFCCs)
    {
        this->MFCCs = MFCCs;
        this->MFCCs.setDescriptorType(FFTDescriptor::FFT_MFCCS);
        this->MFCCsFlag = true;
    }
    void setBFCs(IRAnalysisDataStr BFCs)
    {
        this->BFCs = BFCs;
        this->BFCs.setDescriptorType(FFTDescriptor::FFT_BFCS);
        this->BFCsFlag = true;
    }
    void setBFCCs(IRAnalysisDataStr BFCCs)
    {
        this->BFCCs = BFCCs;
        this->BFCCs.setDescriptorType(FFTDescriptor::FFT_BFCCS);
        this->BFCCsFlag = true;
    }
    
    // ============================================================
    
    IRAnalysisDataStr getLinearPower()        { return this->linearPower; }
    IRAnalysisDataStr getLogPower()           { return this->logPower; }
    IRAnalysisDataStr getPhase()              { return this->phase; }

    
    IRAnalysisDataStr& getMagnitude()         { return this->magnitude; }
    IRAnalysisDataStr& getCentroid()          { return this->centroid; }
    IRAnalysisDataStr& getSpread()            { return this->spread; }
    IRAnalysisDataStr& getNoisiness()         { return this->noisiness; }
    IRAnalysisDataStr& getPitch()             { return this->pitch; }
    IRAnalysisDataStr& getFlatness()          { return this->flatness; }

    
    IRAnalysisDataStr& getMFCs()              { return this->MFCs; }
    IRAnalysisDataStr& getMFCCs()             { return this->MFCCs; }

    IRAnalysisDataStr& getBFCs()              { return this->BFCs; }
    IRAnalysisDataStr& getBFCCs()             { return this->BFCCs; }
    
    
    // ============================================================
    Array<FFTDescriptor> getDescriptorList() const { return this->descriptorList; }
    void addDescriptorList(FFTDescriptor newDescriptor)
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
    Array<std::string> getDescriptorNameList() const { return this->descriptorNameList; }
    
    std::string getDescriptorName(FFTDescriptor descriptor)
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

private:
    
    // linear power [nframe]
    IRAnalysisDataStr linearPower;
    IRAnalysisDataStr logPower;
    IRAnalysisDataStr phase;
    
    IRAnalysisDataStr magnitude;
    IRAnalysisDataStr centroid;
    IRAnalysisDataStr spread;
    IRAnalysisDataStr noisiness;
    IRAnalysisDataStr pitch;
    IRAnalysisDataStr flatness;
    
    // Mel-Frequency Coefficients
    IRAnalysisDataStr MFCs;
    // Mel-Frequency Cepstrum Coefficients
    IRAnalysisDataStr MFCCs;
    // Bark-Frequency Coefficients
    IRAnalysisDataStr BFCs;
    // Bark-Frequency Cepstrum Coefficients
    IRAnalysisDataStr BFCCs;
    
    
    bool linearPowerFlag     = false;
    bool logPowerFlag       = false;
    bool phaseFlag          = false;
    bool magnitudeFlag      = false;
    bool centroidFlag       = false;
    bool spreadFlag         = false;
    bool noisinessFlag      = false;
    bool pitchFlag          = false;
    bool flatnessFlag       = false;

    bool MFCsFlag           = false;
    bool MFCCsFlag          = false;
    bool BFCsFlag           = false;
    bool BFCCsFlag          = false;


    Array<FFTDescriptor> descriptorList;
    Array<std::string> descriptorNameList;
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
#endif /* IRDescriptor_h */
