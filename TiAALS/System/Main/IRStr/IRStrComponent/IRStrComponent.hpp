//
//  IRStrComponent.hpp
//  IRiMaS
//
//  Created by Keitaro on 29/08/2019.
//

#ifndef IRStrComponent_hpp
#define IRStrComponent_hpp

#include "IRStr.h"
#include "Benchmark.h"


class IRStrComponent
{
 
public:
    IRStrComponent(IRStr* str, IRStr* parentStr = nullptr);
    ~IRStrComponent();
    // ==================================================

    IRStr* getStr() { return this->ir_str; }
    void setStr(IRStr* str) { this->ir_str = str; }
    KeyListener* getMasterKey() const { return this->masterKey; }
    
    // keep its parent IRStr
    IRStr* getParentStr() const { return this->ir_parentStr; }
    void setParentStr(IRStr* str) { this->ir_parentStr = str; }
    
    // ==================================================

    void setUIColour(IR::colorPattern pattern);
    
    
    // ==================================================
        

 // ==================================================

private:
    IRStr* ir_str;
    KeyListener* masterKey;
    
    IRStr* ir_parentStr;
    
};

#endif /* IRStrComponent_hpp */
