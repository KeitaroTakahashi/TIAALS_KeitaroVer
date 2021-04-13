//
//  IRVNImageViewerObject.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 11/04/2021.
//

#ifndef IRVNImageViewerObject_hpp
#define IRVNImageViewerObject_hpp

#include "IRImageViewerObject.hpp"

class IRVNImageViewerObject : public IRImageViewerObject
{
public:
    IRVNImageViewerObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRVNImageViewerObject();
    
    void initialiseSetup(String text,
                         Colour colour) override;

};

#endif /* IRVNImageViewerObject_hpp */
