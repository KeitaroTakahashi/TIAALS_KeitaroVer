//
//  VideoAnnotaterWindowController.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 24/03/2021.
//

#ifndef VideoAnnotaterWindowController_hpp
#define VideoAnnotaterWindowController_hpp

#include "IRObjectController.hpp"
#include "VideoAnnotaterWindowControllerUI.hpp"

class VideoAnnotaterWindowController : public IRObjectController,
public ChangeBroadcaster
{
public:
    enum VideoAnnotaterWindowControllerStatus
    {
        NONE,
        OpenVideoFile
    };
    
    VideoAnnotaterWindowController(IRStr* str);
    ~VideoAnnotaterWindowController();
    
    
    VideoAnnotaterWindowControllerUI* getVideoAnnotaterController() { return this->videoAnnotaterController.get(); }
    
    VideoAnnotaterWindowControllerStatus getStatus() const { return this->status; }
    
    void callVideoFileCallback();
    std::function<void()> openVideoFileCallback = nullptr;
    
    void callVideoSizePercentCallback();
    std::function<void(int val)> videoSizePercentCallback = nullptr;

private:
    void ControllerResized() override;
    void paint(Graphics& g) override;
    
    VideoAnnotaterWindowControllerStatus status = NONE;
    
    // called by IRObjectController
    void mainControllerSelected() override;
    void arrangeControllerSelected() override;

    void controllerChangeListenerCallback (ChangeBroadcaster* source) override;
    
    std::shared_ptr<VideoAnnotaterWindowControllerUI> videoAnnotaterController;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VideoAnnotaterWindowController)

};
#endif /* VideoAnnotaterWindowController_hpp */
