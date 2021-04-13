//
//  IRShapeUI.hpp
//  IRiMaS
//
//  Created by Keitaro on 26/07/2019.
//

#ifndef IRShapeUI_hpp
#define IRShapeUI_hpp

#include "IRFoundation.h"
#include "IRUIFoundation.hpp"
#include "IRShapePreference.h"
#include "IRShapeController.hpp"

class IRShapeUI : public IRUIFoundation,
public ChangeBroadcaster
{
public:
    
    enum IRShapeStatus
    {
        SQUARE,
        RHOMBUS,
        CIRCLE,
        TRIANGLE,
        RIGHTTRIANGLE
        
    };
    IRShapeUI(IRNodeObject* parent, IRStr* str);
    ~IRShapeUI();
    //========================================================
    
    void paint (Graphics&) override;
    void resized() override;
    
    //========================================================
    void setStatus(IRShapeStatus status)
    {
        this->status = status;
        
        if(this->ShapeController != nullptr)
            this->ShapeController->setShape((int)status + 1);
    }
    IRShapeStatus getStatus() const { return this->status; }
    
    void setColour(Colour colour){ this->colour = colour; }
    Colour getColour() const { return this->colour; }
    
    void setLineWidth(float w) { this->lineWidth = w; }
    float getLineWidth() const { return this->lineWidth; }
    
    void setFill(bool flag)
    {
        this->isFill = flag;
        
        if(this->ShapeController != nullptr)
            this->ShapeController->setFillShape(flag);
    }
    bool getFill()const { return this->isFill; }
    
    void setShapeController(shapeController* ctl)
    {
        this->ShapeController = ctl;
    }
    
private:

    void drawSquare(Graphics& g);
    void drawRhombus(Graphics& g);
    void drawBorderSquare(Graphics& g);
    void drawCircle(Graphics& g);
    void drawTriangle(Graphics& g);
    //========================================================

    bool isFill = false;
    //========================================================

    shapeController* ShapeController = nullptr;
    
    Colour colour;
    IRShapeStatus status = SQUARE;
    
    float lineWidth = 4.0;
    
};
#endif /* IRShapeUI_hpp */
