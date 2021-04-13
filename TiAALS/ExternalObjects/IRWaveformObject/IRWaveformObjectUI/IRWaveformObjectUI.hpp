//
//  IRWaveformObjectUI.h
//  NodeComponentObject_Study
//
//  Created by Keitaro on 27/08/2018.
//

#ifndef IRWaveformObjectUI_h
#define IRWaveformObjectUI_h

#include "IRWaveform.hpp"
#include "IRNodeObjectSelector.hpp"
#include "IRGraphSelector.hpp"
#include "IRViewUI.hpp"
#include "IRWaveformUIController.h"

class IRWaveformObjectUI : public IRWaveform
{

public:
    
    IRWaveformObjectUI(IRNodeObject* parent, IRStr* str);
    ~IRWaveformObjectUI();
    
    void resized() override;
    bool isSelectMode() const;
    
    void setEditMode(bool flag) override;
    
    bool isEditMode() const;
    
    void setLooping(bool flag);
    bool isLooping() const;
    
    void setPlayOffset(int offset);
    int getPlayOffset() const;
    
    void mouseDown(const MouseEvent& e) override;
    void mouseDownHandler(const MouseEvent& e);
    
    void mouseUp(const MouseEvent& e) override;
    void mouseUpHandler(const MouseEvent& e);
    
    void mouseDrag(const MouseEvent& e) override;
    void mouseDragHandler(const MouseEvent& e);
    
    void createSquareObject(Rectangle<int> rect);
    void addSquareObject(IRMultiPurposeObject* obj);
    void deleteSquareObject();
    void deselectAllSquareObject();
    void addSelectedObjects();
    void deleteAllObjects();
    
    void playSelectedArea();
    void stopPlaying();
    void playFromBegin();
    
    // listener IRNodeObject
    // This object takes an exclusive listener which is expected to be Workspace.
    void setListener(IRNodeObject::Listener* newListener);
    
    // IRUIAudioFoundation related method
    void IRKeyPressed (int keyCode, String keyText) override;
    
    
    
    
    std::vector<IRMultiPurposeObject* > selectionSquareObjects;
    std::vector<IRMultiPurposeObject* > selectedSquareObjectList;


    // ==================================================
    void setVisibleArea(Rectangle<int> area);
    
    std::function<void()> zoomInClickedCallback = nullptr;
    std::function<void()> zoomOutClickedCallback = nullptr;
    std::function<void()> commentClickedCallback = nullptr;

    // ==================================================

private:
    // ==================================================

    // called when file import completed!
    void fileImportCompletedAction() override;
    // ==================================================
    IRWaveformUIController controller;
    int previousOffsetX = 0;
    Rectangle<int> visibleArea;
    
    void zoomInClicked();
    void zoomOutClicked();
    void commentClicked();
    // ==================================================

    
    std::shared_ptr<IRGraphSelector> selector;

    IRNodeObject::Listener* parentListener;
    
    

    bool selectFlag = true;
    bool selectModeFlag = false;
    
    bool editModeFlag = true;
    
    bool looping = false;
    int playOffset = 0; // delay
    
    // drag drop action
    bool dragdropCalled = false;
    
    int previousWidth = 0;
    int previousHeight = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IRWaveformObjectUI)

};




#endif /* IRWaveformObjectUI_h */




