//
//  IRWorkspaceCover.hpp
//  IRiMaS
//
//  Created by Keitaro on 11/05/2020.
//

#ifndef IRWorkspaceCover_hpp
#define IRWorkspaceCover_hpp


#include "IRStrComponent.hpp"
#include "KTextLoader.h"

class IRWorkspaceCover : public Component,
public IRStrComponent
{
public:
    IRWorkspaceCover(IRStr* str);
    
    ~IRWorkspaceCover();
    
    
    // ==================================================
    void setEditMode(bool flag);
    
    bool isEditMode() const { return this->isEditModeFlag; }
    
    bool isDrawGrids() const { return this->isdrawGridsFlag; }
    void enableDrawGrids(bool flag) { this->isdrawGridsFlag = flag; }

    void setBackgroundColour(Colour colour);
    

    void setGridValue(int thinInterval, int thickRatio);
    // ==================================================
    // ==================================================

    
private:
    // ==================================================

    void paint(Graphics& g) override;
    
    void resized() override;
    
    // ==================================================

    bool isEditModeFlag = true;
    bool isdrawGridsFlag = true;
    // ==================================================
    Colour backgroundColour = Colours::white;

    // ==================================================
    Image img;
    
};
#endif /* IRWorkspaceCover_hpp */
