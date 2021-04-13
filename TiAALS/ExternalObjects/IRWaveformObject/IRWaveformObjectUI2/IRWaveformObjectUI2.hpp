//
//  IRWaveformObjectUI2.hpp
//  NodeComponentObject_Study - App
//
//  Created by Keitaro on 02/06/2019.
//

#ifndef IRWaveformObjectUI2_hpp
#define IRWaveformObjectUI2_hpp

#include "IRWaveformObjectUI.hpp"
#include "IRViewPort.hpp"
#include "IRMeasureGrid.hpp"
#include "IRViewUI.hpp"



class IRWaveformObjectUI2 : public IRUIFoundation,
public ChangeListener
{
public:
    
    enum IRWaveformUIStatus
    {
        AudioFileImportCompleted,
        AudioFileChanged,
        DescriptorSelected
    };
    
    IRWaveformObjectUI2(IRNodeObject* parent, IRStr* str);
    ~IRWaveformObjectUI2();
    // ==================================================
    void resized() override;
    void paint(Graphics& g) override;
    
    // ==================================================


    void setEditMode(bool newEditMode) override;

    void visibleAreaChanged(Rectangle<int> area);
    
    void setAutomationWidthRatio(float ratio);
    float getAutomationWidthRatio() const { return this->automation_width_ratio; }
    
    IRWaveformObjectUI* getWaveformUI() { return this->waveform.get(); }
    
    int getGridSize() const { return this->gridSize; }
    int getXMargin() const { return this->xMargin; }
    int getYMargin() const { return this->yMargin; }
    int getScrollSpace() const { return this->scrollSpace; }
private:
    
    void changeListenerCallback (ChangeBroadcaster* source) override;

    
    // ==================================================
    void zoomResize();
    
    // ==================================================
    std::shared_ptr<IRViewUI> waveformView;
    
    
    std::shared_ptr<IRWaveformObjectUI> waveform;
    
    float automation_width_ratio = 1.0;
    
    int xMargin = 5;
    int yMargin = 1;
    int scrollSpace = 10;
    int previousOffsetX = 0;

    // ==================================================
    
    void zoomInClicked();
    void zoomOutClicked();
    
    // ==================================================

    int gridSize = 30;
    
};
#endif /* IRWaveformObjectUI2_hpp */
