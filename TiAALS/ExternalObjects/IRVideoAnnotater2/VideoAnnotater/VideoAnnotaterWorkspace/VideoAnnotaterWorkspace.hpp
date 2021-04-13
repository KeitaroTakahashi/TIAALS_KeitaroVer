//
//  VideoAnnotaterWorkspace.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 19/03/2021.
//

#ifndef VideoAnnotaterWorkspace_hpp
#define VideoAnnotaterWorkspace_hpp

#include "IRWorkspaceComponent.hpp"
#include "IRHeavyWeightComponent.h"
#include "VideoAnnotaterDelegate.hpp"
#include "VideoAnnotaterWindowController.hpp"
#include "IRAnnotationWorkspace.hpp"


class VideoAnnotaterWorkspace : public IRAnnotationWorkspace,
public VideoAnnotaterDelegate,
public IRHeavyWeightComponent
{
public:
    VideoAnnotaterWorkspace(String title,
                            Rectangle<int> draggableMargin,
                            IRStr* str,
                            VideoAnnotaterBase* base,
                            int index = 0);
    ~VideoAnnotaterWorkspace();
    
    
    void onPaint(Graphics& g) override;
    void onResized() override;
    
    
    VideoAnnotaterWindowController* getController() override { return this->controller.get(); }
    
    // set from VideoPlayerView
    void setVideoFilePath(String path) { this->videoFilePath = path; }
    
    t_json getSaveData();
    void loadFromSaveData(t_json saveData);

    std::function<void()> openVideoFileCallback = nullptr;
    std::function<void(int)> videoSizePercentCallback = nullptr;
    std::function<void(IRNodeObject*)> nodeObjectStartEndTimeChangedCallback = nullptr;

    // --------------------------------------------------
    
    void createNodeObjectOnWorkspace(IRNodeObject* nodeObj);
    // --------------------------------------------------
    
    void annotationUpdateByPlayingPosition(double pos);
    // --------------------------------------------------



private:
    
    void IRChangeListenerCallback(ChangeBroadcaster* source) override;
    
    
    std::shared_ptr<VideoAnnotaterWindowController> controller;
    
    //void videoLoadCompleteAction();
    void videoSizePercentChangedAction(int val);
    // --------------------------------------------------
    
    void createTextObject();
    void createShapeObject();
    void createImageObject();
    void createMediumTextObject();
    void createSmallTextObject();

    
    void command1Pressed() override;
    void command2Pressed() override;
    void command3Pressed() override;
    void command4Pressed() override;
    void command5Pressed() override;

    void openVideoFileAction();
    // --------------------------------------------------
    //IRNodeObject
    
    void nodeObjectStartEndTimeChanged(IRNodeObject* obj) override;
    // --------------------------------------------------

    // video scale relative to the parent bounds
    float videoScale = 1.0;
    
    String videoFilePath;
    
    double currentPlayingPosition = 0;
};

#endif /* VideoAnnotaterWorkspace_hpp */
