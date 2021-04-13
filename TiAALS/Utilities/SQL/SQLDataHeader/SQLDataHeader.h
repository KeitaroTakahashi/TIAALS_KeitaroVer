//
//  SQLDataHeader.h
//  IRiMaS
//
//  Created by Keitaro on 03/09/2019.
//

#ifndef SQLDataHeader_h
#define SQLDataHeader_h

#include "DataType.h"

struct SQLDataHeader
{
    // Title of a column
    std::string columnTitle;
    
    IRDataType dataType;
    
    
    SQLDataHeader(std::string columnTitle, IRDataType dataType)
    {
        this->columnTitle = columnTitle;
        this->dataType = dataType;
    }
    
    std::string getDataTypeInSQLString() const
    {
        switch(this->dataType)
        {
            case INT:
                return "INT";
                break;
            case FLOAT:
                return "REAL";
                break;
            case STRING:
                return "TEXT";
                break;
            case FILEPATH:
                return "TEXT";
                break;
            default:
                return "INVALID";
                break;
                
        }
    }
};

#endif /* SQLDataHeader_h */
