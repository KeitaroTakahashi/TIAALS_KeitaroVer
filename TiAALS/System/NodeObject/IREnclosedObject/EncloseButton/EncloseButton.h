//
//  EncloseButton.h
//  IRiMaS
//
//  Created by Keitaro on 07/07/2020.
//

#ifndef EncloseButton_h
#define EncloseButton_h

#include "IRStrComponent.hpp"

class EncloseButton : public TextButton,
                      public IRStrComponent
{
public:
    EncloseButton(IRStr* str) : IRStrComponent(str)
    {
        
    }
    
    ~EncloseButton()
    {
        
    }
    
    
private:
    
};
#endif /* EncloseButton_h */
