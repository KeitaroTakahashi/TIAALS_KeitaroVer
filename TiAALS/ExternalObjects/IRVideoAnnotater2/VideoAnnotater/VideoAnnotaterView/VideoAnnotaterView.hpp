//
//  VideoAnnotaterView.hpp
//  TIAALS_LIGHT - App
//
//  Created by Keitaro on 22/03/2021.
//

#ifndef VideoAnnotaterView_hpp
#define VideoAnnotaterView_hpp

#include "IRStrComponent.hpp"
#include "VideoTransportComponent.hpp"
#include "VideoAnnotaterDelegate.hpp"
#include "VideoPlayerView.hpp"
#include "ControllerView.hpp"
#include "TransportView.hpp"
#include "WorkspaceView.hpp"

class VideoAnnotaterView : public Component,
public IRStrComponent,
public VideoAnnotaterBase,
public ChangeListener,
public KeyListener
{
public:
    VideoAnnotaterView(IRStr* str);
    ~VideoAnnotaterView();
    //-----------------------------------

    void initializeArea(bool setInitialBounds = true);
    //-----------------------------------
    //-----------------------------------
    
    void setController(IRObjectController* controller);
    void removeController();
    
    void setEditMode(bool flag);
    bool isEditMode() const;
    
    t_json getVideoWorkspaceSaveData();
    void loadVideoWorkspaceSaveData(t_json saveData);
    t_json getSequenceWorkspaceSaveData();
    void loadSequenceWorkspaceSaveData(t_json saveData);
    
    std::function<void()> videoLoadAndLoadSaveDataCompletedCallback = nullptr;
    //-----------------------------------

    void initializeAndOpenFile();
    //void addEventButtonAction();
    void playAction();
    void stopAction();
    
    void playPositionChangedBySliderAction();


private:
    bool loadingSaveData = false;
    //-----------------------------------
    
    void resized() override;
    void paint(Graphics& g) override;
    //-----------------------------------

    void createViews();
    //-----------------------------------

    Rectangle<int> videoPlayerArea;
    Rectangle<int> videoPlayerRect;
    Rectangle<int> transportArea;
    Rectangle<int> workspaceArea;
    Rectangle<int> controllerArea;
    //-----------------------------------
    
    void nothingSelectedAction();
    void nodeObjectGetFocusedAction(IRNodeObject* focusedObj);
    void nodeObjectCreatedAction(IRNodeObject* obj);
    
    // this method is called when sequencer object is created which has an annotation
    // it happens when loading save data
    void sequencerObjectWantsAnnotationObject(IRNodeObject* annotation);
    //-----------------------------------

    std::shared_ptr<VideoPlayerView> videoPlayerView;
    std::shared_ptr<ControllerView> controllerView;
    std::shared_ptr<TransportView> transportView;
    std::shared_ptr<WorkspaceView> workspaceView;
    
    //-----------------------------------

    std::shared_ptr<VideoAnnotaterDelegate> delegate;
    
    VideoTransportComponent transport;
    void videoLoadCompletedAction();
    
    //-----------------------------------
    
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override; // JUCE oriented
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void transportChangeCallback();
    
    //-----------------------------------
    // base
    void eventModifiedAction(Component* modifiedEvent) override;
    void eventSelectedAction(Component* selectedEvent) override;
    void newEventCreatedAction(Component* selectedEvent) override;
    void eventTimeCodeChangedAction(Component* changedEvent) override;
    void updateAnnotation() override;
    void showEventPosition(Component* event) override;
    void eventActivationChanged(Component* changedEvent) override;
    
    void playPositionUpdated(float sec) override;
    void videoSegmentChanged(float begin, float end) override;
    //-----------------------------------
    std::shared_ptr<IRStr> str = nullptr;
    void initialize(IRStr* parentStr);
    //-----------------------------------

};

#endif /* VideoAnnotaterView_hpp */
