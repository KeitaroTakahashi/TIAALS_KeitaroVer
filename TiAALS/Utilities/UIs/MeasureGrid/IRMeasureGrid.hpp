//
//  IRMeasureGrid.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 30/05/2019.
//

#ifndef IRMeasureGrid_hpp
#define IRMeasureGrid_hpp

#include "JuceHeader.h"
#include "IRGridStr.h"
#include "IRStrComponent.hpp"

class IRMeasureGrid : public Component,
public IRStrComponent
{
public:

    
    IRMeasureGrid(IRStr* str, IRGridStr::IRMeasureGridType type);
    ~IRMeasureGrid();
    // ==================================================
    
    void paint(Graphics& g) override;
    void resized() override;
    // ==================================================

    // ==================================================
    void initGrids();
    void createGrids();
    
    // ==================================================
    void setRange(float min, float max);
    void setSmallGridInterval(float interval);
    
    
    // ==================================================
    void setSmallGridShowValue(bool flag) { this->isSmallGridShowValueFlag = flag; }
    bool isSmallGridShowValue()     const { return this->isSmallGridShowValueFlag; }
    
    void setMedGridShowValue(bool flag)   { this->isMedGridShowValueFlag = flag; }
    bool isMedGridShowValue()       const { return this->isMedGridShowValueFlag; }
    
    void setLargeGridShowValue(bool flag) { this->isLargeGridShowValueFlag = flag; }
    bool isLargeGridShowValue()     const { return this->isLargeGridShowValueFlag; }
    // ==================================================
    
    void setMarge(int x, int y );

private:
    
    // ==================================================

    // ui
    int margeX = 50;
    int margeY = 50;
    
    IRGridStr::IRMeasureGridType type;

    // ==================================================

    // interval of each grid
    float smallGridInterval = 1.0;
    bool isSmallGridShowValueFlag = false;
    
    // medium size grid every midGridInterval times of smallGridInterval grids
    int medGridInterval = 5;
    bool isMedGridShowValueFlag = false;

    // bigger grid every majorGridInterval times of smallGridInterval grids
    int largeGridInterval = 10;
    bool isLargeGridShowValueFlag = false;
    
    // ==================================================
    
    // min and max values in the range
    float minRange = 0;
    float maxRange = 100;
    
    // ==================================================
    float defaultSmallLineLength = 5.0;
    float smallLineLength   = 5.0;
    float medLineLength     = 10.0;
    float LargeLineLength   = 15.0;
    
    float getLength(IRGridStr::IRGridSize size)
    {
        switch(size)
        {
            case IRGridStr::IRGridSize::SMALL:
                return this->smallLineLength;
                break;
            case IRGridStr::IRGridSize::MEDIUM:
                return this->medLineLength;
                break;
            case IRGridStr::IRGridSize::LARGE:
                return this->LargeLineLength;
                break;
            default:
                break;
        }
    }
    
    // ==================================================

    std::vector<IRGridStr> gridBuffer;
    
    // ==================================================

};

#endif /* IRMeasureGrid_hpp */
