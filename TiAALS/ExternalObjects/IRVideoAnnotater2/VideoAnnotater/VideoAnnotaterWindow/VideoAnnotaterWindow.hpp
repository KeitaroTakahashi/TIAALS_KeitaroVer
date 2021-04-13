//
//  VideoAnnotaterWindow.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 22/03/2021.
//

#ifndef VideoAnnotaterWindow_hpp
#define VideoAnnotaterWindow_hpp

#include <JuceHeader.h>
#include "VideoAnnotaterView.hpp"

/*
 
 VideoAnnotaterWindow
 |
 VideoAnnotaterView - IRStr - VideoAnnotaterBase
 |                                             |                                         |                                          |
 VideoPlayerView - VideoAnnotaterDelegate      WorkspaceView - VideoAnnotaterDelegate    TransportView - VideoAnnotaterDelegate     ControllerView - VideoAnnotaterDelegate
 |                                             |                                         |                                          |
 VideoAnnotaterWorkspace                        WorkspaceWorkspace                       VideoTransportComponent                    optional controller
 

 */



class VideoAnnotaterWindow : public DocumentWindow
{
public:
    VideoAnnotaterWindow(IRStr* str);
    ~VideoAnnotaterWindow();
    
    void close();
    void open();
    
    VideoAnnotaterView* getView() { return this->view.get(); }
private:
    
    void closeButtonPressed() override;
    void minimiseButtonPressed() override;
    void maximiseButtonPressed() override;

    std::shared_ptr<VideoAnnotaterView> view;

};

#endif /* VideoAnnotaterWindow_hpp */
