//
//  VideoPlayerView.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 23/03/2021.
//

#ifndef VideoPlayerView_hpp
#define VideoPlayerView_hpp

#include "VideoAnnotaterDelegate.hpp"
#include "VideoAnnotaterWorkspace.hpp"
#include "IRVideoComponent.h"
#include "KeAnimationComponent.h"


class VideoPlayerView : public Component,
public IRStrComponent,
public VideoAnnotaterDelegate,
IRWorkspaceComponent::Listener,
KeAnimationComponent
{
public:
    VideoPlayerView(IRStr* str, VideoAnnotaterBase* base);
    ~VideoPlayerView();
    // ---------------------------------------------

    t_json getSaveData();
    void loadFromSaveData(t_json saveData);
    
    // ---------------------------------------------
    void nothingSelected() override;
    std::function<void()> nothingSelectedAction = nullptr;
    
    void nodeObjectCreated(IRNodeObject* obj) override;
    std::function<void(IRNodeObject*)> nodeObjectCreatedAction = nullptr;
    
    void nodeObjectGetFocused(IRNodeObject* obj) override;
    std::function<void(IRNodeObject*)> nodeObjectGetFocusedAction = nullptr;
    // ---------------------------------------------
    
    void setVideoBoundsScale(float scale);
    // ---------------------------------------------
    
    IRObjectController* getController() { return this->annotationWorkspace->getController(); }
    VideoAnnotaterWorkspace* getWorkspace() { return this->annotationWorkspace.get(); }
    
    // ---------------------------------------------

    void openVideoFile();
    void videoSizePercentChangedAction(int val);
    void openFile();
    void openFile(File file, bool isCallback = true);
    
    String getVideoFilePath() const { return this->videoFilePath; }
    
    std::function<void()> videoLoadCompletedCallback = nullptr;
    
    void setPlayPosition(double position);
    double getPlayPosition();
    void setAudioVolume(float newVolume);
    float getAudioVolume();
    double getVideoLength();
    void setVideoRange(float begin, float end);
    Point<float> getVideoRange();
    
    void playVideo();
    void stopVideo();
    // ---------------------------------------------

    
    void setInitialBoundsOfWorkspace(Rectangle<int> initialBounds);
    void setInitialBoundsOfWorkspace(Rectangle<float> initialBounds);

private:
    void resized() override;
    void paint(Graphics& g) override;
    // ---------------------------------------------
    void editModeChanged(IRWorkspaceComponent* changedSpace) override;
    // ---------------------------------------------

    std::shared_ptr<VideoAnnotaterWorkspace> annotationWorkspace;
    // ==================================================
    
    void createSequencerObjectFromAnnotation(IRNodeObject* obj);
   
    // ==================================================
    
    void updateAnimationFrame() override;
    
    // --------------------------------------------------

    // video scale relative to the parent bounds
    float videoScale = 1.0;
    
    void rescaleVideoAndAdjustWorkspace(float scale);

    IRVideoComponent videoPlayer;
    String videoFilePath;
    
    float videoBegin = 0.0;
    float videoEnd = 0.0;

    void videoLoadCompleteAction();
    // --------------------------------------------------
    void loadRestSaveDataAfterVideoLoaded();
    bool loadingSaveData = false;
    int temporarlVideoSizePercent = 100;
    
    // --------------------------------------------------
    bool requestCreatingSequencerObject = true;
    
    // --------------------------------------------------
    // if true then initialBounds are set in resize()
    bool requestInitialBoundsToWorkspace = true;
    
public:
    void setRequestCreatingSequencerObject(bool flag) { this->requestCreatingSequencerObject = flag; }
    bool isRequestCreatingSequencerObject() const { return this->requestCreatingSequencerObject; }

    
    // --------------------------------------------------

    class emptyComponent : public Component, public IRStrComponent
    {
    public:
        emptyComponent(IRStr* str):IRStrComponent(str) {}
        void paint(Graphics& g) { g.fillAll(Colours::white); }
    };
    
    emptyComponent empty;

};

#endif /* VideoPlayerView_hpp */
