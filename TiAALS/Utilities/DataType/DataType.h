//
//  DataType.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 07/09/2018.
//

#ifndef DataType_h
#define DataType_h

#include "IRAudio.hpp"
#include "IRData.hpp"
#include "IRText.hpp"
#include "IRImage.hpp"

typedef void* IRObjectPtr;


enum IRDataType
{
    INT,
    FLOAT,
    
    STRING,
    FILEPATH,
    
    IMAGE,
    MOVIE,
    AUDIO,
    
    OBJECT
};



#endif /* DataType_h */
