
#ifndef IRObjectCreater_hpp
#define IRObjectCreater_hpp

#include "JuceHeader.h"

#include "IRObjectCreaterBase.hpp"
#include "IRNodeObject.hpp"


template<class T>
class IRObjectCreater : public IRObjectCreaterBase
{
    
public:
    IRObjectCreater() {}
    ~IRObjectCreater() {}

    IRNodeObject* create(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE) override
    {
        return new T(parent, str);
    }
    
    
private:
};


#endif /* IRObjectCreater_hpp */




