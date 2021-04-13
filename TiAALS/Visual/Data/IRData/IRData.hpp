//
//  IRData.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 26/04/2019.
//

#ifndef IRData_hpp
#define IRData_hpp

#include "JuceHeader.h"

class IRData
{
    IRData();
    ~IRData();
    
    File getFile() const { return this->file; }
private:
    
    File file;
    
};
#endif /* IRData_hpp */
