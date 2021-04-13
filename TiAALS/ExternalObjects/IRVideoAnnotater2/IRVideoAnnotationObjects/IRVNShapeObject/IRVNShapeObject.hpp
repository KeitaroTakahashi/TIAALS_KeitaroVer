//
//  IRVNShapeObject.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 04/04/2021.
//

#ifndef IRVNShapeObject_hpp
#define IRVNShapeObject_hpp

#include "IRShapeObject.hpp"

class IRVNShapeObject : public IRShapeObject
{
public:
    IRVNShapeObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRVNShapeObject();
    
    
    
private:
    
    void initialSetup();
};

#endif /* IRVNShapeObject_hpp */
