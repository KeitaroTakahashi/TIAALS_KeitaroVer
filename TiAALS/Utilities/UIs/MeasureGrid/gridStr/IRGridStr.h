//
//  IRGridStr.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 30/05/2019.
//

#ifndef IRGridStr_h
#define IRGridStr_h
#include "JuceHeader.h"

struct IRGridStr
{
    
    enum IRGridSize
    {
        SMALL,
        MEDIUM,
        LARGE
    };
    
    enum IRMeasureGridType
    {
        VERTICAL,
        HORIZONTAL
    };
    
    IRGridStr(float value, IRGridSize size, Line<float> line)
    {
        this->value = value;
        this->size = size;
        this->line = line;
    }
    
    float value = 0.0;
    IRGridSize size = SMALL;
    
    Line<float> line;
    
};

#endif /* IRGridStr_h */
