//
//  IRText.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 26/04/2019.
//

#ifndef IRText_hpp
#define IRText_hpp

#include "JuceHeader.h"

class IRText
{
public:
    IRText();
    ~IRText();
    
    File getFile() const { return this->file; } 
    
private:
    File file;
    
    String text;
};
#endif /* IRText_hpp */
