//
//  IRVNTextEditorObject.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 04/04/2021.
//

#ifndef IRVNTextEditorObject_hpp
#define IRVNTextEditorObject_hpp

#include "IRTextEditorObject.hpp"

class IRVNTextEditorObject : public IRTextEditorObject
{
public:
    IRVNTextEditorObject(Component* parent, IRStr* str, IRBoundType boundType = IRBoundType::ABSOLUTE);
    ~IRVNTextEditorObject();
    void initialiseSetup(String text,
                         Colour colour) override;
    
    void initialiseSetup(String text,
                         Colour colour,
                         int fontSize);

private:
};
#endif /* IRVNTextEditorObject_hpp */
