//
//  srtWriter.h
//  IRiMaS
//
//  Created by Keitaro on 17/01/2020.
//

#ifndef srtWriter_h
#define srtWriter_h

#include <fstream>
#include "JuceHeader.h"

class srtWriter
{
public:
    
    struct SRT_STRUCT
    {
        std::string beginTime;
        std::string endTime;
        std::string Contents;
        
        SRT_STRUCT(std::string beginTime,
                   std::string endTime,
                   std::string Contents) :
        beginTime(beginTime),
        endTime(endTime),
        Contents(Contents)
        {
            
        }
        
        SRT_STRUCT() :
        beginTime(""),
        endTime(""),
        Contents("")
        {
            
        }
        
        void show()
        {
            std::cout << beginTime << " --> " << endTime << "\n" << Contents << std::endl;
        }
    };
    
    struct IRSRT_STRUCT : public SRT_STRUCT
    {
        Rectangle<float> relativeBounds;
        
        IRSRT_STRUCT()
        {
            
        }
        
        
        
    };
    
    srtWriter()
    {
    }
    
    ~srtWriter()
    {
        
    }
    
    void open(std::string filePath)
    {
        index = 0;
        myFile.open(filePath, std::ofstream::trunc);

    }
    
    void close()
    {
        myFile.close();
    }
    
    void addItem(SRT_STRUCT item)
    {
        index ++;
        this->myFile << std::to_string(index) << std::endl;
        this->myFile << item.beginTime << " --> " << item.endTime << std::endl;
        this->myFile << item.Contents << std::endl;
        this->myFile << "\n";
    }

   
private:
    
    std::ofstream myFile;
    int index = 0;
};

#endif /* srtWriter_h */
