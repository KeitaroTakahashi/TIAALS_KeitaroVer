//
//  IRMasterStr.h
//  IRiMaS
//
//  Created by Keitaro on 18/06/2020.
//

#ifndef IRMasterStr_h
#define IRMasterStr_h

//IRMasterStr is used for the master class of each project (not the application).
// Only IRMasterStr holds some unique methods so that API does not conflict each other.



#include "IRStr.h"
#include "IRObjectFactory2.hpp"

class IRMasterStr : public IRStr
{
public:
    IRMasterStr()
    {
        
    }
    
    virtual ~IRMasterStr()
    {
        
    }
    
    Component* createNewObject(std::string id, Component* parent, IRStr* str) override
    {
        return factory.createObject(id, parent, str);
    }

    
private:
    IRObjectFactory2& factory = singleton<IRObjectFactory2>::get_instance();

};
#endif /* IRMasterStr_h */
