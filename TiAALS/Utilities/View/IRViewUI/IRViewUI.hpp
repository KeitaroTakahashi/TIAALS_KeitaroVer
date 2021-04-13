//
//  IRViewUI.hpp
//  IRiMaS
//
//  Created by Keitaro on 12/07/2019.
//

#ifndef IRViewUI_hpp
#define IRViewUI_hpp

#include "IRiMaSHeader.h"
#include "IRUIFoundation.hpp"
#include "IRViewPort.hpp"
#include "IRMeasureGrid.hpp"
#include "InteractiveAutomation.hpp"
class IRViewUI : public IRViewPort
{
public:
    IRViewUI(IRStr* str,
             Component* main,
             float vmin, float vmax,
             float hmin, float hmax);
    ~IRViewUI();
    
    // ==================================================
    virtual void zoomInClicked() {};
    virtual void zoomOutClicked() {};
    // ==================================================
    void setVisibleArea(Rectangle<int> area);
    void setComponentBounds(int x, int y, int w, int h);
    
    juce::Point<float> getDummyRatio() const   { return this->viewPort->dummyRatio; }
    int getMaxViewWidth() const          { return this->viewPort->MaxViewWidth; }
    int getMaxViewHeight() const         { return this->viewPort->MaxViewHeight; }
    int getDummyWidth() const            { return this->viewPort->dummyWidth; }
    int getDummyHeight() const           { return this->viewPort->dummyHeight; }
    // ==================================================
    void visibleAreaChangedAction(const Rectangle< int > &newVisibleArea) override;

    // ==================================================

    int getGridSize() const { return this->gridSize; }
    
private:
    // ==================================================

    int gridSize = 20;
    IRMeasureGrid verticalGrid;
    IRMeasureGrid horizontalGrid;
    
    // ==================================================

    class Component4ViewPort : public Component
    {
    public:
          Component4ViewPort(Component* main,
                             IRMeasureGrid* vertical,
                             IRMeasureGrid* horizontal,
                             int gridSize) :
        main(main),
        vertical(vertical),
        horizontal(horizontal),
        gridSize(gridSize)
        {
            addAndMakeVisible(main);
            addAndMakeVisible(vertical);
            addAndMakeVisible(horizontal);
            
        }
        
        ~Component4ViewPort() {}
        
        void setThisBounds(int x, int y, int w, int h)
        {
            int width = w;
            if(width > this->MaxViewWidth) width = this->MaxViewWidth;
            int height = h;
            if(height > this->MaxViewHeight) height = this->MaxViewHeight;

            this->dummyWidth = w;
            this->dummyHeight = h;
            
            this->dummyRatio = juce::Point<float>((float)w / (float)width,
                                            (float)h / (float)height);
            
            
            setBounds(x,y,width,height);
        }
        
        void setHorizontalBounds(int x, int w)
        {
            Rectangle<int> p (this->gridSize + x,
                              0,
                              w - this->gridSize,
                              this->gridSize);
            this->horizontal->setBounds(p);
        }
        
        
        void resized() override
        {
            this->main->setBounds(this->gridSize,
                                  this->gridSize,
                                  getWidth() - this->gridSize,
                                  getHeight() - this->gridSize);
            this->vertical->setBounds(0,
                                      this->gridSize,
                                      this->gridSize,
                                      getHeight() - this->gridSize);
            this->horizontal->setBounds(this->gridSize,
                                        0,
                                        getWidth() - this->gridSize,
                                        this->gridSize);
            
            this->vertical->createGrids();
            this->horizontal->createGrids();

        }
        
        void setVisibleArea(Rectangle<int> area)
        {
            this->vertical->setBounds(area.getX(),
                                      this->gridSize,
                                      this->gridSize,
                                      getHeight() - this->gridSize);
        }
        
        // we use dummy size as it is very expensive if you use millions size of the view...
        juce::Point<float> dummyRatio;
        const int MaxViewWidth = 10000000;
        const int MaxViewHeight = 10000;
        int dummyWidth = 0;
        int dummyHeight = 0;
        
        void setDummyWidth(int w)    { this->dummyWidth = w; }
        void setDummyHeight(int h)   { this->dummyHeight = h; }
        
    private:
        Component* main;
        IRMeasureGrid* vertical;
        IRMeasureGrid* horizontal;

        int gridSize;
    };
    
    std::shared_ptr<Component4ViewPort> viewPort;
    
    
    
    // ==================================================
    // ==================================================
    IR::IRColours& SYSTEMCOLOUR = singleton<IR::IRColours>::get_instance();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRViewUI)

};


#endif /* IRViewUI_hpp */
