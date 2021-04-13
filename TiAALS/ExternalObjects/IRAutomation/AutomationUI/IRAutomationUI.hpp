//
//  IRAutomation.hpp
//  InteractiveAutomation - App
//
//  Created by Keitaro on 02/05/2019.
//

#ifndef IRAutomation_hpp
#define IRAutomation_hpp


#include "IRUIFoundation.hpp"
#include "InteractiveAutomation.hpp"
#include "AutomationController.hpp"
#include "IRViewUI.hpp"

#include "IRFFTAnalysis.h"

class IRAutomationUI : public IRUIFoundation,
public ChangeBroadcaster,
public IRAudio::Listener
{
public:
    
    enum IRAutomationUIStatus
    {
        AudioFileImportCompleted,
        AudioFileChanged,
        DescriptorSelected,
        zoomInfoShared,
        currentPlayedFrameShared,
        viewPosShared
    };
    
    IRAutomationUI(IRNodeObject* nodeObject, IRStr* str);
    ~IRAutomationUI();
    // ==================================================
    void resized() override;
    void paint(Graphics& g) override;
    // ==================================================
    
    void demoData(int num);
    
    void setDescriptor(IRDescriptorStr* data);
    
    void openFile();
    void openFile(String path);
        
    String getFilePath() const { return this->path; }
    
    IRAutomationUIStatus getStatus() const { return this->status; }
    
    virtual void fileImportCompletedAction() = 0;
    
    DataAllocationManager<IRAudio>* getAudioData() { return this->audioData; }
    
private:
    
    IRAutomationUIStatus status;
    
    IRNodeObject* parent;
    
    void getFilePtr(File file);
    void fileImportCompleted();
    
    DataAllocationManager<IRAudio>* audioData = nullptr;
    // ==================================================
    
    // called by IRAudio
    void zoomInOutOperatedFromComponent(IRAudio* obj) override;
    void audioPlayOperatedFromComponent(IRAudio* obj) override;
    void viewPortPositionFromComponent(IRAudio* obj) override;
    
    void setZoomInfo(juce::Point<float> zoom) {
        this->zoomInfo = zoom;
        if(this->audioData != nullptr)
        {
            auto data = this->audioData->getData();
            data->setZoomInfo(this->zoomInfo);
        }
    }
    
    void setZoomInfo(float w, float h) {
        this->zoomInfo = juce::Point<float>(w, h);
        setZoomInfo(this->zoomInfo);
    }
    
    void linkZoomInfo(Component* comp);
    void linkViewPosition(Component* comp);
    
    juce::Point<float> getZoomInfo() const { return this->zoomInfo; }
    
    void setCurrentPlayedFrame(int64 frame) { this->currentPlayedFrame = frame; }
    int64 getCurrentPlayedFrame() const { return this->currentPlayedFrame; }
    
    void linkCurrentPlayedFrame(Component* comp);
    
    void setVisiblePos(juce::Point<int>pos) { this->visiblePos = pos; }
    juce::Point<int> getVisiblePos() const { return this->visiblePos; }
    
    Rectangle<int> visibleArea;
    // ---------------------------------------------------------------------------
    // sharedInformation
    
    int64 currentPlayedFrame = 0;
    juce::Point<int>visiblePos;
    juce::Point<float> zoomInfo;
    Rectangle<int>playingLine;
    
    void createPlayingLine(int64 currentFrame);
    
    // ==================================================
    
    std::shared_ptr<IRViewUI> automationView;

    void visibleAreaChanged(Rectangle<int> area);
    
    int previousOffsetX = 0;
    
    // ==================================================
    void zoomInClicked();
    void zoomOutClicked();
    void movableClicked(IRAutomation::movableStatus status);
    // ==================================================

    // setup
    bool isVerticalMovable = true;
    bool isHorizontalMovable = true;
    
    // all setter
    void setMovable(bool movable, bool verticalMovable, bool horizontalMovable);
    
    // ==================================================
    
    std::shared_ptr<InteractiveAutomation> automation;
    
    float automation_width_ratio = 1.0;
    
    int xMargin = 5;
    int yMargin = 1;
    
    int controllerWidth = 40;
    
    File file;
    String path;
    
    // ==================================================
    std::string randomIDForPtr;

    // ==================================================

};

#endif /* IRAutomation_hpp */
